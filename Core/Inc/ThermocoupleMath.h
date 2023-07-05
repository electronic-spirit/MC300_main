/*
 * ThermocoupleMath.h
 *
 *  Created on: Jun 16, 2023
 *      Author: agapov
 */

#ifndef INC_THERMOCOUPLEMATH_H_
#define INC_THERMOCOUPLEMATH_H_

#include "main.h"
#include "stm32h7xx_hal.h"


enum TC_Type
{
	Type_J,
	Type_K,
	Type_E,
	Type_T,
	Type_N,
	Type_B,
	Type_S,
	Type_R,
	Type_L,
	Type_M,
	Type_A1,
	Type_A2,
	Type_A3
};



/* Exported struct -----------------------------------------------------------*/
struct ThermocoupleMath
{
	// Type_J
	double (*Type_J_direct)(double degree);
	double (*Type_J_inverse)(double microvolts);
	// Type K
	double (*Type_K_direct)(double degree);
	double (*Type_K_inverse)(double microvolts);
	// Type T
	double (*Type_T_direct)(double degree);
	double (*Type_T_inverse)(double microvolts);
	// Type E
	double (*Type_E_direct)(double degree);
	double (*Type_E_inverse)(double microvolts);
	// Type N
	double (*Type_N_direct)(double degree);
	double (*Type_N_inverse)(double microvolts);
	// Type B
	double (*Type_B_direct)(double degree);
	double (*Type_B_inverse)(double microvolts);
	// Type S
	double (*Type_S_direct)(double degree);
	double (*Type_S_inverse)(double microvolts);
	// Type R
	double (*Type_R_direct)(double degree);
	double (*Type_R_inverse)(double microvolts);
	// Type L
	double (*Type_L_direct)(double degree);
	double (*Type_L_inverse)(double microvolts);
	// Type M
	double (*Type_M_direct)(double degree);
	double (*Type_M_inverse)(double microvolts);
	// Type A1
	double (*Type_A1_direct)(double degree);
	double (*Type_A1_inverse)(double microvolts);
	// Type A2
	double (*Type_A2_direct)(double degree);
	double (*Type_A2_inverse)(double microvolts);
	// Type A3
	double (*Type_A3_direct)(double degree);
	double (*Type_A3_inverse)(double microvolts);
	// TXC
	double (*Thermocouple_direct)(enum TC_Type type, double degree, double TXC_degree);
	double (*Thermocouple_inverse)(enum TC_Type type, double microvolts, double TXC_degree);
};
extern struct ThermocoupleMath Thermocouple;









#endif /* INC_THERMOCOUPLEMATH_H_ */
