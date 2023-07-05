
#include "ModBusSlave.h"
#include "usbd_cdc_if.h"
#include "app_touchgfx.h"

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart7;
extern UART_HandleTypeDef huart4;

uint8_t host_request[RXTX_BUFFER_SIZE];
uint8_t  __attribute__((section(".ExtRAM")))    host_answer[RXTX_BUFFER_SIZE];
uint8_t      h_answer_counter = 0;
volatile signed char USB_TimeOut = -1;
uint8_t      	ra,rb;
uint16_t __attribute__((section(".ExtRAM"))) REG[400];
//uint32_t rxcntr = 0;



// Prototypes
void read_reg(unsigned short i);
unsigned short read_reg16(unsigned short i);
void write_reg(unsigned short i, unsigned char a, unsigned char b); //a-MSB  b-LSB
void write_reg16(unsigned short i, unsigned short val);
void mb_03_read_holding_register(void);
void mb_06_preset_single_register(void);
void mb_10_preset_multiple(void);
void say_to_host(void);


//--------------------------------------------------------------------------------------------
//									CRC16
//--------------------------------------------------------------------------------------------

uint16_t crc16(uint8_t *array, uint8_t offset, uint8_t lenght)
{
	unsigned char i,j,b,al;
	unsigned int b1;

	b1 = 0xffff;
	for (i = offset; i < (lenght + offset); i++)
	{
		b = array[i];
		for (j = 1; j < 9; j++)
		{
			al = b1 & 0x00ff;
			al = al ^ b;
			if ((al & 0x01) != 0)
			{
				b1 = b1 ^ 0x4002;
				b1 = b1 >> 1;
				b1 = b1 | 0x8000;
			}
			else b1 = b1 >> 1;
			b = b >> 1;
		}
	}
	return b1;
}

//--------------------------------------------------------------------------------------------
//									Инициализация USART1 для связи с HOST
//--------------------------------------------------------------------------------------------

void Init_modbus(void)
{
	host_request[0] = 0;
	USB_TimeOut = -1;
	REG[0] = 12345;

	IN_modbus = 0;
	OUT_modbus = 0;
	PRESS_modbus = 0;
}

double ReadDoubleFromREG(uint16_t regnum)
{
	uint8_t testbuf[8];
	double res;
	testbuf[0] = REG[regnum+3]&0xFF;
	testbuf[1] = REG[regnum+3]>>8;
	testbuf[2] = REG[regnum+2]&0xFF;
	testbuf[3] = REG[regnum+2]>>8;
	testbuf[4] = REG[regnum+1]&0xFF;
	testbuf[5] = REG[regnum+1]>>8;
	testbuf[6] = REG[regnum]&0xFF;
	testbuf[7] = REG[regnum]>>8;

	memcpy(&res, testbuf, 8);
	return res;
}

void WriteDoubleToREG(uint16_t regnum, double Data)
{
	uint8_t testbuf[8];
	memcpy(testbuf, &Data, 8);
	REG[regnum+3] = testbuf[1]*256 + testbuf[0];
	REG[regnum+2] = testbuf[3]*256 + testbuf[2];
	REG[regnum+1] = testbuf[5]*256 + testbuf[4];
	REG[regnum] = testbuf[7]*256 + testbuf[6];
}

void WriteFloatToREG(uint16_t regnum, float Data)
{
	uint8_t testbuf[4];
	memcpy(testbuf, &Data, 4);
	REG[regnum+1] = testbuf[1]*256 + testbuf[0];
	REG[regnum] = testbuf[3]*256 + testbuf[2];
}

void WriteInt32ToREG(uint16_t regnum, int32_t Data)
{
	uint8_t testbuf[4];
	memcpy(testbuf, &Data, 4);
	REG[regnum+1] = (testbuf[1]<<8) | testbuf[0];
	REG[regnum] = (testbuf[3]<<8) | testbuf[2];
}

//--------------------------------------------------------------------------------------------
//													Обработка полученных данных
//--------------------------------------------------------------------------------------------

