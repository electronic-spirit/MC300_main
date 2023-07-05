
#include "Buttons.h"
#include "app_touchgfx.h"


uint8_t ContraContactBounce[6];
uint8_t	ButtonState;
#define ContraContactBounceConst	15

void ButtonsProcess(void)
{
	MX_TouchGFX_Process();

	// Button 1
	if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0)
	{
		if(ContraContactBounce[0]<ContraContactBounceConst)ContraContactBounce[0]++;
		else ButtonState|=(1<<0);


	}
	else ContraContactBounce[0] = 0;


	ELSPIRE.sleep(10);
}
