/**
  ******************************************************************************
  * @file    motors.c
  * @author  Abdoulaye
  * @date    22-November-2023
  * @brief   Contient les fonctions utilisable par le moteur JGA25-370.
  ******************************************************************************
*/



#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "stm32f1_motorDC.h"


#define VITESSE_AVANCER 900
#define VITESSE_TOURNER 700
#define VITESSE_STOP 0

#define RIGHT_MOTOR_R1_GPIO          GPIOB
#define RIGHT_MOTOR_R1_PIN           GPIO_PIN_14

#define RIGHT_MOTOR_F1_GPIO          GPIOB
#define RIGHT_MOTOR_F1_PIN           GPIO_PIN_13

#define LEFT_MOTOR_R0_GPIO         GPIOA
#define LEFT_MOTOR_R0_PIN          GPIO_PIN_10

#define LEFT_MOTOR_F0_GPIO         GPIOA
#define LEFT_MOTOR_F0_PIN          GPIO_PIN_11

static motor_id_e left_motor_id;
static motor_id_e right_motor_id;

/**
 * @brief Intialisation des ports du JGA25-370 du robot
 */

void MOTOR_init(void){

	left_motor_id = MOTOR_add(LEFT_MOTOR_R0_GPIO, LEFT_MOTOR_R0_PIN, LEFT_MOTOR_F0_GPIO, LEFT_MOTOR_F0_PIN);	//le choix des broches est stratégiques : elles doivent correspondre à des TIMERS !
	right_motor_id = MOTOR_add(RIGHT_MOTOR_R1_GPIO, RIGHT_MOTOR_R1_PIN, RIGHT_MOTOR_F1_GPIO, RIGHT_MOTOR_F1_PIN);
}

/**
 * @brief Fais tourner le robot a droite
 * @pre Initialisation des moteurs
 */

void MOTOR_turn_right(void){

	MOTOR_set_duty(left_motor_id, VITESSE_TOURNER);
	MOTOR_set_duty(right_motor_id, -VITESSE_TOURNER);
	HAL_Delay(750);

}

/**
 * @brief Fais avancer le robot
 * @pre Initialisation des moteurs
 */
void MOTOR_move_forward(void){

	MOTOR_set_duty(left_motor_id, VITESSE_AVANCER);
	MOTOR_set_duty(right_motor_id, VITESSE_AVANCER);
	HAL_Delay(1000);

}

/**
 * @brief Fais tourner le robot a gauche
 * @pre Initialisation des moteurs
 */

void MOTOR_turn_left(void){

	MOTOR_set_duty(left_motor_id, -VITESSE_TOURNER);
	MOTOR_set_duty(right_motor_id, VITESSE_TOURNER);
	HAL_Delay(750);

}

/**
 * @brief Arrete le mouvement du robot
 * @pre Initialisation des moteurs
 */

void MOTOR_stop(void){

	MOTOR_set_duty(left_motor_id, VITESSE_STOP);
	MOTOR_set_duty(right_motor_id, VITESSE_STOP);
	HAL_Delay(1000);

}

/**
 * @brief Fais reculer le robot
 * @pre Initialisation des moteurs
 */
void MOTOR_move_backward(void){

	MOTOR_set_duty(left_motor_id, -VITESSE_AVANCER);
	MOTOR_set_duty(right_motor_id, -VITESSE_AVANCER);
	HAL_Delay(1000);

}
