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

int8_t eye = 5;
static int16_t color;

/**
 * @brief Initialise l'ecran
 */

void ECRAN_init(void){
	ILI9341_Init();
	ILI9341_Fill(ILI9341_COLOR_BLACK);
}

/**
 * @brief Fais grossir les yeux et les mettent en bleu
 * @pre Initialise l'ecran
 */

void affiche_yeux(void){
for(int i = 0; i < eye; i ++){
		if(eye<35){
			color=ILI9341_COLOR_BLUE;
			visage_robot();
			eye = eye + 2;
		}
		else if(eye>=35 && eye<50){
			color=ILI9341_COLOR_RED;
			visage_robot();
			eye = eye + 2;
		}
		else {
			eye = 5;
			color= ILI9341_COLOR_BLUE;
		}
		//HAL_Delay(10);
	}
}

/**
 * @brief Affiche le visage du robot
 * @pre Initialise l'ecran
 */

void yeux_robot(void){

	  ILI9341_DrawCircle(70,70,50,ILI9341_COLOR_WHITE);
	  ILI9341_DrawCircle(70,250,50,ILI9341_COLOR_WHITE);
      ILI9341_DrawFilledCircle(70,70, eye, color);
      ILI9341_DrawFilledCircle(70, 250, eye, color);
      HAL_Delay(1000);
      ILI9341_DrawRectangle(180,60,200,260,ILI9341_COLOR_RED);
      ILI9341_DrawFilledCircle(70,70, eye, ILI9341_COLOR_BLACK);
      ILI9341_DrawFilledCircle(70, 250, eye, ILI9341_COLOR_BLACK);
}
