#include "BMP390.h"
#include "math.h"

extern I2C_HandleTypeDef hi2c3;



#define BMP390_ADDRESS 0xEC // (0x76<<1)

#define Total_Number_32 4294967296.0
#define Total_Number_30 1073741824.0
#define Total_Number_29 536870912.0
#define Total_Number_24 16777216.0
#define Total_Number_20 1048576.0
#define Total_Number_16 65536.0
#define Total_Number_15 32768.0
#define Total_Number_14 16384.0
#define Total_Number_12 4096.0
#define Total_Number_8 256.0
#define Total_Number_6 64.0
#define Total_Number_5 32.0
#define Total_Number_1 2.0
#define Total_Number_Neg_8 0.00390625
#define Total_Number_Neg_3 0.125
#define Standard_atmospheric_pressure 101325.0

/**
 * @brief chip register definition
 */
#define BMP390_REG_CMD                 0x7E        /**< command register */
#define BMP390_REG_NVM_PAR_T1_L        0x31        /**< NVM PAR T1 low register */
#define BMP390_REG_NVM_PAR_T1_H        0x32        /**< NVM PAR T1 high register */
#define BMP390_REG_NVM_PAR_T2_L        0x33        /**< NVM PAR T2 low register */
#define BMP390_REG_NVM_PAR_T2_H        0x34        /**< NVM PAR T2 high register */
#define BMP390_REG_NVM_PAR_T3          0x35        /**< NVM PAR T3 register */
#define BMP390_REG_NVM_PAR_P1_L        0x36        /**< NVM PAR P1 low register */
#define BMP390_REG_NVM_PAR_P1_H        0x37        /**< NVM PAR P1 high register */
#define BMP390_REG_NVM_PAR_P2_L        0x38        /**< NVM PAR P2 low register */
#define BMP390_REG_NVM_PAR_P2_H        0x39        /**< NVM PAR P2 high register */
#define BMP390_REG_NVM_PAR_P3          0x3A        /**< NVM PAR P3 register */
#define BMP390_REG_NVM_PAR_P4          0x3B        /**< NVM PAR P4 register */
#define BMP390_REG_NVM_PAR_P5_L        0x3C        /**< NVM PAR P5 low register */
#define BMP390_REG_NVM_PAR_P5_H        0x3D        /**< NVM PAR P5 high register */
#define BMP390_REG_NVM_PAR_P6_L        0x3E        /**< NVM PAR P6 low register */
#define BMP390_REG_NVM_PAR_P6_H        0x3F        /**< NVM PAR P6 high register */
#define BMP390_REG_NVM_PAR_P7          0x40        /**< NVM PAR P7 register */
#define BMP390_REG_NVM_PAR_P8          0x41        /**< NVM PAR P8 register */
#define BMP390_REG_NVM_PAR_P9_L        0x42        /**< NVM PAR P9 low register */
#define BMP390_REG_NVM_PAR_P9_H        0x43        /**< NVM PAR P9 high register */
#define BMP390_REG_NVM_PAR_P10         0x44        /**< NVM PAR P10 register */
#define BMP390_REG_NVM_PAR_P11         0x45        /**< NVM PAR P11 register */
#define BMP390_REG_CONFIG              0x1F        /**< configure register */
#define BMP390_REG_ODR                 0x1D        /**< odr register */
#define BMP390_REG_OSR                 0x1C        /**< osr register */
#define BMP390_REG_PWR_CTRL            0x1B        /**< power control register */
#define BMP390_REG_IF_CONF             0x1A        /**< if configure register */
#define BMP390_REG_INT_CTRL            0x19        /**< interrupt control register */
#define BMP390_REG_FIFO_CONFIG_2       0x18        /**< fifo configure 2 register */
#define BMP390_REG_FIFO_CONFIG_1       0x17        /**< fifo configure 1 register */
#define BMP390_REG_FIFO_WTM_1          0x16        /**< fifo watermark 1 register */
#define BMP390_REG_FIFO_WTM_0          0x15        /**< fifo watermark 2 register */
#define BMP390_REG_FIFO_DATA           0x14        /**< fifo data register */
#define BMP390_REG_FIFO_LENGTH_1       0x13        /**< fifo length 1 register */
#define BMP390_REG_FIFO_LENGTH_0       0x12        /**< fifo length 0 register */
#define BMP390_REG_INT_STATUS          0x11        /**< interrupt status register */
#define BMP390_REG_EVENT               0x10        /**< event register */
#define BMP390_REG_SENSORTIME_2        0x0E        /**< sensor time 2 register */
#define BMP390_REG_SENSORTIME_1        0x0D        /**< sensor time 1 register */
#define BMP390_REG_SENSORTIME_0        0x0C        /**< sensor time 0 register */
#define BMP390_REG_DATA_5              0x09        /**< data 5 register */
#define BMP390_REG_DATA_4              0x08        /**< data 4 register */
#define BMP390_REG_DATA_3              0x07        /**< data 3 register */
#define BMP390_REG_DATA_2              0x06        /**< data 2 register */
#define BMP390_REG_DATA_1              0x05        /**< data 1 register */
#define BMP390_REG_DATA_0              0x04        /**< data 0 register */
#define BMP390_REG_STATUS              0x03        /**< status register */
#define BMP390_REG_ERR_REG             0x02        /**< error register */
#define BMP390_REG_REV_ID              0x01        /**< rev id register */
#define BMP390_REG_CHIP_ID             0x00        /**< chip id register */


