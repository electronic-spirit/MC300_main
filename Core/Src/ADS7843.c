
#include "ADS7843.h"


extern SPI_HandleTypeDef hspi1;

static uint16_t data[6];
static int32_t xtemp=0, ytemp=0;
static uint8_t ClickCounter = 50;
static uint32_t X_factor_min = 3959;
static uint32_t X_factor_max = 7805;
static float X_factor = 6.01;
static uint32_t Y_factor_min = 3830;
static uint32_t Y_factor_max = 7449;
static float Y_factor = 7.54;
static uint16_t TouchThreshold = 450;


void ADS7843_Init(void)
{
	X_factor = (float)(X_factor_max - X_factor_min)/640.0;
	Y_factor = (float)(Y_factor_max - Y_factor_min)/480.0;


}


static uint16_t ADS7843_Read_AD(uint8_t CMD)
{
	uint8_t txdata[2];
	uint8_t rxdata[2];
	uint16_t ret;
	txdata[0] = CMD;

	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, txdata, 1, 1000);
	HAL_SPI_Receive(&hspi1, rxdata, 2, 1000);
	HAL_GPIO_WritePin(T_CS_GPIO_Port, T_CS_Pin, GPIO_PIN_SET);

	ret = (rxdata[0] << 8) | rxdata[1];
	ret >>= 3;
	ret &= 0xFFF;

	return ret;
}


uint16_t absTouch(int16_t data)
{
	if(data>0)return (uint16_t)data;
	else return (uint16_t)(-data);
}

static int16_t besttwoavg( int16_t x , int16_t y , int16_t z )
{
//	int16_t da, db, dc;
//	int16_t reta = 0;
//
//	if ( x > y ) da = x - y; else da = y - x;
//	if ( x > z ) db = x - z; else db = z - x;
//	if ( z > y ) dc = z - y; else dc = y - z;
//
//	if ( da <= db && da <= dc ) reta = (x + y) >> 1;
//	else if ( db <= da && db <= dc ) reta = (x + z) >> 1;
//	else reta = (y + z) >> 1;

//	return reta;

	if(absTouch(x-y)>TouchThreshold) return 0;
	else if(absTouch(x-z)>TouchThreshold) return 0;
	else if(absTouch(y-z)>TouchThreshold) return 0;
	else return (x+y+z)/3;
}



uint8_t ADS7843_Update(int32_t *x, int32_t *y)
{
	if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0) && (ClickCounter == 0))
	{
		ClickCounter = 50;

		data[0] = ADS7843_Read_AD(0x90);
		data[1] = ADS7843_Read_AD(0xD0);
		data[2] = ADS7843_Read_AD(0x90);
		data[3] = ADS7843_Read_AD(0xD0);
		data[4] = ADS7843_Read_AD(0x90);
		data[5] = ADS7843_Read_AD(0xD0);

		xtemp = besttwoavg(data[0], data[2], data[4]);
		ytemp = besttwoavg(data[1], data[3], data[5]);

		if(xtemp<=X_factor_min && xtemp!=0) *x = (X_factor_min-xtemp)/X_factor;
		else *x=0;
		if(ytemp<=Y_factor_min && ytemp!=0) *y = (Y_factor_min-ytemp)/Y_factor;
		else *y=0;

		return 1;
	}
	else
	{
		ADS7843_Read_AD(0x90);

		if(ClickCounter>0)ClickCounter--;
		return 0;
	}
}


