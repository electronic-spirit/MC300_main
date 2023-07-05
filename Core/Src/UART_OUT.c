

#include "UART_OUT.h"
#include "string.h"
#include "app_touchgfx.h"
#include "usbd_cdc_if.h"


extern UART_HandleTypeDef huart4;
extern DMA_HandleTypeDef hdma_uart4_tx;



enum OutState
{
	Read_Reg_U_TC1 = 12,					// Напряжение на термопаре TC1, В
	Read_Reg_U_TC2 = 14,					// Напряжение на термопаре TC2, В
	Read_Reg_TXC_TC1 = 16,					// Температура холодного спая TC1, °С
	Read_Reg_TXC_TC2 = 18,					// Температура холодного спая TC2, °С
	Read_Reg_R1_4 = 20,						// Сопротивление R1, Ом
	Read_Reg_R2_4 = 22,						// Сопротивление R2, Ом
	Read_Reg_R1_2 = 24,						// Сопротивление R1, Ом
	Read_Reg_R2_2 = 26,						// Сопротивление R2, Ом
	Read_Reg_R1_3 = 28,						// Сопротивление R1, Ом
	Read_Reg_R2_3 = 30,						// Сопротивление R2, Ом

	Read_Reg_R_mode = 38,					// Режим измерения сопртивления

	Write_Reg_TC1_SET = 42,					// Уставка ТП TC1, В
	Write_Reg_U_SET = 44,					// Уставка напряжения U, В
	Write_Reg_I_SET = 46,					// Уставка тока I, мА
	Write_Reg_R1_SET = 48,					// Уставка сопротивления R1, Ом
	Write_Reg_Set_Pulse_Len = 50,			// Уставка длительности импульса, uS
	Write_Reg_Set_Pause_Len = 52,			// Уставка длительности паузы, uS
	Write_Reg_Set_P_count = 54,				// Уставка количества импульсов (N)
	Write_Reg_Frequency = 56,				// Уставка Частоты, Гц
	Write_Reg_DutyCycle = 58,				// Скважность (%)

	Write_Reg_Meas_Mode = 10,				// Режим работы
	Write_Reg_Emul_Mode = 40,				// Тип эмуляции
};


uint8_t OUTTXBuff[OUTTX_BUFFER_SIZE];
uint8_t OUTRXBuff[OUTRX_BUFFER_SIZE];
uint8_t OUTTXBuff_size = 0;
uint32_t outrxcntr = 0;
int16_t TimeOut = -1;
uint8_t UART_OUT_STATE = Read_Reg_U_TC1;
static uint8_t errcntr = 0;


struct OUTModuleStruct
{
	uint16_t MeasureMode;
	float ControlCurrent;
	float U_ThermoCoupleTC1;
	float U_ThermoCoupleTC2;
	float R1_2W;
	float R1_3W;
	float R1_4W;
	float R2_2W;
	float R2_3W;
	float R2_4W;
	uint16_t EmulatorMode;
	float Set_U_Thermocouple;
	float Set_U;
	float Set_I;
	float Set_R;
	float Set_Period;
	float Set_PulseCounter;
	float Set_DutyCicle;
	float TXC_TC1;
	float TXC_TC2;

	uint16_t mode_state;
	uint16_t emul_state;
	uint16_t R_mode;
};
struct OUTModuleStruct OUTModule;




