/*
 * ThermoCalculator.c
 *
 *  Created on: 27 июн. 2023 г.
 *      Author: agapov
 */
#include "ThermoCalculator.h"
//#include <texts/TextKeysAndLanguages.hpp>


void ThermoCalculator_process(void)
{
	double TXC_degree = 0;

	MX_TouchGFX_Process();

	// Расчет температуры на термосопротивлении
	//CalibrateChannel.ThermoResistance_R1 =

	// Расчет температуры на термопаре TC1
	switch(CalibrateChannel.ThermoCoupleTXCsourceTC1)
	{
		case ThermoCoupleTXCsource_Internal: TXC_degree = CalibrateChannel.TXC_TC1; break;
		case ThermoCoupleTXCsource_R1: TXC_degree = CalibrateChannel.ThermoResistance_R1; break;
		case ThermoCoupleTXCsource_R2: TXC_degree = CalibrateChannel.ThermoResistance_R2; break;
		case ThermoCoupleTXCsource_Manual: TXC_degree = CalibrateChannel.TXC_manual; break;
	}

	CalibrateChannel.ThermoCouple_TC1 = Thermocouple.Thermocouple_inverse(CalibrateChannel.ThermoCoupleTypeTC1, CalibrateChannel.Voltage_TC1, TXC_degree);

	// Расчет температуры на термопаре TC2
	switch(CalibrateChannel.ThermoCoupleTXCsourceTC2)
	{
		case ThermoCoupleTXCsource_Internal: TXC_degree = CalibrateChannel.TXC_TC2; break;
		case ThermoCoupleTXCsource_R1: TXC_degree = CalibrateChannel.ThermoResistance_R1; break;
		case ThermoCoupleTXCsource_R2: TXC_degree = CalibrateChannel.ThermoResistance_R2; break;
		case ThermoCoupleTXCsource_Manual: TXC_degree = CalibrateChannel.TXC_manual; break;
	}

	CalibrateChannel.ThermoCouple_TC2 = Thermocouple.Thermocouple_inverse(CalibrateChannel.ThermoCoupleTypeTC2, CalibrateChannel.Voltage_TC2, TXC_degree);

	ELSPIRE.sleep(500);
}



float ReturnTXCFromSource(uint16_t source)
{
	switch(source)
	{
		case ThermoCoupleTXCsource_Internal: return (float)CalibrateChannel.TXC_TC1;
		case ThermoCoupleTXCsource_R1: return (float)CalibrateChannel.ThermoResistance_R1;
		case ThermoCoupleTXCsource_R2: return (float)CalibrateChannel.ThermoResistance_R2;
		case ThermoCoupleTXCsource_Manual: return (float)CalibrateChannel.TXC_manual;
		default: return 0;
	}
}

enum TEXTS TCtypeConverter(uint16_t type)
{
	switch(type)
	{
		case Type_J: return T_RESOURCE_J;
		case Type_K: return T_RESOURCE_K;
		case Type_E: return T_RESOURCE_E;
		case Type_T: return T_RESOURCE_T;
		case Type_N: return T_RESOURCE_N;
		case Type_B: return T_RESOURCE_B;
		case Type_S: return T_RESOURCE_S;
		case Type_R: return T_RESOURCE_R;
		case Type_L: return T_RESOURCE_L;
		case Type_M: return T_RESOURCE_M;
		case Type_A1: return T_RESOURCE_A1;
		case Type_A2: return T_RESOURCE_A2;
		case Type_A3: return T_RESOURCE_A3;
		default: return T_RESOURCE_J;
	}
}



