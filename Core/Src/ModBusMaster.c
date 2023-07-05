
#include "ModBusMaster.h"
#include "string.h"




uint16_t WriteFloatToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, float Data)
{
	uint8_t membuf[4];
	uint16_t CRC16;
	memcpy(membuf, &Data, 4);
	BUFF[0] = address;
	BUFF[1] = 0x10;
	BUFF[2] = reg>>8;
	BUFF[3] = reg&0xFF;
	BUFF[4] = 0x00;
	BUFF[5] = 2;
	BUFF[6] = membuf[3];
	BUFF[7] = membuf[2];
	BUFF[8] = membuf[1];
	BUFF[9] = membuf[0];
	CRC16 = crc16((uint8_t*)BUFF, 0, 10);
	BUFF[11] = CRC16>>8;
	BUFF[10] = CRC16&0xFF;
	return 12;
}


uint16_t WriteInt32ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, int32_t Data)
{
	uint8_t membuf[4];
	uint16_t CRC16;
	memcpy(membuf, &Data, 4);
	BUFF[0] = address;
	BUFF[1] = 0x10;
	BUFF[2] = reg>>8;
	BUFF[3] = reg&0xFF;
	BUFF[4] = 0x00;
	BUFF[5] = 2;
	BUFF[6] = membuf[3];
	BUFF[7] = membuf[2];
	BUFF[8] = membuf[1];
	BUFF[9] = membuf[0];
	CRC16 = crc16((uint8_t*)BUFF, 0, 10);
	BUFF[11] = CRC16>>8;
	BUFF[10] = CRC16&0xFF;
	return 12;
}


uint16_t WriteUint32ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, uint32_t Data)
{
	uint8_t membuf[4];
	uint16_t CRC16;
	memcpy(membuf, &Data, 4);
	BUFF[0] = address;
	BUFF[1] = 0x10;
	BUFF[2] = reg>>8;
	BUFF[3] = reg&0xFF;
	BUFF[4] = 0x00;
	BUFF[5] = 2;
	BUFF[6] = membuf[3];
	BUFF[7] = membuf[2];
	BUFF[8] = membuf[1];
	BUFF[9] = membuf[0];
	CRC16 = crc16((uint8_t*)BUFF, 0, 10);
	BUFF[11] = CRC16>>8;
	BUFF[10] = CRC16&0xFF;
	return 12;
}


uint16_t WriteUint16ToBUFF(uint8_t* BUFF, uint16_t address, uint16_t reg, uint16_t Data)
{
	uint16_t CRC16;

	BUFF[0] = address;
	BUFF[1] = 0x06;
	BUFF[2] = reg>>8;
	BUFF[3] = reg&0xFF;
	BUFF[4] = Data>>8;
	BUFF[5] = Data&0xFF;
	CRC16 = crc16((uint8_t*)BUFF, 0, 6);
	BUFF[7] = CRC16>>8;
	BUFF[6] = CRC16&0xFF;
	return 8;
}


float TakeFloatFromBUFF(uint8_t* BUFF, uint16_t index)
{
	float RES;
	uint8_t readbuf[4];
	readbuf[0] = BUFF[index+3]; 	//      3F 59 99 9A
	readbuf[1] = BUFF[index+2];		//      0 3 2
	readbuf[2] = BUFF[index+1];		//      2 1 0
	readbuf[3] = BUFF[index];		//      3 0 1

	memcpy(&RES, readbuf, 4);
	return RES;
}




int32_t TakeINT32FromBUFF(uint8_t* BUFF, uint16_t index)
{
	int32_t RES;
	uint8_t readbuf[4];
	readbuf[0] = BUFF[index+3];
	readbuf[1] = BUFF[index+2];
	readbuf[2] = BUFF[index+1];
	readbuf[3] = BUFF[index];
	memcpy(&RES, readbuf, 4);
	return RES;
}


uint16_t TakeUINT16FromBUFF(uint8_t* BUFF, uint16_t index)
{
	return (uint16_t)(BUFF[index]*256 + BUFF[index+1]);
}


uint16_t RegisterRequest(uint8_t* BUFF, uint16_t address, uint16_t REGISTER, uint8_t com, uint8_t size)
{
	uint16_t CRC16;
	BUFF[0] = address;
	BUFF[1] = com;
	BUFF[2] = REGISTER>>8;
	BUFF[3] = REGISTER&0xFF;
	BUFF[4] = size>>8;
	BUFF[5] = size&0xFF;
	CRC16 = crc16((uint8_t*)BUFF, 0, 6);
	BUFF[7] = CRC16>>8;
	BUFF[6] = CRC16&0xFF;
	return 8;
}



