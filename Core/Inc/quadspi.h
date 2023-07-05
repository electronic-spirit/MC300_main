/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    quadspi.h
  * @brief   This file contains all the function prototypes for
  *          the quadspi.c file
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
#ifndef __QUADSPI_H__
#define __QUADSPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern QSPI_HandleTypeDef hqspi;

/* USER CODE BEGIN Private defines */

#define MEMORY_FLASH_SIZE				0x800000 /* 64Mbit =>8Mbyte */
#define MEMORY_BLOCK_SIZE				0x10000   /* 128 blocks of 64KBytes */
#define MEMORY_SECTOR_SIZE				0x1000    /* 4kBytes */
#define MEMORY_PAGE_SIZE				0x100     /* 256 bytes */

#define MEM_FLASH_SIZE 64U 	// 256 MB-bit
/// Mem big block size in KB
#define MEM_BLOCK_SIZE 64U		// 64 KB: 256 pages
/// Mem small block size in KB
#define MEM_SBLOCK_SIZE 32U		// 32 KB: 128 pages
/// Mem sector size in KB
#define MEM_SECTOR_SIZE 4U		// 4 KB : 16 pages
/// Mem page size in bytes
#define MEM_PAGE_SIZE  256U		// 256 byte : 1 page

#define N25Q128A_DUMMY_CYCLES_READ           8
#define N25Q128A_DUMMY_CYCLES_READ_QUAD      10

#define N25Q128A_BULK_ERASE_MAX_TIME         250000
#define N25Q128A_SECTOR_ERASE_MAX_TIME       3000
#define N25Q128A_SUBSECTOR_ERASE_MAX_TIME    800

/**
  * @brief  N25Q128A Commands
  */
/* Reset Operations */
#define RESET_ENABLE_CMD                     0x66
#define RESET_MEMORY_CMD                     0x99

/* Identification Operations */
#define READ_ID_CMD                          0x9E
#define READ_ID_CMD2                         0x9F
#define MULTIPLE_IO_READ_ID_CMD              0xAF
#define READ_SERIAL_FLASH_DISCO_PARAM_CMD    0x5A

/* Read Operations */
#define READ_CMD                             0x03
#define FAST_READ_CMD                        0x0B
#define DUAL_OUT_FAST_READ_CMD               0x3B
#define DUAL_INOUT_FAST_READ_CMD             0xBB
#define QUAD_OUT_FAST_READ_CMD               0x6B
#define QUAD_INOUT_FAST_READ_CMD             0xEB

/* Write Operations */
#define WRITE_ENABLE_CMD                     0x06
#define WRITE_DISABLE_CMD                    0x04

/* Register Operations */
#define READ_STATUS_REG_CMD                  0x05
#define WRITE_STATUS_REG_CMD                 0x01

#define READ_LOCK_REG_CMD                    0xE8
#define WRITE_LOCK_REG_CMD                   0xE5

#define READ_FLAG_STATUS_REG_CMD             0x70
#define CLEAR_FLAG_STATUS_REG_CMD            0x50

#define READ_NONVOL_CFG_REG_CMD              0xB5
#define WRITE_NONVOL_CFG_REG_CMD             0xB1

#define READ_VOL_CFG_REG_CMD                 0x85
#define WRITE_VOL_CFG_REG_CMD                0x81

#define READ_ENHANCED_VOL_CFG_REG_CMD        0x65
#define WRITE_ENHANCED_VOL_CFG_REG_CMD       0x61

/* Program Operations */
#define PAGE_PROG_CMD                        0x02
#define DUAL_IN_FAST_PROG_CMD                0xA2
#define EXT_DUAL_IN_FAST_PROG_CMD            0xD2
#define QUAD_IN_FAST_PROG_CMD                0x32
#define EXT_QUAD_IN_FAST_PROG_CMD            0x12

/* Erase Operations */
#define SUBSECTOR_ERASE_CMD                  0x20
//#define SECTOR_ERASE_CMD                     0xD8
#define BULK_ERASE_CMD                       0xC7

#define PROG_ERASE_RESUME_CMD                0x7A
#define PROG_ERASE_SUSPEND_CMD               0x75

/* One-Time Programmable Operations */
#define READ_OTP_ARRAY_CMD                   0x4B
#define PROG_OTP_ARRAY_CMD                   0x42

/**
  * @brief  N25Q128A Registers
  */
/* Status Register */
#define N25Q128A_SR_WIP                      ((uint8_t)0x01)    /*!< Write in progress */
#define N25Q128A_SR_WREN                     ((uint8_t)0x02)    /*!< Write enable latch */
#define N25Q128A_SR_BLOCKPR                  ((uint8_t)0x5C)    /*!< Block protected against program and erase operations */
#define N25Q128A_SR_PRBOTTOM                 ((uint8_t)0x20)    /*!< Protected memory area defined by BLOCKPR starts from top or bottom */
#define N25Q128A_SR_SRWREN                   ((uint8_t)0x80)    /*!< Status register write enable/disable */