#define P_Oversampling_x1	0x00
#define P_Oversampling_x2	0x01
#define P_Oversampling_x4	0x02
#define P_Oversampling_x8	0x03
#define P_Oversampling_x16	0x04
#define P_Oversampling_x32	0x05

#define T_Oversampling_x1	0x00
#define T_Oversampling_x2	0x08
#define T_Oversampling_x4	0x10
#define T_Oversampling_x8	0x18
#define T_Oversampling_x16	0x20
#define T_Oversampling_x32	0x28

#define ODR_200				0x00
#define ODR_100				0x01
#define ODR_50				0x02
#define ODR_25				0x03
#define ODR_12p5			0x04
#define ODR_6p25			0x05
#define ODR_3p1				0x06
#define ODR_1p5				0x07
#define ODR_0p78			0x08
#define ODR_0p39			0x09
#define ODR_0p2				0x0A
#define ODR_0p1				0x0B
#define ODR_0p05			0x0C
#define ODR_0p02			0x0D
#define ODR_0p01			0x0E
#define ODR_0p006			0x0F
#define ODR_0p003			0x10
#define ODR_0p0015			0x11

#define IIR_coef_0			0x00
#define IIR_coef_1			0x02
#define IIR_coef_3			0x04
#define IIR_coef_7			0x06
#define IIR_coef_15			0x08
#define IIR_coef_31			0x0A
#define IIR_coef_63			0x0C
#define IIR_coef_127		0x0E


struct BMP390_calib_data
{
	float PAR_T1;
	float PAR_T2;
	float PAR_T3;
	float T_LIN;

	float PAR_P1;
	float PAR_P2;
	float PAR_P3;
	float PAR_P4;
	float PAR_P5;
	float PAR_P6;
	float PAR_P7;
	float PAR_P8;
	float PAR_P9;
	float PAR_P10;
	float PAR_P11;
};
struct BMP390_calib_data BMP390;


//static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
//{
//	HAL_I2C_Mem_Write(&hi2c3, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT, &Value, 1, 0x10000);
//}


//static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
//{
//	uint8_t value = 0;
//	HAL_I2C_Mem_Read(&hi2c3, Addr, Reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 1000);
//	return value;
//}


static void BMP390_Write_Byte(uint8_t reg, uint8_t data)
{
	//I2Cx_WriteData(BMP390_ADDRESS, reg, data);

	HAL_I2C_Mem_Write(&hi2c3, BMP390_ADDRESS, (uint16_t)reg, I2C_MEMADD_SIZE_8BIT, &data, 1, 0x10000);
}

static uint8_t BMP390_Read_Byte(uint8_t reg)
{
	//return I2Cx_ReadData(BMP390_ADDRESS, reg);

	uint8_t value = 0;
	HAL_I2C_Mem_Read(&hi2c3, BMP390_ADDRESS, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, 1000);
	return value;
}


