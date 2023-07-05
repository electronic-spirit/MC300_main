
#ifndef INC_MODBUSMASTER_H_
#define INC_MODBUSMASTER_H_

#include "stm32h7xx_hal.h"
#include "main.h"


/* Write full modbus' packet to the buffer ****************************************************************/
uint16_t WriteFloatToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, float Data);
uint16_t WriteInt32ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, int32_t Data);
uint16_t WriteUint32ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, uint32_t Data);
uint16_t WriteUint16ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, uint16_t Data);
/* Read meaning from buffer *******************************************************************************/
float TakeFloatFromBUFF(uint8_t* BUFF, uint16_t index);
uint16_t TakeUINT16FromBUFF(uint8_t* BUFF, uint16_t index);
int32_t TakeINT32FromBUFF(uint8_t* BUFF, uint16_t index);
/* Write full modbus' packet to the buffer for reading ****************************************************/
uint16_t RegisterRequest(uint8_t* BUFF, uint16_t address, uint16_t REGISTER, uint8_t com, uint8_t size);




#endif /* INC_MODBUSMASTER_H_ */
