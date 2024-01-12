/**
  ******************************************************************************
  * @file    distance.c
  * @author  Abdoulaye
  * @date    29-November-2023
  * @brief   Contient les fonctions utilisables par le HCSR04
  ******************************************************************************
*/


#include "config.h"
#include "HCSR04.h"
#include "macro_types.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "HCSR04.h"
#include "motors.h"

#define CAPTEUR_ULTRA_TRIG_GPIO       GPIOA
#define CAPTEUR_ULTRA_TRIG_PIN		 GPIO_PIN_9


#define CAPTEUR_ULTRA_ECHO_GPIO       GPIOA
#define CAPTEUR_ULTRA_ECHO_PIN        GPIO_PIN_8

#define PERIOD_MEASURE			100


static uint8_t id_sensor;
static uint32_t tlocal;
static HAL_DMA_StateTypeDef ret;
static uint8_t distance;

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

 void HCSR04_mode_auto(void){
	 typedef enum{
			INIT,
			START,
			DETECTE,
	}state_e;

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool_e entrance;
	entrance = (state != previous_state)?TRUE:FALSE;
	previous_state = state;

	switch(state){
		case INIT:
			//HCSR04_init();
			MOTOR_init();
			id_sensor = 0;
			state = START;
			break;
		case START:
			ret = HCSR04_get_value(id_sensor, &distance);

			if(ret == HAL_OK){
				if(distance < 100){
					state = DETECTE;
					printf("Detecte");
				}
			}
			MOTOR_move_forward();
			break;

		case DETECTE:
			HCSR04_get_value(id_sensor, &distance);
			if(distance > 300){
				state = START;
				print("Non detecte");
			}
			MOTOR_turn_right();
			break;

	}

}
