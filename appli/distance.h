/**
  ******************************************************************************
  * @file    distance.h
  * @author  Abdoulaye
  * @date    29-November-2023
  * @brief   Contient les fonctions publiques de distance.c
  ******************************************************************************
*/


#include "config.h"


void HCSR04_init(void);

void HCSR04_mode_auto(void);

uint16_t HCSR04_ChercherDistance(void);
