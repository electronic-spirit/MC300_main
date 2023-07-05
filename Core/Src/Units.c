
#include "Units.h"

double ConvertUnit_Pressure(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_kgcm2: 	RES = (((double)data)*98066.5); break;
		case MeasureUnits_kPa: 		RES = (((double)data)*1000.0); break;
		case MeasureUnits_MPa: 		RES = (((double)data)*1000000.0); break;
		case MeasureUnits_inHg:  	RES = (((double)data)*3386.389); break;
		case MeasureUnits_psi:  	RES = (((double)data)*6894.76); break;
		case MeasureUnits_Bar: 		RES = (((double)data)*100000.0); break;
		case MeasureUnits_mbar: 	RES = ((double)data*100.0); break;
		case MeasureUnits_mmHg: 	RES = (((double)data)*133.322); break;
		case MeasureUnits_mmH2O: 	RES = (((double)data)*9.80665002863); break;
		case MeasureUnits_inH2O: 	RES = (((double)data)*249.082); break;
		case MeasureUnits_Pa: 		break;
		default: return  data;
	}
	switch(unitTo)
	{
		case MeasureUnits_kgcm2: 	return (((double)RES)/98066.5);
		case MeasureUnits_kPa: 		return (((double)RES)/1000.0);
		case MeasureUnits_MPa: 		return (((double)RES)/1000000.0);
		case MeasureUnits_inHg:  	return (((double)RES)/3386.389);
		case MeasureUnits_psi:  	return (((double)RES)/6894.76);
		case MeasureUnits_Bar: 		return (((double)RES)/100000.0);
		case MeasureUnits_mbar: 	return ((double)RES/100.0);
		case MeasureUnits_mmHg: 	return (((double)RES)/133.322);
		case MeasureUnits_mmH2O: 	return (((double)RES)/9.80665002863);
		case MeasureUnits_inH2O: 	return (((double)RES)/249.082);
		case MeasureUnits_Pa: 		return  RES;
		default: return  data;
	}
}


double ConvertUnit_Voltage(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_uV: 	break;
		case MeasureUnits_mV: 	RES = (((double)data)*1000); break;
		case MeasureUnits_V: 	RES = (((double)data)*1000000); break;
		default: return  data;
	}

	switch(unitTo)
	{
		case MeasureUnits_uV: return RES;
		case MeasureUnits_mV: return (((double)RES)/1000);
		case MeasureUnits_V:  return (((double)RES)/1000000);
		default: return  RES;
	}
}


double ConvertUnit_Current(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_nA: 	break;
		case MeasureUnits_uA: 	RES = (((double)data)*1000); break;
		case MeasureUnits_mA: 	RES = (((double)data)*1000000); break;
		case MeasureUnits_A: 	RES = (((double)data)*1000000000); break;
		default: return  data;
	}
	switch(unitTo)
	{
		case MeasureUnits_nA: 	return RES;
		case MeasureUnits_uA: 	return (((double)RES)/1000);
		case MeasureUnits_mA: 	return (((double)RES)/1000000);
		case MeasureUnits_A: 	return (((double)RES)/1000000000);
		default: return  RES;
	}
}


double ConvertUnit_Temperature(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_C: 	break;
		case MeasureUnits_F: 	return (((double)data - 32) * 0.55555555); break;
		default: return  data;
	}
	switch(unitTo)
	{
		case MeasureUnits_C: 	return RES;
		case MeasureUnits_F: 	return ((double)RES / 0.55555555) + 32;
		default: return  RES;
	}
}


double ConvertUnit_Frequency(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_uHz: 	RES = data; break;
		case MeasureUnits_mHz: 	RES = (((double)data)*1000); break;
		case MeasureUnits_Hz: 	RES = (((double)data)*1000000); break;
		case MeasureUnits_kHz: 	RES = (((double)data)*1000000000); break;
		case MeasureUnits_MHz: 	RES = (((double)data)*1000000000000); break;
		default: return  data;
	}
	switch(unitTo)
	{
		case MeasureUnits_uHz: 	return RES;
		case MeasureUnits_mHz: 	return (((double)RES)/1000);
		case MeasureUnits_Hz: 	return (((double)RES)/1000000);
		case MeasureUnits_kHz: 	return (((double)RES)/1000000000);
		case MeasureUnits_MHz: 	return (((double)RES)/1000000000000);
		default: return  RES;
	}
}



double ConvertUnit_Resistance(uint16_t unitFrom, uint16_t unitTo, double data)
{
	double RES = data;
	switch(unitFrom)
	{
		case MeasureUnits_Ohm: 	RES = data; break;
		case MeasureUnits_kOhm: RES = (((double)data)/1000); break;
		case MeasureUnits_MOhm: RES = (((double)data)/1000000); break;
		default: return  data;
	}
	switch(unitTo)
	{
		case MeasureUnits_Ohm: 	return RES;
		case MeasureUnits_kOhm: return (((double)RES)/1000);
		case MeasureUnits_MOhm: return (((double)RES)/1000000);
		default: return  RES;
	}
}