static void Read_Parameters(void)
{
	uint8_t BUFF[16];

	unsigned int T1, T2, P5, P6;
	signed int T3, P1, P2, P3, P4, P7, P8, P9, P10, P11;

	// Temperature
	BUFF[0] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_T1_L);
	BUFF[1] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_T1_H);
	BUFF[2] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_T2_L);
	BUFF[3] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_T2_H);
	BUFF[4] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_T3);

	T1 = (BUFF[1]<<8) + BUFF[0];
	T2 = (BUFF[3]<<8) + BUFF[2];
	T3 = BUFF[4];
	if((T3>>7)==1) T3 = T3 - 256;

	BMP390.PAR_T1 = (float)T1/Total_Number_Neg_8;
	BMP390.PAR_T2 = (float)T2/Total_Number_30;
	BMP390.PAR_T3 = (float)T3/Total_Number_32/Total_Number_16;

	// Pressure
	BUFF[0] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P1_L);
	BUFF[1] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P1_H);
	BUFF[2] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P2_L);
	BUFF[3] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P2_H);
	BUFF[4] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P3);
	BUFF[5] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P4);
	BUFF[6] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P5_L);
	BUFF[7] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P5_H);
	BUFF[8] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P6_L);
	BUFF[9] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P6_H);
	BUFF[10] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P7);
	BUFF[11] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P8);
	BUFF[12] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P9_L);
	BUFF[13] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P9_H);
	BUFF[14] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P10);
	BUFF[15] = BMP390_Read_Byte(BMP390_REG_NVM_PAR_P11);

	P1 = (BUFF[1]<<8) + BUFF[0];
	P2 = (BUFF[3]<<8) + BUFF[2];
	P3 = BUFF[4];
	P4 = BUFF[5];

	P5 = (BUFF[7]<<8) + BUFF[6];
	P6 = (BUFF[9]<<8) + BUFF[8];

	P7 = BUFF[10];
	P8 = BUFF[11];
	P9 = (BUFF[13]<<8) + BUFF[12];
	P10 = BUFF[14];
	P11 = BUFF[15];

	if((P3>>7)==1) P3 = P3 - 256;
	if((P4>>7)==1) P4 = P4 - 256;
	if((P7>>7)==1) P7 = P7 - 256;
	if((P8>>7)==1) P8 = P8 - 256;
	if((P10>>7)==1) P10 = P10 - 256;
	if((P11>>7)==1) P11 = P11 - 256;

	if((P1>>15)==1) P1 = P1 - 65535;
	if((P2>>15)==1) P2 = P2 - 65535;
	if((P9>>15)==1) P9 = P9 - 65535;

	BMP390.PAR_P1 = ((float)P1-Total_Number_14)/Total_Number_20;
	BMP390.PAR_P2 = ((float)P2-Total_Number_14)/Total_Number_29;
	BMP390.PAR_P3 = (float)P3/Total_Number_32;
	BMP390.PAR_P4 = (float)P4/Total_Number_32/Total_Number_5;
	BMP390.PAR_P5 = (float)P5/Total_Number_Neg_3;
	BMP390.PAR_P6 = (float)P6/Total_Number_6;
	BMP390.PAR_P7 = (float)P7/Total_Number_8;
	BMP390.PAR_P8 = (float)P8/Total_Number_15;
	BMP390.PAR_P9 = (float)P9/Total_Number_32/Total_Number_16;
	BMP390.PAR_P10 = (float)P10/Total_Number_32/Total_Number_16;
	BMP390.PAR_P11 = (float)P11/Total_Number_32/Total_Number_32/Total_Number_1;
}


static float BMP390_compensate_temperature(uint32_t uncomp_temp, struct BMP390_calib_data *calib_data)
{
	float partial_data1;
	float partial_data2;

	partial_data1 = (float)(uncomp_temp - calib_data->PAR_T1);
	partial_data2 = (float)(partial_data1 * calib_data->PAR_T2);

	/* Update the compensated temperature in calib structure since this is
	* needed for pressure calculation */
	calib_data->T_LIN = partial_data2 + (partial_data1*partial_data1) * calib_data->PAR_T3;

	/* Returns compensated temperature */
	return calib_data->T_LIN;
}


