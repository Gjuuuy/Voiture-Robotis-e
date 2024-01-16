/**
  ******************************************************************************
  * @file    distance.c
  * @author  Abdoulaye
  * @date    29-November-2023
  * @brief   Contient les fonctions utilisables par le HCSR04
  ******************************************************************************
*/


#include "config.h"
#include "macro_types.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "HCSR04.h"
#include "motors.h"
#include "buzzer.h"
#include "ecran.h"


#define CAPTEUR_ULTRA_TRIG_GPIO       GPIOA
#define CAPTEUR_ULTRA_TRIG_PIN		 GPIO_PIN_9


#define CAPTEUR_ULTRA_ECHO_GPIO       GPIOA
#define CAPTEUR_ULTRA_ECHO_PIN        GPIO_PIN_8

#define PERIOD_MEASURE                100

static uint8_t id_sensor;
static uint16_t distance;

/**
 * @brief Initialisation du capteur HC-SR04
 */

void HCSR04_init(void){
	if(HCSR04_add(&id_sensor, CAPTEUR_ULTRA_TRIG_GPIO, CAPTEUR_ULTRA_TRIG_PIN, CAPTEUR_ULTRA_ECHO_GPIO, CAPTEUR_ULTRA_ECHO_PIN) != HAL_OK)
		{
			printf("HCSR04 non ajout - erreur gnante\n");
		}
		else
		{
			printf("HCSR04 ajout\n");
		}
}

/**
 * @brief Calcul de la distance mesure par le capteur de distance
 * @pre Initialisation du capteur HC-SR04
 * @retval valeur en 16 bits de la distance mesuree par le capteur de distance
 */

uint16_t HCSR04_ChercherDistance(void){

	typedef enum
		{
			INIT,
			FAIL,
			LAUNCH_MEASURE,
			RUN,
			WAIT_DURING_MEASURE,
			WAIT_BEFORE_NEXT_MEASURE
		}state_e;

		static state_e state = INIT;
		static uint32_t tlocal;
		HAL_StatusTypeDef ret;

		//ne pas oublier d'appeler en tache de fond cette fonction.
		HCSR04_process_main();


		switch(state)
		{
			case INIT:
				printf("HCSR04 ajoute\n");
				state = LAUNCH_MEASURE;
				break;
			case LAUNCH_MEASURE:
				HCSR04_run_measure(id_sensor);
				tlocal = HAL_GetTick();
				state = WAIT_DURING_MEASURE;
				break;
			case WAIT_DURING_MEASURE:
				ret = HCSR04_get_value(id_sensor, &distance);
				switch(ret)
				{
					case HAL_BUSY:
						//rien a faire... on attend...
						break;
					case HAL_OK:
						printf("distance : %d\n", distance);
						state = WAIT_BEFORE_NEXT_MEASURE;
						break;
					case HAL_ERROR:
						printf("sensor %d - erreur ou mesure non lancee\n", id_sensor);
						state = WAIT_BEFORE_NEXT_MEASURE;
						break;

					case HAL_TIMEOUT:
						printf("sensor %d - timeout\n", id_sensor);
						state = WAIT_BEFORE_NEXT_MEASURE;
						break;
				}
				break;
			case WAIT_BEFORE_NEXT_MEASURE:
				if(HAL_GetTick() > tlocal + PERIOD_MEASURE)
					state = LAUNCH_MEASURE;
				break;
			default:
				break;
		}
		return distance;
	}


/**
 * @brief mode automatique de la detection d objet
 * @pre Initialisation du capteur HC-SR04
 */

 void HCSR04_mode_auto(void){
	 typedef enum{
			START,
			DETECTE
	}state_e;

	static state_e state = START;
	static state_e previous_state = START;
	bool_e entrance;
	entrance = (state != previous_state)?TRUE:FALSE;
	previous_state = state;

	switch(state){
		case START:
			distance = HCSR04_ChercherDistance();
			if(distance < 300){
				state = DETECTE;
			}
			MOTOR_move_forward();
			if(entrance){
				visage_yeux_bleu();
			}

			break;
		case DETECTE:

			if(HCSR04_ChercherDistance() > 300){
				state = START;
			}

			MOTOR_turn_right();
			if(entrance){
				visage_yeux_rouges();
				BuzzerOn();
				BuzzerOff();
			}
	}
 }

