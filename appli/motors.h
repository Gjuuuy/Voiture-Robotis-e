/**
  ******************************************************************************
  * @file    motors.h
  * @author  Abdoulaye
  * @date    22-November-2023
  * @brief   Contient les fonctions publiques de motors.c
  ******************************************************************************
*/

#include "macro_types.h"
#include "stdint.h"

void MOTOR_init(void);

void MOTOR_turn_right(void);

void MOTOR_move_forward(void);

void MOTOR_turn_left(void);

void MOTOR_move_backward(void);

