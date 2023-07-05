/*
 * ThermoCalculator.h
 *
 *  Created on: 27 июн. 2023 г.
 *      Author: agapov
 */

#ifndef INC_THERMOCALCULATOR_H_
#define INC_THERMOCALCULATOR_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32h7xx_hal.h"
#include <texts/TextKeysAndLanguages.hpp>
#include "ThermocoupleMath.h"


void ThermoCalculator_process(void);
float ReturnTXCFromSource(uint16_t source);
enum TEXTS TCtypeConverter(uint16_t type);

#ifdef __cplusplus
}
#endif




#endif /* INC_THERMOCALCULATOR_H_ */
