
#ifndef INC_UNITS_H_
#define INC_UNITS_H_


#include "stm32h7xx_hal.h"
#include "main.h"


double ConvertUnit_Pressure(uint16_t unitFrom, uint16_t unitTo, double data);
double ConvertUnit_Voltage(uint16_t unitFrom, uint16_t unitTo, double data);
double ConvertUnit_Current(uint16_t unitFrom, uint16_t unitTo, double data);
double ConvertUnit_Temperature(uint16_t unitFrom, uint16_t unitTo, double data);
double ConvertUnit_Frequency(uint16_t unitFrom, uint16_t unitTo, double data);
double ConvertUnit_Resistance(uint16_t unitFrom, uint16_t unitTo, double data);




#endif /* INC_UNITS_H_ */
