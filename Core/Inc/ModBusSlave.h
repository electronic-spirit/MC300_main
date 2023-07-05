
#ifndef INC_MODBUSSLAVE_H_
#define INC_MODBUSSLAVE_H_

#include "stm32h7xx_hal.h"
#include "main.h"



#define		Version											0					// Версия прошивки
#define		write_read_flash								1					// 1 - записать константы на флэш память, 2 - прочитать из памяти
#define		encoder_data									7					// данные с энкодера
#define		rotate											10					// в какую сторону вращается энкодер
#define		clean_speed										2					// Скорость вращения без усреднения
#define		ask_period										3					// Частота опроса, mS
#define		midle_speed										4					// Скорость вращения
#define		CPU												5					// Загруженность процессора
#define		Speed_H											8
#define		Speed_L											9
#define		Quant											11

#define 	my_address			0xEB
#define 	USB_TimeOut_Const	5
#define 	RXTX_BUFFER_SIZE	60


extern unsigned short				REG[];
extern unsigned char      			host_request[RXTX_BUFFER_SIZE];
extern volatile signed char         USB_TimeOut;
extern uint32_t rxcntr;


void Init_modbus(void);

void process_modbus(void);
void process_modbus_fast(void);

double ReadDoubleFromREG(uint16_t regnum);
void WriteDoubleToREG(uint16_t regnum, double Data);
void WriteFloatToREG(uint16_t regnum, float Data);
void WriteInt32ToREG(uint16_t regnum, int32_t Data);


uint16_t crc16(uint8_t *array, uint8_t offset, uint8_t lenght);


#endif /* INC_MODBUSSLAVE_H_ */