static float BMP390_compensate_pressure(uint32_t uncomp_press, struct BMP390_calib_data *calib_data)
{
	/* Variable to store the compensated pressure */
	float comp_press;

	/* Temporary variables used for compensation */
	float partial_data1;
	float partial_data2;
	float partial_data3;
	float partial_data4;
	float partial_out1;
	float partial_out2;

	/* Calibration data */
	partial_data1 = calib_data->PAR_P6 * calib_data->T_LIN;
	partial_data2 = calib_data->PAR_P7 * (calib_data->T_LIN * calib_data->T_LIN);
	partial_data3 = calib_data->PAR_P8 * (calib_data->T_LIN * calib_data->T_LIN * calib_data->T_LIN);
	partial_out1 = calib_data->PAR_P5 + partial_data1 + partial_data2 + partial_data3;
	partial_data1 = calib_data->PAR_P2 * calib_data->T_LIN;
	partial_data2 = calib_data->PAR_P3 * (calib_data->T_LIN * calib_data->T_LIN);
	partial_data3 = calib_data->PAR_P4 * (calib_data->T_LIN * calib_data->T_LIN * calib_data->T_LIN);
	partial_out2 = (float)uncomp_press * (calib_data->PAR_P1 + partial_data1 + partial_data2 + partial_data3);
	partial_data1 = (float)uncomp_press * (float)uncomp_press;
	partial_data2 = calib_data->PAR_P9 + calib_data->PAR_P10 * calib_data->T_LIN;
	partial_data3 = partial_data1 * partial_data2;
	partial_data4 = partial_data3 + ((float)uncomp_press * (float)uncomp_press * (float)uncomp_press) * calib_data->PAR_P11;
	comp_press = partial_out1 + partial_out2 + partial_data4;

	return comp_press;
}





float Temperature_Read(void)
{
	uint8_t Temp_MSB,Temp_CSB,Temp_LSB;
	uint32_t Temperature;
	Temp_MSB = BMP390_Read_Byte(BMP390_REG_DATA_5);
	Temp_CSB = BMP390_Read_Byte(BMP390_REG_DATA_4);
	Temp_LSB = BMP390_Read_Byte(BMP390_REG_DATA_3);
    Temperature = (Temp_MSB<<16)+(Temp_CSB<<8)+Temp_LSB;

    return BMP390_compensate_temperature(Temperature, &BMP390);
}


float Pressure_Read(void)
{
	uint8_t Pressure_MSB,Pressure_CSB,Pressure_LSB;
	uint32_t Pressure;
    Pressure_MSB = BMP390_Read_Byte(BMP390_REG_DATA_2);
	Pressure_CSB = BMP390_Read_Byte(BMP390_REG_DATA_1);
	Pressure_LSB = BMP390_Read_Byte(BMP390_REG_DATA_0);
	Pressure = (Pressure_MSB<<16)+(Pressure_CSB<<8)+Pressure_LSB;

	return BMP390_compensate_pressure(Pressure, &BMP390);
}


uint8_t BMP390_Init(void)
{
	uint8_t BMP390_ID;
	BMP390_Write_Byte(BMP390_REG_CMD, 0xB6); //RESET

	ELSPIRE.delay_ms(100);

	BMP390_ID = BMP390_Read_Byte(BMP390_REG_CHIP_ID);  	//Read the CHIP_ID-0x60

	if(BMP390_ID == 0x60)
	{
		BMP390_Write_Byte(BMP390_REG_PWR_CTRL, 0x33);     	//Set Working mode and state of sensor
		BMP390_Write_Byte(BMP390_REG_IF_CONF, 0x00); 		//Serial interface settings
		BMP390_Write_Byte(BMP390_REG_INT_CTRL, 0x02); 		//Set interrupt config

		BMP390_Write_Byte(BMP390_REG_OSR, (T_Oversampling_x16+P_Oversampling_x16));
		BMP390_Write_Byte(BMP390_REG_ODR, ODR_0p78);
		BMP390_Write_Byte(BMP390_REG_CONFIG, IIR_coef_3);

		Read_Parameters();
	}

	return BMP390_ID;
}




void BMP390_process(void)
{
	MX_TouchGFX_Process();

	CalibrateChannel.Pressure_atm_temperature = Temperature_Read();
	CalibrateChannel.Pressure_atm = Pressure_Read();

	ELSPIRE.sleep(1500);
}









