
#ifndef INC_BMP390_H_
#define INC_BMP390_H_

#include "stm32h7xx_hal.h"
#include "main.h"


float Temperature_Read(void);
float Pressure_Read(void);
void BMP390_process(void);
uint8_t BMP390_Init(void);


#endif /* INC_BMP390_H_ */
