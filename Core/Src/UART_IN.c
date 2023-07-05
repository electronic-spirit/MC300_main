
#include "UART_IN.h"
#include "string.h"
#include "app_touchgfx.h"
#include "usbd_cdc_if.h"

extern UART_HandleTypeDef huart5;
extern DMA_HandleTypeDef hdma_uart5_tx;



enum PressureState
{
	// 0x04
	Read_Reg_Voltage = 0x00,
	Read_Reg_Current = 0x02,
	Read_Reg_Freqency = 0x04,
	Read_Reg_Pulses = 0x06,
	Read_Reg_Multiply = 0x08,
	Read_Reg_Relay = 0x09,
	Read_Reg_Temperature = 0x0A,
	Read_Reg_V24 = 0x0D,
	// 0x03
	Write_Reg_MeasureMode = 0x01,
	//Read_Reg_State = 0x00,
	//Write_Reg_ResetCounter = 0x06
};



uint8_t INTXBuff[INTX_BUFFER_SIZE];
uint8_t INRXBuff[INRX_BUFFER_SIZE];
uint8_t INTXBuff_size = 0;
uint32_t inrxcntr = 0;
int16_t TimeOutIN = -1;
uint8_t UART_IN_STATE = Read_Reg_Voltage;
static uint8_t errcntr = 0;


struct INModuleStruct
{
	int32_t Voltage;
	int32_t Current;
	int32_t Frequency;
	int32_t Pulses;
	uint16_t Multiply;
	uint16_t Relay;
	int16_t Temperature;
	int32_t ADC;
	int16_t V24;
	uint16_t state;
};
struct INModuleStruct INModule;



void UART_IN_Transmit_process(void)
{
	MX_TouchGFX_Process();

	if((CalibrateChannel.ChangeParameter&IN_module_change) != 0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);

		switch(CalibrateChannel.Parameter_1)
		{
			case MeasureParameterVoltageMeasureIN: INModule.state = 1; break;
			case MeasureParameterCurrentMeasure: INModule.state = 2; break;
			case MeasureParameterFrequencyMeasure: INModule.state = 4; break;
			case MeasureParameterPulsesCounter: INModule.state = 5; break;
			case MeasureParameterRelayNormal:
			case MeasureParameterRelayInverted: INModule.state = 6; break;

			default: INModule.state = 0; break;
		}

		if(INModule.state == 0)
		{
			switch(CalibrateChannel.Parameter_2)
			{
				case MeasureParameterVoltageMeasureIN: INModule.state = 1; break;
				case MeasureParameterCurrentMeasure: INModule.state = 2; break;
				case MeasureParameterFrequencyMeasure: INModule.state = 4; break;
				case MeasureParameterPulsesCounter: INModule.state = 5; break;
				case MeasureParameterRelayNormal:
				case MeasureParameterRelayInverted: INModule.state = 6; break;
			}
		}
		UART_IN_STATE = Write_Reg_MeasureMode;
	}

	switch(UART_IN_STATE)
	{
		case Read_Reg_Voltage: 		INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Voltage, 0x04, 2); break;
		case Read_Reg_Current: 		INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Current, 0x04, 2); break;
		case Read_Reg_Freqency: 	INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Freqency, 0x04, 2); break;
		case Read_Reg_Pulses: 		INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Pulses, 0x04, 2); break;
		case Read_Reg_Multiply: 	INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Multiply, 0x04, 2); break;
		case Read_Reg_Relay: 		INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Relay, 0x04, 2); break;
		case Read_Reg_Temperature: 	INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_Temperature, 0x04, 2); break;
		case Read_Reg_V24: 			INTXBuff_size = RegisterRequest((uint8_t*)INTXBuff, IN_address, Read_Reg_V24, 0x04, 2); break;


		case Write_Reg_MeasureMode: INTXBuff_size = WriteUint16ToBUFF((uint8_t*)INTXBuff, IN_address, Write_Reg_MeasureMode, INModule.state); break;
	}

	//HAL_UART_Transmit_DMA(&huart4, (uint8_t*)test, 10);
	if(IN_modbus == 0) HAL_UART_Transmit(&huart5, (uint8_t*)INTXBuff, INTXBuff_size, 1000);

	// Если в течении 3 секунд  не отвечает, все обнуляем
	if(++errcntr>=30)
	{
		errcntr=30;
		CalibrateChannel.Current_DC = 0;
		CalibrateChannel.Voltage_IN = 0;
	}

	ELSPIRE.sleep(100);
}



void UART_IN_Recieve_process(void)
{
	MX_TouchGFX_Process();

	if(TimeOutIN == 0)
	{
		if(IN_modbus == 0)
		{
			if(INRXBuff[0] == IN_address && INRXBuff[1] == 0x04 && INRXBuff[2] == 0x04)
			{
				INRXBuff[0] = INRXBuff[1] = INRXBuff[2] = 0;

				switch(UART_IN_STATE)
				{
					case Read_Reg_Voltage: CalibrateChannel.Voltage_IN = (double)TakeINT32FromBUFF((uint8_t*)INRXBuff, 3); break;
					case Read_Reg_Current: CalibrateChannel.Current_DC = (double)TakeINT32FromBUFF((uint8_t*)INRXBuff, 3); break;
					case Read_Reg_Freqency: CalibrateChannel.Frequency = (double)TakeINT32FromBUFF((uint8_t*)INRXBuff, 3)*INModule.Multiply; break;
					case Read_Reg_Multiply: INModule.Multiply = TakeUINT16FromBUFF((uint8_t*)INRXBuff, 3); break;
					case Read_Reg_Relay: CalibrateChannel.Switch = TakeUINT16FromBUFF((uint8_t*)INRXBuff, 3); break;
				}

				switch(INModule.state)
				{
					case 1: UART_IN_STATE = Read_Reg_Voltage; break;
					case 2: UART_IN_STATE = Read_Reg_Current; break;
					case 5: UART_IN_STATE = Read_Reg_Pulses; break;
					case 6: UART_IN_STATE = Read_Reg_Relay; break;
					case 4:
						if(UART_IN_STATE == Read_Reg_Freqency) UART_IN_STATE = Read_Reg_Multiply;
						else UART_IN_STATE = Read_Reg_Freqency;
					break;
				}
				errcntr = 0;
			}

			if(INRXBuff[0] == IN_address && INRXBuff[1] == 0x06)
			{
				switch(UART_IN_STATE)
				{
					case Write_Reg_MeasureMode: UART_IN_STATE = Read_Reg_Voltage; CalibrateChannel.ChangeParameter &= ~IN_module_change;
					HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
					break;
				}
				errcntr = 0;
			}
		}
		else
		{
			CDC_Transmit_FS((uint8_t*)INRXBuff, inrxcntr);
			inrxcntr = 0;
		}


		TimeOutIN=-1;
	}


	ELSPIRE.sleep(15);
}





void UART_IN_fastprocess(void)
{
	if(TimeOutIN > 0)TimeOutIN--;
	else if(TimeOutIN == -1) { inrxcntr = 0; }
}
