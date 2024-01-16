/**
  ******************************************************************************
  * @file    ecran.c
  * @author  Dorian
  * @date    22-November-2023
  * @brief   Contient les fonctions utilisable par l'ecran TFT
  ******************************************************************************
*/


#include "tft_ili9341/stm32f1_ili9341.h"
#include "ecran.h"
#include "stm32f1xx_hal.h"


/**
 * @brief Initialise l'ecran
 */

void ECRAN_init(void){
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_BLACK);
}

/**
 * @brief Affiche les yeux rouges et la bouche du robot
 * @pre Initialise l'ecran
 */

void visage_yeux_rouges(void){
	ILI9341_DrawFilledCircle(70,70,50, ILI9341_COLOR_RED);
	ILI9341_DrawFilledCircle(70, 250,50, ILI9341_COLOR_RED);
    ILI9341_DrawRectangle(180,60,200,260,ILI9341_COLOR_RED);
}

/**
 * @brief Affiche les yeux bleux et la bouche du robot
 * @pre Initialise l'ecran
 */

void visage_yeux_bleu(void){
	ILI9341_DrawFilledCircle(70,70,50, ILI9341_COLOR_BLUE);
	ILI9341_DrawFilledCircle(70, 250,50, ILI9341_COLOR_BLUE);
    ILI9341_DrawRectangle(180,60,200,260,ILI9341_COLOR_RED);
}
