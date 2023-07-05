/*
 * BQ40Z50.c
 *
 *  Created on: Feb 21, 2023
 *      Author: agapov
 */

#include "BQ40Z50.h"
#include "app_touchgfx.h"

extern I2C_HandleTypeDef hi2c4;

uint8_t BQ40Z50_readREG(uint16_t reg)
{
	uint8_t tx_buf[1], rx_buf[1];
	tx_buf[0]=0x0D;
	rx_buf[0]=0x00;
	HAL_I2C_Master_Transmit(&hi2c4, 0x16, tx_buf, 1, 10000);
	HAL_I2C_Master_Receive(&hi2c4, 0x16, (uint8_t *)rx_buf, 1, 10000);
	return rx_buf[0];
}


void BQ40Z50_init(void)
{
	REG[8] = BQ40Z50_readREG(0);
}

void BQ40Z50_process(void)
{
	MX_TouchGFX_Process();

	REG[8] = BQ40Z50_readREG(0);

	ELSPIRE.sleep(1000);
}

