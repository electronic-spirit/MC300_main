/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "GlobalVariables.h"
#include "ELSPIRE_OS.h"
#include "ModBusSlave.h"
#include "UART_OUT.h"
#include "UART_IN.h"
#include "UART_PRESSURE.h"
#include "SwitchOff.h"
#include "BQ40Z50.h"
#include "ModBusMaster.h"
#include "Buttons.h"
#include "Units.h"
#include "BMP390.h"
#include "CD4052.h"
#include "Save.h"
#include "ThermocoupleMath.h"
#include "ThermoresistanceMath.h"
#include "ThermoCalculator.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern int analogHours;
extern int analogMinutes;
extern int analogSeconds;
extern uint32_t Xglobal;
extern uint32_t Yglobal;
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BT1_Pin GPIO_PIN_3
#define BT1_GPIO_Port GPIOE
#define T_CS_Pin GPIO_PIN_15
#define T_CS_GPIO_Port GPIOA
#define PEN_IRQ_Pin GPIO_PIN_5
#define PEN_IRQ_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */
#define IN_address 					0x0B
#define PressureAddress				0x01
#define OUT_address 				0x01

#define IN_module_change 			0x01
#define Pressure_module_change		0x02
#define OUT_module_change 			0x04
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