void UART_OUT_Transmit_process(void)
{
	MX_TouchGFX_Process();

		if((CalibrateChannel.ChangeParameter&OUT_module_change) != 0)
		{
			OUTModule.emul_state = 0;
			OUTModule.mode_state = 0;

			switch(CalibrateChannel.Parameter_1)
			{
				// Measure
				case MeasureParameterThermoCoupleMeasureTC1: 	OUTModule.mode_state = 0x0001; break;
				case MeasureParameterThermoCoupleMeasureTC2: 	OUTModule.mode_state = 0x0002; break;
				case MeasureParameterResistanceMeasureR1: 		OUTModule.mode_state = 0x0004; break;
				case MeasureParameterResistanceMeasureR2: 		OUTModule.mode_state = 0x0008; break;
				case MeasureParameterThermoResistanceMeasureR1: OUTModule.mode_state = 0x0004; break;
				case MeasureParameterThermoResistanceMeasureR2: OUTModule.mode_state = 0x0008; break;
				case MeasureParameterVoltageMeasureTC1: 		OUTModule.mode_state = 0x0001; break;
				case MeasureParameterVoltageMeasureTC2: 		OUTModule.mode_state = 0x0002; break;

				// Generate
				case MeasureParameterThermoCoupleGenerate:
				case MeasureParameterVoltageGenerateTC1: 		OUTModule.mode_state = 0x0010; OUTModule.emul_state = 0x0001; break;
				case MeasureParameterVoltageGenerateOUT: 		OUTModule.mode_state = 0x0010; OUTModule.emul_state = 0x0002; break;
				case MeasureParameterCurrentGenerate: 			OUTModule.mode_state = 0x0010;
																if(CalibrateChannel.Power12 == 0) {OUTModule.emul_state = 0x0004;}
																else {OUTModule.emul_state = 0x0003;} break;

				case MeasureParameterThermoResistanceGenerate:
				case MeasureParameterResistanceGenerate: 		OUTModule.mode_state = 0x0010;
																if(CalibrateChannel.Generate_Resistance < 400) OUTModule.emul_state = 0x0005;
																else OUTModule.emul_state = 0x0006;
																break;


				case MeasureParameterPulsesGenerate: 			OUTModule.mode_state = 0x0010;
																if(CalibrateChannel.FrequencyForm == 0) OUTModule.emul_state = 0x0007;
																else OUTModule.emul_state = 0x0008;
																break;
				case MeasureParameterFrequencyGenerate: 		OUTModule.mode_state = 0x0200;
																if(CalibrateChannel.FrequencyForm == 0) OUTModule.emul_state = 0x0009;
																else OUTModule.emul_state = 0x000A;
																break;
			}

			switch(CalibrateChannel.Parameter_2)
			{
				// Measure
				case MeasureParameterThermoCoupleMeasureTC1: 	OUTModule.mode_state |= 0x0001; break;
				case MeasureParameterThermoCoupleMeasureTC2: 	OUTModule.mode_state |= 0x0002; break;
				case MeasureParameterResistanceMeasureR1: 		OUTModule.mode_state |= 0x0004; break;
				case MeasureParameterResistanceMeasureR2: 		OUTModule.mode_state |= 0x0008; break;
				case MeasureParameterThermoResistanceMeasureR1: OUTModule.mode_state |= 0x0004; break;
				case MeasureParameterThermoResistanceMeasureR2: OUTModule.mode_state |= 0x0008; break;
				case MeasureParameterVoltageMeasureTC1: 		OUTModule.mode_state |= 0x0001; break;
				case MeasureParameterVoltageMeasureTC2: 		OUTModule.mode_state |= 0x0002; break;
			}

			if(OUTModule.emul_state == 0)
			{
				switch(CalibrateChannel.Parameter_2)
				{
					// Generate
					case MeasureParameterThermoCoupleGenerate:
					case MeasureParameterVoltageGenerateTC1: 		OUTModule.mode_state |= 0x0010; OUTModule.emul_state = 0x0001; break;
					case MeasureParameterVoltageGenerateOUT: 		OUTModule.mode_state |= 0x0010; OUTModule.emul_state = 0x0002; break;
					case MeasureParameterCurrentGenerate: 			OUTModule.mode_state |= 0x0010;
																	if(CalibrateChannel.Power12 == 0) {OUTModule.emul_state = 0x0004;}
																	else {OUTModule.emul_state = 0x0003;} break;

					case MeasureParameterThermoResistanceGenerate:
					case MeasureParameterResistanceGenerate: 		OUTModule.mode_state |= 0x0010;
																	if(CalibrateChannel.Generate_Resistance < 400) OUTModule.emul_state = 0x0005;
																	else OUTModule.emul_state = 0x0006;
																	break;


					case MeasureParameterPulsesGenerate: 			OUTModule.mode_state = 0x0010;
																	if(CalibrateChannel.FrequencyForm == 0) OUTModule.emul_state = 0x0007;
																	else OUTModule.emul_state = 0x0008;
																	break;
					case MeasureParameterFrequencyGenerate: 		OUTModule.mode_state = 0x0200;
																	if(CalibrateChannel.FrequencyForm == 0) OUTModule.emul_state = 0x0009;
																	else OUTModule.emul_state = 0x000A;
																	break;
				}
			}
			UART_OUT_STATE = Write_Reg_Meas_Mode;
		}

		// Request
		switch(UART_OUT_STATE)
		{
			case Read_Reg_U_TC1: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_U_TC1, 0x03, 2); break;
			case Read_Reg_U_TC2: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_U_TC2, 0x03, 2); break;
			case Read_Reg_TXC_TC1: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_TXC_TC1, 0x03, 2); break;
			case Read_Reg_TXC_TC2: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_TXC_TC2, 0x03, 2); break;
			case Read_Reg_R1_2: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R1_2, 0x03, 2); break;
			case Read_Reg_R1_3: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R1_3, 0x03, 2); break;
			case Read_Reg_R1_4: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R1_4, 0x03, 2); break;
			case Read_Reg_R2_2: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R2_2, 0x03, 2); break;
			case Read_Reg_R2_3: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R2_3, 0x03, 2); break;
			case Read_Reg_R2_4: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R2_4, 0x03, 2); break;
			case Read_Reg_R_mode: 			OUTTXBuff_size = RegisterRequest((uint8_t*)OUTTXBuff, OUT_address, Read_Reg_R_mode, 0x03, 2); break;

			case Write_Reg_TC1_SET: 		OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_TC1_SET, (float)CalibrateChannel.Generate_VoltageTC1); break;
			case Write_Reg_U_SET: 			OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_U_SET, (float)CalibrateChannel.Generate_VoltageOUT); break;
			case Write_Reg_I_SET: 			OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_I_SET, (float)CalibrateChannel.Generate_Current); break;
			case Write_Reg_R1_SET: 			OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_R1_SET, (float)CalibrateChannel.Generate_Resistance); break;
			case Write_Reg_Set_Pulse_Len:	OUTTXBuff_size = WriteUint32ToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Set_Pulse_Len, (uint32_t)CalibrateChannel.Generate_Pulse_Len); break;
			case Write_Reg_Set_Pause_Len: 	OUTTXBuff_size = WriteUint32ToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Set_Pause_Len, (uint32_t)CalibrateChannel.Generate_Pulse_Pause_Len); break;
			case Write_Reg_Set_P_count: 	OUTTXBuff_size = WriteUint32ToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Set_P_count, (uint32_t)CalibrateChannel.Generate_Pulse); break;
			case Write_Reg_Frequency: 		OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Frequency, (float)CalibrateChannel.Generate_Frequency); break;
			case Write_Reg_DutyCycle: 		OUTTXBuff_size = WriteFloatToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_DutyCycle, (float)CalibrateChannel.FrequencyDutyCycle); break;
			case Write_Reg_Meas_Mode: 		OUTTXBuff_size = WriteUint16ToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Meas_Mode, OUTModule.mode_state); break;
			case Write_Reg_Emul_Mode: 		OUTTXBuff_size = WriteUint16ToBUFF((uint8_t*)OUTTXBuff, OUT_address, Write_Reg_Emul_Mode, OUTModule.emul_state); break;
		}

		if(OUT_modbus == 0) HAL_UART_Transmit(&huart4, (uint8_t*)OUTTXBuff, OUTTXBuff_size, 1000);

		// Если в течении 3 секунд  не отвечает, все обнуляем
		if(++errcntr>=30)
		{
			errcntr=30;

		}

		REG[10] = (uint16_t)UART_OUT_STATE;
		ELSPIRE.sleep(100);
}



