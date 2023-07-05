
#ifndef INC_UART_PRESSURE_H_
#define INC_UART_PRESSURE_H_

#include "stm32h7xx_hal.h"
#include "main.h"

#define PRESSURETX_BUFFER_SIZE		50
#define PRESSURERX_BUFFER_SIZE 		100
#define TimeOutConstPRESSURE		10

void UART_PRESSURE_Transmit_process(void);
void UART_PRESSURE_Recieve_process(void);
void UART_PRESSURE_fastprocess(void);


extern uint32_t pressurerxcntr;
extern uint8_t PRESSTXBuff[PRESSURETX_BUFFER_SIZE];
extern uint8_t PRESSURERXBuff[PRESSURERX_BUFFER_SIZE];
extern int16_t TimeOutPressure;




#endif /* INC_UART_PRESSURE_H_ */