void process_modbus(void)
{
	MX_TouchGFX_Process();

	int i = 0;
	int crc16_result = 0;

	if(USB_TimeOut == 0)
	{
		if (host_request[1] == my_address)
		{
			crc16_result = (host_request[host_request[0]]<<8) | host_request[host_request[0] - 1];
			if (crc16_result == crc16(host_request, 1, (host_request[0] - 2)))
			{
				switch (host_request[2])
				{
					case 0x09: for (i = 0; i < (host_request[0]+1); i++) {host_answer[i] = host_request[i];} break;
					case 0x03: mb_03_read_holding_register(); break;
					case 0x06: mb_06_preset_single_register(); break;
					case 0x10: mb_10_preset_multiple(); break;
					default :
										host_request[2] = 0;
										host_request[1] = 0;
										host_request[0] = 0;
					return;
				}
				CDC_Transmit_FS((uint8_t*)host_answer+1, host_answer[0]);
			}
		}
		else if(host_request[1]=='I' && host_request[2]=='N' && host_request[3]=='_' && host_request[4]=='O' && host_request[5]=='N')
		{
			IN_modbus = 1;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}
		else if(host_request[1]=='I' && host_request[2]=='N' && host_request[3]=='_' && host_request[4]=='O' && host_request[5]=='F' && host_request[6]=='F')
		{
			IN_modbus = 0;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}
		else if(host_request[1]=='O' && host_request[2]=='U' && host_request[3]=='T' && host_request[4]=='_' && host_request[5]=='O' && host_request[6]=='N')
		{
			OUT_modbus = 1;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}
		else if(host_request[1]=='O' && host_request[2]=='U' && host_request[3]=='T' && host_request[4]=='_' && host_request[5]=='O' && host_request[6]=='F' && host_request[7]=='F')
		{
			OUT_modbus = 0;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}
		else if(host_request[1]=='P' && host_request[2]=='R' && host_request[3]=='E' && host_request[4]=='S' && host_request[5]=='S' && host_request[6]=='_'  && host_request[7]=='O'  && host_request[8]=='N')
		{
			PRESS_modbus = 1;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}
		else if(host_request[1]=='P' && host_request[2]=='R' && host_request[3]=='E' && host_request[4]=='S' && host_request[5]=='S' && host_request[6]=='_'  && host_request[7]=='O'  && host_request[8]=='F'  && host_request[9]=='F')
		{
			PRESS_modbus = 0;
			CDC_Transmit_FS((uint8_t*)"OK\n", 3);
		}

		// IN module
		if(IN_modbus == 1)
		{
			if (host_request[1] == IN_address)
			{
				crc16_result = (host_request[host_request[0]]<<8) | host_request[host_request[0] - 1];
				if (crc16_result == crc16(host_request, 1, (host_request[0] - 2)))
				{
					for(uint8_t i = 0;i<host_request[0];i++)
						INTXBuff[i] = host_request[i+1];
					HAL_UART_Transmit(&huart5, (uint8_t*)INTXBuff, host_request[0], 1000);
				}
			}
		}
		// PRESS module
		if(PRESS_modbus == 1)
		{
			if (host_request[1] == PressureAddress)
			{
				crc16_result = (host_request[host_request[0]]<<8) | host_request[host_request[0] - 1];
				if (crc16_result == crc16(host_request, 1, (host_request[0] - 2)))
				{
					for(uint8_t i = 0;i<host_request[0];i++)
						PRESSTXBuff[i] = host_request[i+1];
					HAL_UART_Transmit(&huart7, (uint8_t*)PRESSTXBuff, host_request[0], 1000);
				}
			}
		}
		// OUT module
		if(OUT_modbus == 1)
		{
			if (host_request[1] == OUT_address)
			{
				crc16_result = (host_request[host_request[0]]<<8) | host_request[host_request[0] - 1];
				if (crc16_result == crc16(host_request, 1, (host_request[0] - 2)))
				{
					for(uint8_t i = 0;i<host_request[0];i++)
						OUTTXBuff[i] = host_request[i+1];
					HAL_UART_Transmit(&huart4, (uint8_t*)OUTTXBuff, host_request[0], 1000);
				}
			}
		}


		host_request[1] = 0;
		host_request[0] = 0;
		USB_TimeOut = -1;
	}

	ELSPIRE.sleep(5);
}



//--------------------------------------------------------------------------------------------
//						          Читаем спидлисты
//--------------------------------------------------------------------------------------------

void read_reg(uint16_t i)
{ rb = (uint8_t)REG[i]; ra = (uint8_t)(REG[i]>>8); }


