
#ifndef INC_UART_OUT_H_
#define INC_UART_OUT_H_

#include "stm32h7xx_hal.h"
#include "main.h"

#define OUTTX_BUFFER_SIZE 	50
#define OUTRX_BUFFER_SIZE 	100
#define TimeOutConst		10

void UART_OUT_Transmit_process(void);
void UART_OUT_Recieve_process(void);
void UART_OUT_fastprocess(void);


extern uint32_t outrxcntr;
extern uint8_t OUTRXBuff[OUTRX_BUFFER_SIZE];
extern uint8_t OUTTXBuff[OUTTX_BUFFER_SIZE];
extern int16_t TimeOut;

#endif /* INC_UART_OUT_H_ */
