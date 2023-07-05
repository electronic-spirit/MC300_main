
#ifndef INC_UART_IN_H_
#define INC_UART_IN_H_

#include "stm32h7xx_hal.h"
#include "main.h"

#define INRX_BUFFER_SIZE 	100
#define INTX_BUFFER_SIZE 	50
#define TimeOutConstIN		10

void UART_IN_Transmit_process(void);
void UART_IN_Recieve_process(void);
void UART_IN_fastprocess(void);


extern uint32_t inrxcntr;
extern uint8_t INRXBuff[INRX_BUFFER_SIZE];
extern uint8_t INTXBuff[INTX_BUFFER_SIZE];
extern int16_t TimeOutIN;




#endif /* INC_UART_IN_H_ */