/* Nonvolatile Configuration Register */
#define N25Q128A_NVCR_LOCK                   ((uint16_t)0x0001) /*!< Lock nonvolatile configuration register */
#define N25Q128A_NVCR_DUAL                   ((uint16_t)0x0004) /*!< Dual I/O protocol */
#define N25Q128A_NVCR_QUAB                   ((uint16_t)0x0008) /*!< Quad I/O protocol */
#define N25Q128A_NVCR_RH                     ((uint16_t)0x0010) /*!< Reset/hold */
#define N25Q128A_NVCR_ODS                    ((uint16_t)0x01C0) /*!< Output driver strength */
#define N25Q128A_NVCR_XIP                    ((uint16_t)0x0E00) /*!< XIP mode at power-on reset */
#define N25Q128A_NVCR_NB_DUMMY               ((uint16_t)0xF000) /*!< Number of dummy clock cycles */

/* Volatile Configuration Register */
#define N25Q128A_VCR_WRAP                    ((uint8_t)0x03)    /*!< Wrap */
#define N25Q128A_VCR_XIP                     ((uint8_t)0x08)    /*!< XIP */
#define N25Q128A_VCR_NB_DUMMY                ((uint8_t)0xF0)    /*!< Number of dummy clock cycles */

/* Enhanced Volatile Configuration Register */
#define N25Q128A_EVCR_ODS                    ((uint8_t)0x07)    /*!< Output driver strength */
#define N25Q128A_EVCR_VPPA                   ((uint8_t)0x08)    /*!< Vpp accelerator */
#define N25Q128A_EVCR_RH                     ((uint8_t)0x10)    /*!< Reset/hold */
#define N25Q128A_EVCR_DUAL                   ((uint8_t)0x40)    /*!< Dual I/O protocol */
#define N25Q128A_EVCR_QUAD                   ((uint8_t)0x80)    /*!< Quad I/O protocol */

/* Flag Status Register */
#define N25Q128A_FSR_PRERR                   ((uint8_t)0x02)    /*!< Protection error */
#define N25Q128A_FSR_PGSUS                   ((uint8_t)0x04)    /*!< Program operation suspended */
#define N25Q128A_FSR_VPPERR                  ((uint8_t)0x08)    /*!< Invalid voltage during program or erase */
#define N25Q128A_FSR_PGERR                   ((uint8_t)0x10)    /*!< Program error */
#define N25Q128A_FSR_ERERR                   ((uint8_t)0x20)    /*!< Erase error */
#define N25Q128A_FSR_ERSUS                   ((uint8_t)0x40)    /*!< Erase operation suspended */
#define N25Q128A_FSR_READY                   ((uint8_t)0x80)    /*!< Ready or command in progress */



