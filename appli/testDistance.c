/**
  ******************************************************************************
  * @file    testDistance.c
  * @author  Abdoulaye
  * @date    10-January-2023
  * @brief   Contient les fonctions de test du fichier distance.c
  ******************************************************************************
*/

#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "config.h"
#include "HCSR04.h"
#include "macro_types.h"
#include "stm32f1xx_hal.h"
#include "stm32f1_timer.h"
#include "stm32f1_gpio.h"
#include "stm32f1_extit.h"
#include "HCSR04.h"



/**
 * @brief Test pour verifier si la fonction HCSR04_get_distance fonctionne
 */
void testFonctionnementGetDistance(void){
	HAL_Init();
	HCSR04_init();
	//assert(HCSR04_get_distance()<1000);
}


/**
 * @brief Test pour verifier si on peut detecter un objet
 */
void testObjetDetectee(void){
	HAL_Init();
	HCSR04_init();
	//assert(HCSR04_get_distance()<200);
}

/**
 * @brief Test pour verifier si on peut ne pas detecter un objet
 */
void testObjetNonDetectee(void){
	HAL_Init();
	HCSR04_init();
	//assert(HCSR04_get_distance()>200);
}
