
#include "UART_PRESSURE.h"
#include "string.h"
#include "app_touchgfx.h"
#include "usbd_cdc_if.h"

extern UART_HandleTypeDef huart7;
extern DMA_HandleTypeDef hdma_uart7_tx;



enum PressureState
{
	Read_Reg_ADC_0 = 18,
	Read_Reg_ADC_1 = 20,
	Read_Reg_Temperature = 30,
	Read_Reg_Battery = 32,
	Read_Reg_Temperature_Sensor = 34,
	Read_Reg_Pressure = 36,
	Write_Reg_ZeroReg = 38,
	Write_Reg_FilterRatio = 52,
	Write_Reg_FilterOrder = 54,
	Read_Reg_PGA0 = 5,
	Read_Reg_PGA1 = 9
};

uint8_t PRESSTXBuff[PRESSURETX_BUFFER_SIZE];
uint8_t PRESSURERXBuff[PRESSURERX_BUFFER_SIZE];
uint8_t PRESSTXBuff_size = 0;
uint32_t pressurerxcntr = 0;
int16_t TimeOutPressure = -1;
uint16_t UART_PRESSURE_STATE = Read_Reg_Temperature_Sensor;
static uint8_t errcntr = 0;

struct PressureModuleStruct
{
	int32_t ADC_0;
	int32_t ADC_1;
	float Temperature;
	float Battery;
	float Temperature_Sensor;
	float Pressure;
	uint16_t ZeroReg;
	float FilterRatio;
	uint16_t FilterOrder;
};
struct PressureModuleStruct PressureModule;


void UART_PRESSURE_Transmit_process(void)
{
	MX_TouchGFX_Process();

	if(CalibrateChannel.Pressure_outer_Zero == 1) UART_PRESSURE_STATE = Write_Reg_ZeroReg;

	switch(UART_PRESSURE_STATE)
	{
		case Read_Reg_Temperature_Sensor: 	PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_Temperature_Sensor, 0x03, 2); break;
		case Read_Reg_Pressure: 			PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_Pressure, 0x03, 2); break;
		case Write_Reg_ZeroReg: 			PRESSTXBuff_size = WriteUint16ToBUFF((uint8_t*)PRESSTXBuff, PressureAddress, Write_Reg_ZeroReg, CalibrateChannel.Pressure_outer_Zero); break;

		case Read_Reg_ADC_0: 				PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_ADC_0, 0x03, 2); break;
		case Read_Reg_ADC_1: 				PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_ADC_1, 0x03, 2); break;
		case Read_Reg_Temperature: 			PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_Temperature, 0x03, 2); break;
		case Read_Reg_Battery: 				PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_Battery, 0x03, 2); break;
		case Write_Reg_FilterRatio: 		PRESSTXBuff_size = RegisterRequest((uint8_t*)PRESSTXBuff, PressureAddress, Read_Reg_Pressure, 0x03, 4); break;
		case Write_Reg_FilterOrder: 		PRESSTXBuff_size = WriteUint16ToBUFF((uint8_t*)PRESSTXBuff, PressureAddress, Write_Reg_FilterOrder, PressureModule.FilterOrder); break;
	}

	//HAL_UART_Transmit_DMA(&huart8, (uint8_t*)"Test", 4);
	if(PRESS_modbus == 0) HAL_UART_Transmit(&huart7, (uint8_t*)PRESSTXBuff, PRESSTXBuff_size, 500);

	// Если в течении 3 секунд  не отвечает, все обнуляем
	if(++errcntr>=30)
	{
		errcntr=30;
		CalibrateChannel.Pressure_outer_temperature = 0;
		CalibrateChannel.Pressure_outer = 0;
	}

	ELSPIRE.sleep(100);
}

void UART_PRESSURE_Recieve_process(void)
{
	MX_TouchGFX_Process();

	if(TimeOutPressure == 0)
	{
		if(PRESS_modbus == 0)
		{
			if(PRESSURERXBuff[0] == PressureAddress && PRESSURERXBuff[1] == 0x03)
			{
				PRESSURERXBuff[0] = PRESSURERXBuff[1] = 0;

				switch(UART_PRESSURE_STATE)
				{
					case Read_Reg_Temperature_Sensor: 	CalibrateChannel.Pressure_outer_temperature = (double)TakeFloatFromBUFF((uint8_t*)PRESSURERXBuff, 3);
														UART_PRESSURE_STATE = Read_Reg_Pressure;
														break;

					case Read_Reg_Pressure: 			CalibrateChannel.Pressure_outer = (double)TakeFloatFromBUFF((uint8_t*)PRESSURERXBuff, 3);
														UART_PRESSURE_STATE = Read_Reg_Temperature_Sensor;
														break;

					case Read_Reg_ADC_0: 				PressureModule.ADC_0 = TakeINT32FromBUFF((uint8_t*)PRESSURERXBuff, 3); 			UART_PRESSURE_STATE = Read_Reg_ADC_1; break;
					case Read_Reg_ADC_1: 				PressureModule.ADC_1 = TakeINT32FromBUFF((uint8_t*)PRESSURERXBuff, 3); 			UART_PRESSURE_STATE = Read_Reg_Temperature; break;
					case Read_Reg_Temperature: 			PressureModule.Temperature = TakeFloatFromBUFF((uint8_t*)PRESSURERXBuff, 3); 	UART_PRESSURE_STATE = Read_Reg_Battery; break;
					case Read_Reg_Battery: 				PressureModule.Battery = TakeFloatFromBUFF((uint8_t*)PRESSURERXBuff, 3); 		UART_PRESSURE_STATE = Read_Reg_Temperature_Sensor; break;



					case Write_Reg_FilterRatio: 		CalibrateChannel.Pressure_outer = (double)TakeFloatFromBUFF((uint8_t*)PRESSURERXBuff, 3);
																		//UART_PRESSURE_STATE = Write_Reg_ZeroReg;
																		break;
				}
				errcntr = 0;
			}

			// Writing
			if(PRESSURERXBuff[0] == PressureAddress && PRESSURERXBuff[1] == 0x06)
			{
				switch(UART_PRESSURE_STATE)
				{
					case Write_Reg_ZeroReg: 	UART_PRESSURE_STATE = Read_Reg_Temperature_Sensor;
												CalibrateChannel.Pressure_outer_Zero = 0;
												break;
					case Write_Reg_FilterRatio: UART_PRESSURE_STATE = Write_Reg_FilterOrder; break;
					case Write_Reg_FilterOrder: UART_PRESSURE_STATE = Read_Reg_ADC_0; break;
				}
				errcntr = 0;
			}
		}
		else
		{
			CDC_Transmit_FS((uint8_t*)INRXBuff, pressurerxcntr);
			pressurerxcntr = 0;
		}
		TimeOutPressure=-1;
	}

	ELSPIRE.sleep(15);
}





void UART_PRESSURE_fastprocess(void)
{
	if(TimeOutPressure > 0)TimeOutPressure--;
	else if(TimeOutPressure==-1) { pressurerxcntr = 0; }
}
