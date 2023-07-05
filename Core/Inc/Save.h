
#ifndef INC_SAVE_H_
#define INC_SAVE_H_

#include "main.h"
#include "stm32h7xx_hal.h"


struct Saving
{
	uint16_t Brightness;
	uint16_t Parameter2;
	uint8_t Parameter3;
	double Parameter4;
};
extern struct Saving SavingParameters;

void SaveParameters(void);
void LoadParameters(void);


#endif /* INC_SAVE_H_ */
