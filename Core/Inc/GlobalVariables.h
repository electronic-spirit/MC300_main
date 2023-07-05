
#ifndef INC_GLOBALVARIABLES_H_
#define INC_GLOBALVARIABLES_H_

#include "main.h"
#include "stm32h7xx_hal.h"

// Touch screen Coordinates
extern uint32_t Xglobal;
extern uint32_t Yglobal;

// Real time clock
struct RTClock
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t sec;
	uint8_t edit_year;
	uint8_t edit_month;
	uint8_t edit_day;
	uint8_t edit_hour;
	uint8_t edit_minute;
	uint8_t edit_sec;
};
extern struct RTClock RealTimeClock;




// Calibrate
struct CalibrateSettings
{
	// Thermocouple
	float TXC_TC1;						// Температура холодного спая TC1 (°C)
	float TXC_TC2;						// Температура холодного спая TC2 (°C)
	double Generate_ThermocoupleTC1;	// Генерация температуры на термопаре (°C)
	uint16_t ThermoCoupleTypeTC1;		// Тип термопары TC1
	uint16_t ThermoCoupleTypeTC2;		// Тип термопары TC2
	uint16_t ThermoCoupleTXCsourceTC1;	// Источник ТХС TC1
	uint16_t ThermoCoupleTXCsourceTC2;	// Источник ТХС TC2
	double ThermoCouple_TC1;			// Температура TC1 (°C)
	double ThermoCouple_TC2;			// Температура TC2 (°C)
	double TXC_manual;					// Температура холодного спая ручной ввод (°С)

	// Thermoresistance
	double Generate_ThermoResistance;	// Генерируемое термосопротивление (°С)
	uint8_t ThermoResistanceType_R1;	// Тип термосопротивления R1
	uint8_t ThermoResistanceType_R2;	// Тип термосопротивления R2
	double ThermoResistance_R1;			// Температура на R1 (°C)
	double ThermoResistance_R2;			// Температура на R2 (°C)
	float ThermoresistanceTRC_R1;		// Температурный коэффициент сопротивления R1
	float ThermoresistanceTRC_R2;		// Температурный коэффициент сопротивления R2
	uint16_t ThermoResistanceR0_R1;		// Сопротивление при 0°С R1 (Ом)
	uint16_t ThermoResistanceR0_R2;		// Сопротивление при 0°С R2 (Ом)

	// Resistance
	double Resistance_R1;				// Сопротивление R1 (Ohm)
	double Resistance_R2;				// Сопротивление R2 (Ohm)
	uint8_t ResistanceWireSchematic_R1;	// Схема подключения R1
	uint8_t ResistanceWireSchematic_R2;	// Схема подключения R2

	double Generate_Current;
	double Generate_VoltageOUT;
	double Generate_VoltageTC1;
	double Generate_Resistance;
	uint32_t Generate_Pulse;			// Количество импульсов
	uint32_t Generate_Pulse_Len;		// Длительность импульса
	uint32_t Generate_Pulse_Pause_Len;	// Длительность паузы

	double Generate_Frequency;


	// Pressure
	double Pressure_1;					// Первый порт внутренний датчик давления
	double Pressure_2;					// Второй порт внутренний датчик давления
	double Pressure_3;					// Третий порт внутренний датчик давления
	double Pressure_outer;				// Внешний датчик давления
	double Pressure_atm;				// Барометр
	double Pressure_atm_temperature;	// Барометр температура
	double Pressure_outer_temperature;	// Температура внешнего датчика
	uint8_t Pressure_outer_Zero;		// Обнуление для внешнего датчика



	double Current_DC;
	uint8_t Power24;					// Внутренний источник для измерения тока
	uint8_t Power12;					// Внутренний источник для генерации тока

	double Voltage_IN;
	double Voltage_TC1;
	double Voltage_TC2;



	double Pulse;
	double PulseThreshold;
	uint8_t PulseFront;
	double PulseFreq;
	double PulsePWM;
	double PulseAmp;
	double Frequency;
	uint8_t FrequencyForm;
	double FrequencyDutyCycle;
	double FrequencyAmplitude;
	double FrequencyThreshold;
	double SwitchThreshold;
	uint16_t Switch;
	uint8_t Switch_Channel;
	uint8_t SwitchSound;



	uint16_t ThermoResistanceChannel;


