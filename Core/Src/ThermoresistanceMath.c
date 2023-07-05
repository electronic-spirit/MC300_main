/*
 * ThermoresistanceMath.c
 *
 *  Created on: 22 июн. 2023 г.
 *      Author: agapov
 */
#include "math.h"
#include "ThermoresistanceMath.h"

//							A			B			C			D1		D2		D3		D4
const double PT385[7] = {3.9083e-3, -5.775e-7, -4.183e-12, 255.819, 9.1455, -2.92363, 1.7909};
const double PT391[7] = {3.9690e-3, -5.841e-7, -4.330e-12, 251.903, 8.80035, -2.91506, 1.67611};
const double CU428[7] = {4.28e-3, -6.2032e-7, 8.5154e-10, 233.87, 7.9370, -2.0062, -0.3953};
const double CU426[7] = {4.26e-3, -6.2032e-7, 8.5154e-10, 233.87, 7.9370, -2.0062, -0.3953};
const double NI617[7] = {5.4963e-3, 6.7556e-6, 9.2004e-9, 144.096, -25.502, 4.4876, 0};
double USER_TR[7] = {5.4963e-3, 6.7556e-6, 9.2004e-9, 144.096, -25.502, 4.4876, 0};

enum arrindex {A, B, C, D1, D2, D3, D4};



double Thermoresistance_PT_direct(double degree, double R0, const double*PT);
double Thermoresistance_PT_inverse(double resistance, double R0, const double*PT);
double Thermoresistance_CU_direct(double degree, double R0, const double*CU);
double Thermoresistance_CU_inverse(double resistance, double R0, const double*CU);
double Thermoresistance_NI_direct(double degree, double R0, const double*NI);
double Thermoresistance_NI_inverse(double resistance, double R0, const double*NI);


struct ThermoresistanceMath Thermoresistance =
{
		Thermoresistance_PT_direct, Thermoresistance_PT_inverse, Thermoresistance_CU_direct, Thermoresistance_CU_inverse, Thermoresistance_NI_direct, Thermoresistance_NI_inverse
};



double Thermoresistance_PT_direct(double degree, double R0, const double*PT)
{
	if(degree < 0)
		return R0*(1.0 + PT[A]*degree + PT[B]*degree*degree + PT[C]*(degree - 100.0)*degree*degree*degree);
	else return R0*(1.0 + PT[A]*degree + PT[B]*degree*degree);
}


double Thermoresistance_CU_direct(double degree, double R0, const double*CU)
{
	if(degree < 0)
		return R0*(1.0 + CU[A]*degree + CU[B]*degree*(degree + 6.7) + CU[C]*degree*degree*degree);
	else return R0*(1.0 + CU[A]*degree);
}


double Thermoresistance_NI_direct(double degree, double R0, const double*NI)
{
	if(degree < 100.0)
		return R0*(1.0 + NI[A]*degree + NI[B]*degree*degree);
	else return R0*(1.0 + NI[A]*degree + NI[B]*degree*degree + NI[C]*(degree - 100.0)*degree*degree);
}

double Thermoresistance_PT_inverse(double resistance, double R0, const double*PT)
{
	double RES = 0;
	double relative = resistance/R0;
	// if t < 0°C
	if(relative < 1)
	{
		for(int i=0;i<4;i++) RES += PT[D1+i]*pow((relative-1.0), i+1);
	}
	else
	{
		RES = (sqrt(PT[A]*PT[A] - 4*PT[B]*(1.0 - relative)) - PT[A])/(2*PT[B]);
	}

	return RES;
}

double Thermoresistance_CU_inverse(double resistance, double R0, const double*CU)
{
	double RES = 0;
	double relative = resistance/R0;
	// if t < 0°C
	if(relative < 1)
	{
		for(int i=0;i<4;i++) RES += CU[D1+i]*pow((relative-1.0), i+1);
	}
	else
	{
		RES = (relative - 1.0) / CU[A];
	}

	return RES;
}

double Thermoresistance_NI_inverse(double resistance, double R0, const double*NI)
{
	double RES = 0;
	double relative = resistance/R0;
	// if t < 0°C
	if(relative < 1.6172)
	{
		RES = 100;
		for(int i=0;i<3;i++) RES += NI[D1+i]*pow((relative-1.6172), i+1);
	}
	else
	{
		RES = (sqrt(NI[A]*NI[A] - 4*NI[B]*(1.0 - relative)) - NI[A])/2*NI[B];
	}

	return RES;
}


