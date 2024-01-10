/**
  ******************************************************************************
  * @file    testBluetooth.c
  * @author  Abdoulaye
  * @date    10-January-2023
  * @brief   Contient les fonctions de test du fichier bluetooth HC-05
  ******************************************************************************
*/

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "macro_types.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "HCSR04.h"


HAL_Init();


/**
 * @brief Test pour verifier si le capteur recoie 'F' pour avancer
 */
void testAvancementRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='F');
}


/**
 * @brief Test pour verifier si le capteur recoie 'B' pour reculer
 */
void testReculRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='B');
}


/**
 * @brief Test pour verifier si le capteur recioe 'L' pour tourner à gauche
 */
void testtournerGaucheRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='L');
}

/**
 * @brief Test pour verifier si le capteur recoie 'R' pour tourner à droite
 */
void testtournerDroiteRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='R');
}


/**
 * @brief Test pour verifier si le capteur recoie 'E' pour passer en mode automatique
 */
void modeAutoRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='E');
}


/**
 * @brief Test pour verifier si le capteur recoie 'A' pour passer en mode manuel
 */
void modeManuRobot(void){
	HCSR04_init();
	UART_init(UART2_ID,115200);
	char c = UART_getc(UART2_ID);
	assert(c=='A');
}
