
#include "GlobalVariables.h"


// Touch screen Coordinates
uint32_t __attribute__((section(".ExtRAM"))) Xglobal;
uint32_t __attribute__((section(".ExtRAM"))) Yglobal;

struct RTClock __attribute__((section(".ExtRAM"))) RealTimeClock = {0};
struct CalibrateSettings __attribute__((section(".ExtRAM"))) CalibrateChannel = {0};

// Other
uint16_t __attribute__((section(".ExtRAM"))) EditingParameter;
uint8_t __attribute__((section(".ExtRAM"))) BattPercent;
double __attribute__((section(".ExtRAM"))) DoubleNumEdit;
uint8_t __attribute__((section(".ExtRAM"))) PreviousScreen;
uint8_t __attribute__((section(".ExtRAM"))) PreviousMainScreen;
double __attribute__((section(".ExtRAM"))) ThresholdTemp;
double __attribute__((section(".ExtRAM"))) DutyCycleTemp;
uint16_t __attribute__((section(".ExtRAM"))) ThermocoupleTXCTemp;
uint8_t __attribute__((section(".ExtRAM"))) ActiveEditingChannel;
uint8_t __attribute__((section(".ExtRAM"))) GeneratorChannel;
uint8_t __attribute__((section(".ExtRAM"))) EditGeneratorChannel;
uint16_t __attribute__((section(".ExtRAM"))) NumEdit_name;

uint8_t __attribute__((section(".ExtRAM"))) IN_modbus;
uint8_t __attribute__((section(".ExtRAM"))) OUT_modbus;
uint8_t __attribute__((section(".ExtRAM"))) PRESS_modbus;

// For Number Editor
uint8_t __attribute__((section(".ExtRAM"))) NumEditorCurrentPosition;
uint8_t __attribute__((section(".ExtRAM"))) NumEditorSign;
uint8_t __attribute__((section(".ExtRAM"))) NumEditorStorage[16];
uint8_t __attribute__((section(".ExtRAM"))) NumEditorPoint;