	uint16_t Unit_1;
	uint16_t Unit_2;
	uint16_t Parameter_1;
	uint16_t Parameter_2;

	uint8_t ChangeParameter; // 1 if one of parameter was changed
};

extern struct CalibrateSettings CalibrateChannel;



// Other
extern uint16_t EditingParameter;				// Индекс редактируемого параметра
extern uint8_t BattPercent;						// Процент заряда АКБ
extern double DoubleNumEdit;					// Сюда передаем переменную для редактирования
extern uint8_t PreviousScreen;					// Экран возврата
extern uint8_t PreviousMainScreen;				// Экран основного измерения
extern double ThresholdTemp;					// Для временного хранения порогового уровня
extern uint16_t ThermocoupleTXCTemp;			// Временное хранение источника компенсации холодного спая
extern uint8_t ActiveEditingChannel;			// Активный редактируемый канал калибратора
extern double DutyCycleTemp;					// Временное хранение
extern uint8_t GeneratorChannel;				// Номер канала для генерации сигналов
extern uint8_t EditGeneratorChannel;			// Управление генераторами
extern uint16_t NumEdit_name;					// Какой параметр редактируется в NumEdite


extern uint8_t IN_modbus;
extern uint8_t OUT_modbus;
extern uint8_t PRESS_modbus;


// For Number Editor
extern uint8_t NumEditorCurrentPosition;
extern uint8_t NumEditorSign;
extern uint8_t NumEditorStorage[16];
extern uint8_t NumEditorPoint;


enum NumEdit_name_enum
{
	NumEdit_name_Current_1,
	NumEdit_name_VoltageOUT_1,
	NumEdit_name_VoltageTC1_1,
	NumEdit_name_Resistance_1,
	NumEdit_name_Thermocouple_1,
	NumEdit_name_Thermoresistance_1,
	NumEdit_name_Freqency_1,
	NumEdit_name_Pulses_1,
	NumEdit_name_Current_2,
	NumEdit_name_VoltageOUT_2,
	NumEdit_name_VoltageTC1_2,
	NumEdit_name_Resistance_2,
	NumEdit_name_Thermocouple_2,
	NumEdit_name_Thermoresistance_2,
	NumEdit_name_Freqency_2,
	NumEdit_name_Pulses_2,
	NumEdit_name_FreqAmp_1,
	NumEdit_name_FreqAmp_2,
	NumEdit_name_FreqThreshold_1,
	NumEdit_name_FreqThreshold_2,
	NumEdit_name_FreqDutyCycle_1,
	NumEdit_name_FreqDutyCycle_2,
	NumEdit_name_PulsesThreshold_1,
	NumEdit_name_PulsesThreshold_2,
	NumEdit_name_PulseDutyCycle_1,
	NumEdit_name_PulseDutyCycle_2,
	NumEdit_name_PulseAmp_1,
	NumEdit_name_PulseAmp_2,
	NumEdit_name_PulseFreq_1,
	NumEdit_name_PulseFreq_2,
	NumEdit_name_PulsePWM_1,
	NumEdit_name_PulsePWM_2,
};


// Names of screens
enum NameOfPreviousScreen
{
	NameOfPreviousScreen_MeasurementScreen,
	NameOfPreviousScreen_CalibrationScreen,
	NameOfPreviousScreen_TXCThermoCoupleScreen,
	NameOfPreviousScreen_FrequencyThresholdScreen,
	NameOfPreviousScreen_FrequencyAmplitudeScreen,
	NameOfPreviousScreen_FrequencyDutyCycleScreen,
	NameOfPreviousScreen_SwitchThresholdScreen,
	NameOfPreviousScreen_PulseThresholdScreen,
	NameOfPreviousScreen_PulseFreqScreen,
	NameOfPreviousScreen_PulseAmpScreen,
	NameOfPreviousScreen_PulsePWMScreen,
	NameOfPreviousScreen_EditVoltageScreen,
	NameOfPreviousScreen_EditCurrentScreen,
	NameOfPreviousScreen_EditResistanceScreen,
};

