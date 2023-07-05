#include "Save.h"
#include "string.h"

#define MYSECTOR 	FLASH_SECTOR_7
#define MYADDR 		0x081E0000

struct Saving SavingParameters;

void SaveParameters(void)
{
	MX_TouchGFX_Process();

	static FLASH_EraseInitTypeDef EraseInitStruct;
	static uint32_t page_error = 0;
	uint32_t isize = sizeof(SavingParameters)>>3;
	uint64_t idata[isize];

	SavingParameters.Brightness = TIM15->CCR1;


	EraseInitStruct.TypeErase = FLASH_TYPEERASE_SECTORS;
	EraseInitStruct.Sector = MYSECTOR;
	EraseInitStruct.NbSectors = 1;
	EraseInitStruct.Banks = FLASH_BANK_2;
	EraseInitStruct.VoltageRange = FLASH_VOLTAGE_RANGE_3;

	FLASH->SR1 |= FLASH_SR_EOP | FLASH_SR_WRPERR | FLASH_SR_PGSERR;
	while(FLASH->SR1 == FLASH_SR_BSY);
	HAL_FLASH_Unlock();
	while(FLASH->SR1 == FLASH_SR_BSY);
	HAL_FLASHEx_Erase(&EraseInitStruct, &page_error);
	while(FLASH->SR1 == FLASH_SR_BSY);

	memcpy((uint8_t*)&idata, (uint8_t*)&SavingParameters, isize*8);
	for(uint32_t i = 0;i < isize;i++)
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, MYADDR+i*8, (uint32_t)&idata[i]);


	HAL_FLASH_Lock();
}

void LoadParameters(void)
{
	MX_TouchGFX_Process();

	uint32_t address = MYADDR;
	uint32_t isize = sizeof(SavingParameters)>>3;
	uint64_t idata[isize];

	for(uint16_t i = 0; i < isize; i++)
	{
		idata[i] = *(uint64_t*)address;
		address = address + 8;
	}
	memcpy((uint8_t *)&SavingParameters, (uint8_t *)&idata, isize*8);

	// Apply parameters
	if(SavingParameters.Brightness<100 && SavingParameters.Brightness>20)
	TIM15->CCR1 = SavingParameters.Brightness;
}

