/*
 * SwitchOff.c
 *
 *  Created on: Feb 10, 2023
 *      Author: agapov
 */
#include "SwitchOff.h"
#include "app_touchgfx.h"

uint8_t TimeOutSwitchOff = 0;

void SwitchOff_process(void)
{
	MX_TouchGFX_Process();

	if(TimeOutSwitchOff<30)TimeOutSwitchOff++;
	else
	{
		// MC300 OFF
		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2)==GPIO_PIN_RESET)
		{
			SaveParameters();
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, RESET);
		}
	}

	ELSPIRE.sleep(100);
}
