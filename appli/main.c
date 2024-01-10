/**
  ******************************************************************************
  * @file    main.c
  * @author  Abdoulaye
  * @date    29-December-2023
  * @brief   Default main function.
  ******************************************************************************
*/
#include "stm32f1xx_hal.h"
#include "stm32f1_uart.h"
#include "stm32f1_sys.h"
#include "stm32f1_gpio.h"
#include "macro_types.h"
#include "systick.h"
#include "stm32f1_motorDC.h"
#include "buzzer.h"
#include "motors.h"
#include "distance.h"
#include "ecran.h"
#include "HCSR04.h"

static uint16_t distanceMesuree;

void writeLED(bool_e b)
{
	HAL_GPIO_WritePin(LED_GREEN_GPIO, LED_GREEN_PIN, b);
}

bool_e readButton(void)
{
	return !HAL_GPIO_ReadPin(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN)	;
}

static volatile uint32_t t = 0;
void process_ms(void)
{
	if(t)
		t--;
}

void state_machine(void){
		typedef enum{
				INIT,
				MODE_AUTO,
				MODE_MANU,
				ERROR
			}state_e;

			static state_e state = INIT;
			static state_e previous_state = INIT;
			bool_e entrance;
			entrance = (state != previous_state)?TRUE:FALSE;
			char c;
			previous_state = state;
			c = UART_getc(UART2_ID);

			switch(state){

			case INIT:
				printf("Mode initialisation\n");
				MOTOR_init();
				ECRAN_init();
				HCSR04_init();

				Systick_add_callback_function(&process_ms);

				state = MODE_AUTO;
				break;

			case MODE_AUTO:
				if(entrance){
					printf("Mode auto active\n");
					//Affichage de quelque chose sur l'écran
					BuzzerOn();
					BuzzerOff();
				}
				if(HCSR04_get_distance() < 350){
					//printf("%d\n", HCSR04_get_distance());
					MOTOR_turn_right();
				}else{
					MOTOR_move_forward();
					//printf("%d\n", HCSR04_get_distance());
				}
				if(c == 'A')
					state = MODE_MANU;
				break;

			case MODE_MANU:
				if(entrance){
					printf("Mode manuel");
					//Affichage de quelque chose sur l'écran
					BuzzerOn();
					BuzzerOff();
					MOTOR_stop();
				}
				//c = UART_getc(UART2_ID);
				if(c == 'F')
					MOTOR_move_forward();
				else if(c == 'B')
					MOTOR_move_backward();
				else if(c == 'L')
					MOTOR_turn_left();
				else if(c == 'R')
					MOTOR_turn_right();
				else if(c == 'S')
					MOTOR_stop();
				else if(c == 'E')
					state = MODE_AUTO;
				break;
			case ERROR:
				break;
			default: break;

			}
	}


int main(void)
{
	//Initialisation de la couche logicielle HAL (Hardware Abstraction Layer)
	//Cette ligne doit rester la première étape de la fonction main().
  	HAL_Init();

	//Initialisation de l'UART2 à la vitesse de 115200 bauds/secondes (92kbits/s) PA2 : Tx  | PA3 : Rx.
		//Attention, les pins PA2 et PA3 ne sont pas reliées jusqu'au connecteur de la Nucleo.
		//Ces broches sont redirigées vers la sonde de débogage, la liaison UART étant ensuite encapsulée sur l'USB vers le PC de développement.
	UART_init(UART2_ID,115200);

	//"Indique que les printf sortent vers le périphérique UART2."
	SYS_set_std_usart(UART2_ID, UART2_ID, UART2_ID);

	//Initialisation du port de la led Verte (carte Nucleo)
	BSP_GPIO_PinCfg(LED_GREEN_GPIO, LED_GREEN_PIN, GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du bouton bleu (carte Nucleo)
	BSP_GPIO_PinCfg(BLUE_BUTTON_GPIO, BLUE_BUTTON_PIN, GPIO_MODE_INPUT,GPIO_PULLUP,GPIO_SPEED_FREQ_HIGH);

	//Initialisation du port du buzzer
	BSP_GPIO_PinCfg(GPIOA, GPIO_PIN_1, GPIO_MODE_OUTPUT_PP, GPIO_PULLUP, GPIO_SPEED_FREQ_LOW);

	//On ajoute la fonction process_ms à la liste des fonctions appelées automatiquement chaque ms par la routine d'interruption du périphérique SYSTICK
	Systick_add_callback_function(&process_ms);
	//Ajouter dans la fonction main(), juste avant la boucle while(1) de tache de fond
	//ECRAN_init();
	HCSR04_init();
	MOTOR_init();

	while(1)	//boucle de tâche de fond
	{
		HCSR04_demo_state_machine();
		/*if(getDistance() < 30){
			printf("%d\n", getDistance());
			MOTOR_turn_right();
		}else{
			MOTOR_move_forward();
			printf("%d\n", HCSR04_get_distance());
		}*/
		//state_machine();
	}


}