enum EditGeneratorChannelNames
{
	EditGeneratorChannel_Current,
	EditGeneratorChannel_Pressure,
	EditGeneratorChannel_Voltage,
	EditGeneratorChannel_Thermocouple,
	EditGeneratorChannel_Thermoresistance,
	EditGeneratorChannel_Resistance,
	EditGeneratorChannel_Frequency,
	EditGeneratorChannel_Pulses,
	EditGeneratorChannel_Relay,
	EditGeneratorChannel_HART,
};

// Names of active editing channel
enum NameOfActiveEditingChannel
{
	ActiveChannel_Measurement,
	ActiveChannel_Calibration_1,
	ActiveChannel_Calibration_2,
};



// TXC source
enum ThermoCoupleTXCsource
{
	ThermoCoupleTXCsource_Internal,
	ThermoCoupleTXCsource_R1,
	ThermoCoupleTXCsource_R2,
	ThermoCoupleTXCsource_Manual,
};



// Measure channel
enum MeasureChannel
{
	MeasureChannelR1,
	MeasureChannelR2,
	MeasureChannelPORT1,
	MeasureChannelPORT2,
	MeasureChannelPORT3,
	MeasureChannelPORT4,
	MeasureChannelBarometer,
	MeasureChannelTC1,
	MeasureChannelTC2,
	MeasureChannelVoltageInput,
	MeasureChannelVoltageTC1,
	MeasureChannelVoltageTC2,
	MeasureChannelSwitchNormal,
	MeasureChannelSwitchInverted,
};


// Measure parameters
enum MeasureParameter
{
	// Pressure
	MeasureParameterExternalPressure,
	MeasureParameterInternalPressure_1,
	MeasureParameterInternalPressure_2,
	MeasureParameterInternalPressure_3,
	MeasureParameterBarometerPressure,
	// Thermocouple
	MeasureParameterThermoCoupleGenerate,
	MeasureParameterThermoCoupleMeasureTC1,
	MeasureParameterThermoCoupleMeasureTC2,
	// Frequency
	MeasureParameterFrequencyGenerate,
	MeasureParameterFrequencyMeasure,
	// Current
	MeasureParameterCurrentGenerate,
	MeasureParameterCurrentMeasure,
	// Thermoresistance
	MeasureParameterThermoResistanceGenerate,
	MeasureParameterThermoResistanceMeasureR1,
	MeasureParameterThermoResistanceMeasureR2,
	// Pulse
	MeasureParameterPulsesCounter,
	MeasureParameterPulsesGenerate,
	// Voltage
	MeasureParameterVoltageGenerateOUT,
	MeasureParameterVoltageGenerateTC1,
	MeasureParameterVoltageMeasureIN,
	MeasureParameterVoltageMeasureTC1,
	MeasureParameterVoltageMeasureTC2,
	// Resistance
	MeasureParameterResistanceGenerate,
	MeasureParameterResistanceMeasureR1,
	MeasureParameterResistanceMeasureR2,
	// Relay
	MeasureParameterRelayNormal,
	MeasureParameterRelayInverted,
	// HART
	MeasureParameterHart,
};

// Measure Units
enum MeasureUnits
{
	// Current
	MeasureUnits_nA,
	MeasureUnits_uA,
	MeasureUnits_mA,
	MeasureUnits_A,
	// Voltage
	MeasureUnits_uV,
	MeasureUnits_mV,
	MeasureUnits_V,
	// Resistance
	MeasureUnits_Ohm,
	MeasureUnits_kOhm,
	MeasureUnits_MOhm,
	//Pressure
	MeasureUnits_kgcm2,
	MeasureUnits_psi,
	MeasureUnits_mbar,
	MeasureUnits_Bar,
	MeasureUnits_mmHg,
	MeasureUnits_mmH2O,
	MeasureUnits_inHg,
	MeasureUnits_inH2O,
	MeasureUnits_Pa,
	MeasureUnits_kPa,
	MeasureUnits_MPa,
	// Relay
	MeasureUnits_Switch_on,
	MeasureUnits_Switch_off,
	// Thermocouple Thermoresistance
	MeasureUnits_C,
	MeasureUnits_F,
	// Frequency
	MeasureUnits_uHz,
	MeasureUnits_mHz,
	MeasureUnits_Hz,
	MeasureUnits_kHz,
	MeasureUnits_MHz,
	// Pulse
	MeasureUnits_uS,
	MeasureUnits_mS,
	MeasureUnits_S,
};

#endif /* INC_GLOBALVARIABLES_H_ */
