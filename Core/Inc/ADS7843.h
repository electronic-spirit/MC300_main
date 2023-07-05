
#ifndef INC_ADS7843_H_
#define INC_ADS7843_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "stm32h7xx_hal.h"



 void ADS7843_Init(void);
uint8_t ADS7843_Update(int32_t *x, int32_t *y);




#ifdef __cplusplus
}
#endif

#endif /* INC_ADS7843_H_ */
