/**
  ******************************************************************************
  * @file    buzzer.c
  * @author  Abdoulaye
  * @date    17-November-2023
  * @brief   Contient les fonctions utilise par le buzzer
  ******************************************************************************
*/


#include "stm32f1xx_hal.h"
#include "stm32f1_gpio.h"




#define BUZZER_GPIO         GPIOA
#define BUZZER_PIN          GPIO_PIN_1


/**
 * @brief Fais sonner le buzzer
 */
void BuzzerOn(void){
	HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, GPIO_PIN_SET);
	HAL_Delay(500);
}

/**
 * @brief Arrete de faire sonner le buzzer
 */
void BuzzerOff(void){
	HAL_GPIO_WritePin(BUZZER_GPIO, BUZZER_PIN, GPIO_PIN_RESET);
	HAL_Delay(500);
}
