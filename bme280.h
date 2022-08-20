/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bme280.h
  * @brief          : Header for bme280.c file.
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
#ifndef __BME280_H
#define __BME280_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

// Expected Chip Id from reading the Id Register.
#define CHIP_ID 0x60

// Soft Reset for the Reset Register
#define SOFT_RESET 0xB6

// Read and Write RW Bit Masks
#define READ_BIT_MASK = 0xFF
#define WRITE_BIT_MASK = 0x7F

// Register Addresses
#define ADDRESS_HUM_LSB 0xFE
#define ADDRESS_HUM_MSB 0xFD
#define ADDRESS_TEMP_XLSB 0xFC
#define ADDRESS_TEMP_LSB 0xFB
#define ADDRESS_TEMP_MSB 0xFA
#define ADDRESS_PRESS_XLSB 0xF9
#define ADDRESS_PRESS_LSB 0xF8
#define ADDRESS_PRESS_MSB 0xF7
#define ADDRESS_CONFIG 0xF5
#define ADDRESS_CTRL_MEAS 0xF4
#define ADDRESS_STATUS 0xF3
#define ADDRESS_CTRL_HUM 0xF2
#define ADDRESS_RESET 0xE0
#define ADDRESS_ID 0xD0
#define ADDRESS_CALIB00 0x88
#define ADDRESS_CALIB01 0x89
#define ADDRESS_CALIB02 0x90
#define ADDRESS_CALIB03 0x91
#define ADDRESS_CALIB04 0x92
#define ADDRESS_CALIB05 0x93
#define ADDRESS_CALIB06 0x94
#define ADDRESS_CALIB07 0x95
#define ADDRESS_CALIB08 0x96
#define ADDRESS_CALIB09 0x97
#define ADDRESS_CALIB10 0x98
#define ADDRESS_CALIB11 0x99

typedef enum	/* BME280_ModeTypeDef */
{
	SLEEP,			/* Sleep Power Mode:  no operation, all registers accessible, selected after power-on reset (POC) */
	FORCED,			/* Force Power Mode: perform one measurement, store the results and return to sleep mode */
	NORMAL = 0b11	/* Normal Power Mode: perpetual cycling of measurements and inactive periods */
} BME280_ModeTypeDef;

typedef enum	/* BME280_ErrorTypeDef */
{
	BME280_OK,	/* No error */
	BME280_ERROR
} BME280_ErrorTypeDef;

typedef enum	/* BME280_InterfaceTypeDef */
{
	SPI,	/* SPI Interface */
	I2C		/* I2C Interface */
} BME280_InterfaceTypeDef;

typedef enum	/* SPI_ModeTypeDef */
{
	MODE00,	/* CPOL = 0, CPHA = 0 */
	MODE11	/* CPOL = 1, CPHA = 1 */
} SPI_ModeTypeDef;

typedef enum	/* Register_TypeTypeDef */
{
	WRITE_ONLY,	/* Write-only register */
	READ_ONLY,	/* Read-only register */
	READ_WRITE	/* Read/Write register */
} Register_TypeTypeDef;

typedef enum	/* osrs_SettingTypeDef */
{
	SKIPPED = 0b000,	/* Skipped (output set to 0x80000) */
	OVERSAMPLINGX1,		/* oversampling x1 */
	OVERSAMPLINGX2,		/* oversampling x2 */
	OVERSAMPLINGX4,		/* oversampling x4 */
	OVERSAMPLINGX8,		/* oversampling x8 */
	OVERSAMPLINGX16		/* oversampling x16 */
} osrs_SettingTypeDef;

typedef enum	/* t_sb_SettingTypeDef */
{
	T_STANDBY_000 = 0b000,	/* t_standby = 0.5 ms */
	T_STANDBY_001,			/* t_standby = 62.5 ms */
	T_STANDBY_010,			/* t_standby = 125 ms */
	T_STANDBY_011,			/* t_standby = 250 ms */
	T_STANDBY_100,			/* t_standby = 500 ms */
	T_STANDBY_101,			/* t_standby = 1000 ms */
	T_STANDBY_110,			/* t_standby = 10 ms */
	T_STANDBY_111			/* t_standby = 20 ms */
} t_sb_SettingTypeDef;

typedef enum	/* filter_SettingTypeDef */
{
	FILTER_OFF = 0b000,		/* Filter off */
	FILTER_COEFFICIENT_2,	/* IIR Filter Time Constant = 2 */
	FILTER_COEFFICIENT_4,	/* IIR Filter Time Constant = 4 */
	FILTER_COEFFICIENT_8,	/* IIR Filter Time Constant = 8 */
	FILTER_COEFFICIENT_16,	/* IIR Filter Time Constant = 16 */
} filter_SettingTypeDef;

typedef enum	/* spixw_en_SettingTypeDef */
{
	spi4w_en,	/* 4-wire SPI enable setting */
	spi3w_en	/* 3-wire SPI enable setting */
} spixw_en_SettingTypeDef;

typedef struct
{
	char *RegisterName;	/* Register Name */
	uint8_t Address;	/* Address */
	uint8_t Bits;		/* 8-bit Register */
	uint8_t ResetState;	/* Reset State */
	char Type;			/* Register Type */
} BME280_RegisterTypeDef;

typedef struct
{
	uint8_t Interface;  /* Communication Interface (SPI(0) or I2C(1)) */
	uint8_t Mode; 		/* Mode -- SPI */
	uint8_t CPOL;  		/* Clock Polarity -- SPI */
	uint8_t CPHA;  		/* Clock Phase -- SPI */
	uint8_t CS;    		/* Chip Select, Active Low -- SPI */
	uint8_t SDI;  		/* Serial Data Input -- SPI */
	uint8_t SDO;   		/* Serial Data Output -- SPI */
	uint8_t SCK;   		/* Serial Clock -- SPI */
	uint8_t SDA;  		/* Serial Data -- I2C */
	uint8_t SCL;  		/* Serial Clock -- I2C */
	uint8_t PMode;		/* Power Mode */
} BME280_HandleTypeDef;

typedef struct
{
	uint8_t ControlByte;	/* BME280_RegisterTypeDef.Address & RW_BIT_MASK */
	uint8_t DataByte[];		/* Data byte array */
} SPI_RW_TypeDef;

BME280_ErrorTypeDef BME280_Init(uint8_t Interface);		/* Initializes the BME280 Handle */

BME280_ErrorTypeDef BME280_RegistersInit(void);			/* Initializes all BME280 Registers */

BME280_ErrorTypeDef _BME280_HumRegistersInit(void);		/* Initializes the Humidity Registers */
BME280_ErrorTypeDef _BME280_TempRegistersInit(void);	/* Initializes the Temperature Registers */
BME280_ErrorTypeDef _BME280_PressRegistersInit(void);	/* Initializes the Pressure Registers */
BME280_ErrorTypeDef _BME280_ConfigRegisterInit(void);	/* Initializes the Config Register */
BME280_ErrorTypeDef _BME280_CtrlRegistersInit(void);	/* Initializes the Ctrl Registers */
BME280_ErrorTypeDef _BME280_StatusRegisterInit(void);	/* Initializes the Status Register */
BME280_ErrorTypeDef _BME280_ResetRegisterInit(void);	/* Initializes the Reset Register */
BME280_ErrorTypeDef _BME280_IdRegisterInit(void);		/* Initializes the Id Register */
BME280_ErrorTypeDef _BME280_CalibXXRegistersInit(void);	/* Initializes the CalibXX Registers */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __BME280_H */