void UART_OUT_Recieve_process(void)
{
	MX_TouchGFX_Process();

	if(TimeOut == 0)
	{
		if(OUT_modbus == 0)
		{
			if(OUTRXBuff[0] == OUT_address && OUTRXBuff[1] == 0x03 && OUTRXBuff[2] == 0x04)
			{
				OUTRXBuff[0] = OUTRXBuff[1] = OUTRXBuff[2] = 0;

				switch(UART_OUT_STATE)
				{
					case Read_Reg_U_TC1: 	CalibrateChannel.Voltage_TC1 = (double)TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_U_TC2; break;
					case Read_Reg_U_TC2: 	CalibrateChannel.Voltage_TC2 = (double)TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_TXC_TC1; break;
					case Read_Reg_TXC_TC1: 	CalibrateChannel.TXC_TC1 = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_TXC_TC2; break;
					case Read_Reg_TXC_TC2: 	CalibrateChannel.TXC_TC1 = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R1_2; break;
					case Read_Reg_R1_2: 	OUTModule.R1_2W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R1_3; break;
					case Read_Reg_R1_3: 	OUTModule.R1_3W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R1_4; break;
					case Read_Reg_R1_4: 	OUTModule.R1_4W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R2_2; break;
					case Read_Reg_R2_2: 	OUTModule.R2_2W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R2_3; break;
					case Read_Reg_R2_3: 	OUTModule.R2_3W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R2_4; break;
					case Read_Reg_R2_4: 	OUTModule.R2_4W = TakeFloatFromBUFF((uint8_t*)OUTRXBuff, 3); UART_OUT_STATE = Read_Reg_R_mode; break;
					case Read_Reg_R_mode:	OUTModule.R_mode = TakeUINT16FromBUFF((uint8_t*)OUTRXBuff, 3); OUTModule.R_mode>>=6; UART_OUT_STATE = Read_Reg_U_TC1; break;
				}

				switch(OUTModule.R_mode)
				{
					case 0x00: CalibrateChannel.Resistance_R1 = OUTModule.R1_2W; CalibrateChannel.Resistance_R2 = OUTModule.R2_2W;  break; // R1 2w, R2 2w
					case 0x01: CalibrateChannel.Resistance_R1 = OUTModule.R1_3W; CalibrateChannel.Resistance_R2 = OUTModule.R2_2W;  break; // R1 3w, R2 2w
					case 0x03: CalibrateChannel.Resistance_R1 = OUTModule.R1_4W; CalibrateChannel.Resistance_R2 = OUTModule.R2_2W;  break; // R1 4w, R2 2w
					case 0x04: CalibrateChannel.Resistance_R1 = OUTModule.R1_2W; CalibrateChannel.Resistance_R2 = OUTModule.R2_3W;  break; // R1 2w, R2 3w
					case 0x05: CalibrateChannel.Resistance_R1 = OUTModule.R1_3W; CalibrateChannel.Resistance_R2 = OUTModule.R2_3W;  break; // R1 3w, R2 3w
					case 0x07: CalibrateChannel.Resistance_R1 = OUTModule.R1_4W; CalibrateChannel.Resistance_R2 = OUTModule.R2_3W;  break; // R1 4w, R2 3w
					case 0x0C: CalibrateChannel.Resistance_R1 = OUTModule.R1_2W; CalibrateChannel.Resistance_R2 = OUTModule.R2_4W;  break; // R1 2w, R2 4w
					case 0x0D: CalibrateChannel.Resistance_R1 = OUTModule.R1_3W; CalibrateChannel.Resistance_R2 = OUTModule.R2_4W;  break; // R1 3w, R2 4w
					case 0x0F: CalibrateChannel.Resistance_R1 = OUTModule.R1_4W; CalibrateChannel.Resistance_R2 = OUTModule.R2_4W;  break; // R1 4w, R2 4w
				}

				errcntr = 0;
			}

			if(OUTRXBuff[0] == OUT_address && OUTRXBuff[1] == 0x06)
			{
				switch(UART_OUT_STATE)
				{
					case Write_Reg_Meas_Mode: UART_OUT_STATE = Write_Reg_Emul_Mode; CalibrateChannel.ChangeParameter &= ~OUT_module_change; break;
					case Write_Reg_Emul_Mode: UART_OUT_STATE = Write_Reg_TC1_SET; break;
				}
				errcntr = 0;
			}

			if(OUTRXBuff[0] == OUT_address && (OUTRXBuff[1] == 0x10 || OUTRXBuff[1] == 10))
			{
				switch(UART_OUT_STATE)
				{
					case Write_Reg_TC1_SET: UART_OUT_STATE = Write_Reg_U_SET; break;
					case Write_Reg_U_SET: UART_OUT_STATE = Write_Reg_I_SET; break;
					case Write_Reg_I_SET: UART_OUT_STATE = Write_Reg_R1_SET; break;
					case Write_Reg_R1_SET: UART_OUT_STATE = Write_Reg_Set_Pulse_Len; break;
					case Write_Reg_Set_Pulse_Len: UART_OUT_STATE = Write_Reg_Set_Pause_Len; break;
					case Write_Reg_Set_Pause_Len: UART_OUT_STATE = Write_Reg_Set_P_count; break;
					case Write_Reg_Set_P_count: UART_OUT_STATE = Write_Reg_Frequency; break;
					case Write_Reg_Frequency: UART_OUT_STATE = Write_Reg_DutyCycle; break;
					case Write_Reg_DutyCycle: UART_OUT_STATE = Read_Reg_U_TC1; break;
				}
				errcntr = 0;
			}
		}
		else
		{
			CDC_Transmit_FS((uint8_t*)OUTRXBuff, outrxcntr);
			outrxcntr = 0;
		}

		TimeOut=-1;
	}


	ELSPIRE.sleep(15);
}





void UART_OUT_fastprocess(void)
{
	if(TimeOut > 0)TimeOut--;
	else if(TimeOut == -1){  outrxcntr = 0; }
}






