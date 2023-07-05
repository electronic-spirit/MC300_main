
#include "IS42S16400J.h"

FMC_SDRAM_CommandTypeDef Command;
HAL_StatusTypeDef hal_status;
extern LTDC_HandleTypeDef hltdc;

void IS42S16400J_init(SDRAM_HandleTypeDef *hsdram)
{
	__IO uint32_t tmpmrd=0;
	Command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1_2;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;
	hal_status = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	HAL_Delay(1);

	Command.CommandMode = FMC_SDRAM_CMD_PALL;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1_2;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = 0;
	hal_status = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	HAL_Delay(1);

	Command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1_2;
	Command.AutoRefreshNumber = 8;
	Command.ModeRegisterDefinition = 0;
	hal_status = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	HAL_Delay(1);

	tmpmrd = (uint32_t)	SDRAM_MODEREG_BURST_LENGTH_1 |
						SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL |
						SDRAM_MODEREG_CAS_LATENCY_2 |
						SDRAM_MODEREG_OPERATING_MODE_STANDARD |
						SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

	Command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
	Command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK1_2;
	Command.AutoRefreshNumber = 1;
	Command.ModeRegisterDefinition = tmpmrd;
	hal_status = HAL_SDRAM_SendCommand(hsdram, &Command, SDRAM_TIMEOUT);
	HAL_Delay(1);

	/* Step 8: Set the refresh rate counter */
	/* (15.62 us x Freq) — 20 */
	/* Set the device refresh counter */
	//hsdram->Instance->SDRTR |= ((uint32_t)((1292)<< 1));

	HAL_SDRAM_ProgramRefreshRate(hsdram, 0x0603);
}


void FillScreen(uint32_t color)
{
	uint32_t i;
	uint32_t n = hltdc.LayerCfg[0].ImageHeight*hltdc.LayerCfg[0].ImageWidth;
	for(i=0;i<n;i++)
	{
		*(__IO uint32_t*)(hltdc.LayerCfg[0].FBStartAdress+(i*4)) = color;
	}
}