//--------------------------------------------------------------------------------------------
//							    Записываем в регистр
//--------------------------------------------------------------------------------------------

void write_reg(uint16_t i, uint8_t hi, uint8_t lo)
{ REG[i] = hi*256 + lo; }


//--------------------------------------------------------------------------------------------
//		       Читаем начиная с определенного регистра несколько значений
//--------------------------------------------------------------------------------------------

void mb_03_read_holding_register(void)
{
	int sa0, sa1, i;

	sa0 = host_request[3]*256 + host_request[4];
	sa1 = host_request[5]*256 + host_request[6];
	if((sa0 < 400)&(sa1 < 50) & ((sa1 + sa0) < 398))
	{
		host_answer[1] = my_address;
		host_answer[2] = 3;
		host_answer[3] = sa1*2;
		for (i = sa0; i < (sa0 + sa1 + 1); i++)
		{
			read_reg(i);
			host_answer[2*(i-sa0)+4]  = ra;
			host_answer[2*(i-sa0)+4+1] = rb;
		}
		host_answer[0] = sa1*2 + 3;
		host_answer[host_answer[0]+2] = crc16(host_answer, 1, host_answer[0])>>8;
		host_answer[host_answer[0]+1] = crc16(host_answer, 1, host_answer[0])&0xFF;
		host_answer[0] = sa1*2 + 3 + 2;
	}
	else
	{
		host_answer[0] = 0;
		host_answer[host_answer[0]+2] = crc16(host_answer, 1, host_answer[0])>>8;
		host_answer[host_answer[0]+1] = crc16(host_answer, 1, host_answer[0])&0xFF;
	}
}

//--------------------------------------------------------------------------------------------
//							Команда записи в регистр
//--------------------------------------------------------------------------------------------

void mb_06_preset_single_register(void)
{
	uint16_t sa0;

	sa0 = host_request[3]*256 + host_request[4];
	if((sa0 < 400))
	{
		write_reg(sa0, host_request[5], host_request[6]);
		host_answer[1] = my_address;
		host_answer[2] = 6;
		host_answer[3] = host_request[3];
		host_answer[4] = host_request[4];
		host_answer[5] = host_request[5];
		host_answer[6] = host_request[6];
		host_answer[7] = host_request[7];
		host_answer[8] = host_request[8];
		host_answer[0] = 8;
	}
	else
	{
		host_answer[0] = 0;
		host_answer[1] = crc16(host_answer, 1, host_answer[0])>>8;
		host_answer[2] = crc16(host_answer, 1, host_answer[0])&0xFF;
	}
}


//--------------------------------------------------------------------------------------------
//							Команда записи по нескольким регистрам
//--------------------------------------------------------------------------------------------

void mb_10_preset_multiple(void)
{
	uint16_t sa0, sa1, i;

	sa0 = host_request[3]*256 + host_request[4];
	sa1 = host_request[5]*256 + host_request[6];
	host_answer[1] = my_address;
	host_answer[2] = 0x10;
	host_answer[3] = host_request[3];
	host_answer[4] = host_request[4];
	host_answer[5] = host_request[5];
	host_answer[6] = host_request[6];

	for (i = sa0; i < (sa0 + sa1); i++)
	{ write_reg(i, host_request[2*(i-sa0) + 7], host_request[2*(i-sa0) + 8]); }

	host_answer[0] = 6;
	host_answer[host_answer[0]+1] = crc16(host_answer, 1, host_answer[0])>>8;
	host_answer[host_answer[0]+2] = crc16(host_answer, 1, host_answer[0])&0xFF;
	host_answer[0] = 8;
}



//--------------------------------------------------------------------------------------------
//							Читаем регистры
//--------------------------------------------------------------------------------------------

unsigned short read_reg16(unsigned short i)
{ return REG[i];}

//--------------------------------------------------------------------------------------------
//							Записываем в регистры
//--------------------------------------------------------------------------------------------

void write_reg16(unsigned short i, unsigned short val)
{ REG[i] = val; }


//--------------------------------------------------------------------------------------------
//							 Считаем таймаут
//--------------------------------------------------------------------------------------------

void process_modbus_fast(void)
{
	if (USB_TimeOut > 0)
	{ USB_TimeOut--; }
	//else {rxcntr=host_request[0];host_request[0] = 0;}
}