#define W25Q_WRITE_ENABLE 0x06U			///< sets WEL bit, must be set before any write/program/erase
#define W25Q_WRITE_DISABLE 0x04U		///< resets WEL bit (state after power-up)
#define W25Q_ENABLE_VOLATILE_SR 0x50U	///< check 7.1 in datasheet
#define W25Q_READ_SR1 0x05U				///< read status-register 1
#define W25Q_READ_SR2 0x35U				///< read status-register 2
#define W25Q_READ_SR3 0x15U				///< read ststus-register 3
#define W25Q_WRITE_SR1 0x01U			///< write status-register 1 (8.2.5)
#define W25Q_WRITE_SR2 0x31U			///< write status-register 2 (8.2.5)
#define W25Q_WRITE_SR3 0x11U			///< write status-register 3 (8.2.5)
#define W25Q_READ_EXT_ADDR_REG 0xC8U	///< read extended addr reg (only in 3-byte mode)
#define W25Q_WRITE_EXT_ADDR_REG 0xC8U	///< write extended addr reg (only in 3-byte mode)
#define W25Q_ENABLE_4B_MODE 0xB7U			///< enable 4-byte mode (128+ MB address)
#define W25Q_DISABLE_4B_MODE 0xE9U			///< disable 4-byte mode (<=128MB)
#define W25Q_READ_DATA 0x03U				///< read data by standard SPI
#define W25Q_READ_DATA_4B 0x13U				///< read data by standard SPI in 4-byte mode
#define W25Q_FAST_READ 0x0BU				///< highest FR speed (8.2.12)
#define W25Q_FAST_READ_4B 0x0CU				///< fast read in 4-byte mode
#define W25Q_FAST_READ_DUAL_OUT 0x3BU		///< fast read in dual-SPI OUTPUT (8.2.14)
#define W25Q_FAST_READ_DUAL_OUT_4B 0x3CU	///< fast read in dual-SPI OUTPUT in 4-byte mode
#define W25Q_FAST_READ_QUAD_OUT 0x6BU		///< fast read in quad-SPI OUTPUT (8.2.16)
#define W25Q_FAST_READ_QUAD_OUT_4B 0x6CU	///< fast read in quad-SPI OUTPUT in 4-byte mode
#define W25Q_FAST_READ_DUAL_IO 0xBBU		///< fast read in dual-SPI I/O (address transmits by both lines)
#define W25Q_FAST_READ_DUAL_IO_4B 0xBCU		///< fast read in dual-SPI I/O in 4-byte mode
#define W25Q_FAST_READ_QUAD_IO 0xEBU		///< fast read in quad-SPI I/O (address transmits by quad lines)
#define W25Q_FAST_READ_QUAD_IO_4B 0xECU		///< fast read in quad-SPI I/O in 4-byte mode
#define W25Q_SET_BURST_WRAP 0x77U			///< use with quad-I/O (8.2.22)
#define W25Q_PAGE_PROGRAM 0x02U				///< program page (256bytes) by single SPI line
#define W25Q_PAGE_PROGRAM_4B 0x12U			///< program page by single SPI in 4-byte mode
#define W25Q_PAGE_PROGRAM_QUAD_INP 0x32U	///< program page (256bytes) by quad SPI lines
#define W25Q_PAGE_PROGRAM_QUAD_INP_4B 0x34U ///< program page by quad SPI in 4-byte mode
#define W25Q_SECTOR_ERASE 0x20U				///< sets all 4Kbyte sector with 0xFF (erases it)
#define W25Q_SECTOR_ERASE_4B 0x21U			///< sets all 4Kbyte sector with 0xFF in 4-byte mode
#define W25Q_32KB_BLOCK_ERASE 0x52U			///< sets all 32Kbyte block with 0xFF
#define W25Q_64KB_BLOCK_ERASE 0xD8U			///< sets all 64Kbyte block with 0xFF
#define W25Q_64KB_BLOCK_ERASE_4B 0xDCU		///< sets all 64Kbyte sector with 0xFF in 4-byte mode
#define W25Q_CHIP_ERASE 0xC7U				///< fill all the chip with 0xFF
//#define W25Q_CHIP_ERASE 0x60U				///< another way to erase chip
#define W25Q_ERASEPROG_SUSPEND 0x75U		///< suspend erase/program operation (can be applied only when SUS=0, BYSY=1)
#define W25Q_ERASEPROG_RESUME 0x7AU			///< resume erase/program operation (if SUS=1, BUSY=0)
#define W25Q_POWERDOWN 0xB9U				///< powers down the chip (power-up by reading ID)
#define W25Q_POWERUP 0xABU					///< release power-down
#define W25Q_DEVID 0xABU					///< read Device ID (same as powerup)
#define W25Q_FULLID 0x90U					///< read Manufacturer ID & Device ID
#define W25Q_FULLID_DUAL_IO 0x92U			///< read Manufacturer ID & Device ID by dual I/O
#define W25Q_FULLID_QUAD_IO 0x94U			///< read Manufacturer ID & Device ID by quad I/O
#define W25Q_READ_UID 0x4BU					///< read unique chip 64-bit ID
#define W25Q_READ_JEDEC_ID 0x9FU			///< read JEDEC-standard ID
#define W25Q_READ_SFDP 0x5AU				///< read SFDP register parameters
#define W25Q_ERASE_SECURITY_REG 0x44U		///< erase security registers
#define W25Q_PROG_SECURITY_REG 0x42U		///< program security registers
#define W25Q_READ_SECURITY_REG 0x48U		///< read security registers
#define W25Q_IND_BLOCK_LOCK 0x36U			///< make block/sector read-only
#define W25Q_IND_BLOCK_UNLOCK 0x39U			///< disable block/sector protection
#define W25Q_READ_BLOCK_LOCK 0x3DU			///< check block/sector protection
#define W25Q_GLOBAL_LOCK 0x7EU				///< global read-only protection enable
#define W25Q_GLOBAL_UNLOCK 0x98U			///< global read-only protection disable
#define W25Q_ENABLE_RST 0x66U				///< enable software-reset ability
#define W25Q_RESET 0x99U					///< make software reset


#define CHIP_ERASE_CMD 0xC7
#define READ_STATUS_REG_CMD 0x05
#define WRITE_ENABLE_CMD 0x06
#define VOLATILE_SR_WRITE_ENABLE             0x50
#define READ_STATUS_REG2_CMD 0x35
#define WRITE_STATUS_REG2_CMD 0x31
#define READ_STATUS_REG3_CMD 0x15
#define WRITE_STATUS_REG3_CMD                0x11
#define SECTOR_ERASE_CMD 0x20
#define BLOCK_ERASE_CMD 0xD8
#define QUAD_IN_FAST_PROG_CMD 0x32
#define FAST_PROG_CMD 0x02
#define QUAD_OUT_FAST_READ_CMD 0x6B
#define DUMMY_CLOCK_CYCLES_READ_QUAD 8
#define QUAD_IN_OUT_FAST_READ_CMD 0xEB
#define RESET_ENABLE_CMD 0x66
#define RESET_EXECUTE_CMD 0x99


/* USER CODE END Private defines */

void MX_QUADSPI_Init(void);

/* USER CODE BEGIN Prototypes */
uint8_t CSP_QUADSPI_Init(void);
uint8_t CSP_QSPI_EnableMemoryMappedMode2(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __QUADSPI_H__ */

