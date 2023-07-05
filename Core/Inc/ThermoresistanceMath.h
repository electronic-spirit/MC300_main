/*
 * ThermoresistanceMath.h
 *
 *  Created on: 22 июн. 2023 г.
 *      Author: agapov
 */

#ifndef INC_THERMORESISTANCEMATH_H_
#define INC_THERMORESISTANCEMATH_H_


#include "main.h"
#include "stm32h7xx_hal.h"


// Thermoresistance wire schematic
enum ThermoresistanceWireSchematic
{
	Thermoresistance2Wire,
	Thermoresistance3Wire,
	Thermoresistance4Wire,
};


// Thermoresistance wire schematic
enum ThermoresistanceType
{
	ThermoresistancePT,
	ThermoresistanceCU,
	ThermoresistanceNI,
};



extern const double PT385[7];
extern const double PT391[7];
extern const double CU428[7];
extern const double CU426[7];
extern const double NI617[7];
extern double USER_TR[7];


/* Exported struct -----------------------------------------------------------*/
struct ThermoresistanceMath
{
	double (*PT_direct)(double degree, double R0, const double*PT);
	double (*PT_inverse)(double resistance, double R0, const double*PT);
	double (*CU_direct)(double degree, double R0, const double*CU);
	double (*CU_inverse)(double resistance, double R0, const double*CU);
	double (*NI_direct)(double degree, double R0, const double*NI);
	double (*NI_inverse)(double resistance, double R0, const double*NI);
};
extern struct ThermoresistanceMath Thermoresistance;


#endif /* INC_THERMORESISTANCEMATH_H_ */
