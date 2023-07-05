
#include "CD4052.h"


#define MUX_A_0()	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_RESET)
#define MUX_A_1()	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4, GPIO_PIN_SET)
#define MUX_B_0()	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_RESET)
#define MUX_B_1()	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_6, GPIO_PIN_SET)

void CD4052_MUX(uint8_t channel)
{
	switch(channel)
	{
		case 0: MUX_A_0(); MUX_B_0(); break;
		case 1: MUX_A_1(); MUX_B_0(); break;
		case 2: MUX_A_0(); MUX_B_1(); break;
		case 3: MUX_A_1(); MUX_B_1(); break;
	}
}
