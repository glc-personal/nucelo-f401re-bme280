/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : bme280.c
  * @brief          : BME280 program body
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
/* Includes ------------------------------------------------------------------*/
#include "bme280.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
BME280_HandleTypeDef hbme280;
BME280_RegisterTypeDef hum_lsb;
BME280_RegisterTypeDef hum_msb;
BME280_RegisterTypeDef temp_xlsb;
BME280_RegisterTypeDef temp_lsb;
BME280_RegisterTypeDef temp_msb;
BME280_RegisterTypeDef press_xlsb;
BME280_RegisterTypeDef press_lsb;
BME280_RegisterTypeDef press_msb;
BME280_RegisterTypeDef config;
BME280_RegisterTypeDef ctrl_meas;
BME280_RegisterTypeDef status;
BME280_RegisterTypeDef ctrl_hum;
BME280_RegisterTypeDef reset;
BME280_RegisterTypeDef id;
BME280_RegisterTypeDef calib00;
BME280_RegisterTypeDef calib01;
BME280_RegisterTypeDef calib02;
BME280_RegisterTypeDef calib03;
BME280_RegisterTypeDef calib04;
BME280_RegisterTypeDef calib05;
BME280_RegisterTypeDef calib06;
BME280_RegisterTypeDef calib07;
BME280_RegisterTypeDef calib08;
BME280_RegisterTypeDef calib09;
BME280_RegisterTypeDef calib10;
BME280_RegisterTypeDef calib11;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

// BME280 Init Function
BME280_ErrorTypeDef BME280_Init(uint8_t Interface)
{
	// Initialize
	hbme280.Interface = Interface;

	if (Interface == SPI)
	{
		// Set the mode
		hbme280.Mode = MODE00;
		hbme280.CPOL = 0;
		hbme280.CPHA = 0;

		// Set the pins
		//hbme280.CS = 0;
		//hbme280.SDI = 0;
		//hbme280.SDO = 0;
		//hbme280.SCK = 0;
	}
	else if (Interface == I2C)
	{
		// Set the pins
		//hbme280.SCL = 0;
		//hbme280.SDA = 0;
	}
	else
	{
		return BME280_ERROR;
	}

	hbme280.PMode = SLEEP;

	// Initialize the registers.
	BME280_RegistersInit();

	return BME280_OK;
}

BME280_ErrorTypeDef BME280_RegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Registers.
	_BME280_HumRegistersInit();
	_BME280_TempRegistersInit();
	_BME280_PressRegistersInit();
	_BME280_ConfigRegisterInit();
	_BME280_CtrlRegistersInit();
	_BME280_StatusRegisterInit();
	_BME280_ResetRegisterInit();
	_BME280_IdRegisterInit();
	_BME280_CalibXXRegistersInit();

	return rslt;
}

BME280_ErrorTypeDef _BME280_HumRegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Humidity Registers.
	hum_lsb.RegisterName = "hum_lsb";
	hum_lsb.Address = ADDRESS_HUM_LSB;
	hum_lsb.Bits = *(uint8_t *) NULL;
	hum_lsb.ResetState = 0x00;
	hum_lsb.Type = READ_ONLY;

	hum_msb.RegisterName = "hum_msb";
	hum_msb.Address = ADDRESS_HUM_MSB;
	hum_msb.Bits = *(uint8_t *) NULL;
	hum_msb.ResetState = 0x80;
	hum_msb.Type = READ_ONLY;

	return rslt;
}

BME280_ErrorTypeDef _BME280_TempRegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Temperature Registers
	temp_xlsb.RegisterName = "temp_xlsb";
	temp_xlsb.Address = ADDRESS_TEMP_XLSB;
	temp_xlsb.Bits = *(uint8_t *) NULL;
	temp_xlsb.ResetState = 0x00;
	temp_xlsb.Type = READ_ONLY;

	temp_lsb.RegisterName = "temp_lsb";
	temp_lsb.Address = ADDRESS_TEMP_LSB;
	temp_lsb.Bits = *(uint8_t *) NULL;
	temp_lsb.ResetState = 0x00;
	temp_lsb.Type = READ_ONLY;

	temp_msb.RegisterName = "temp_msb";
	temp_msb.Address = ADDRESS_TEMP_MSB;
	temp_msb.Bits = *(uint8_t *) NULL;
	temp_msb.ResetState = 0x80;
	temp_msb.Type = READ_ONLY;

	return rslt;
}


BME280_ErrorTypeDef _BME280_PressRegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Pressure Registers
	press_xlsb.RegisterName = "press_xlsb";
	press_xlsb.Address = ADDRESS_PRESS_XLSB;
	press_xlsb.Bits = *(uint8_t *) NULL;
	press_xlsb.ResetState = 0x00;
	press_xlsb.Type = READ_ONLY;

	press_lsb.RegisterName = "press_lsb";
	press_lsb.Address = ADDRESS_PRESS_LSB;
	press_lsb.Bits = *(uint8_t *) NULL;
	press_lsb.ResetState = 0x00;
	press_lsb.Type = READ_ONLY;

	press_msb.RegisterName = "press_msb";
	press_msb.Address = ADDRESS_PRESS_MSB;
	press_msb.Bits = *(uint8_t *) NULL;
	press_msb.ResetState = 0x80;
	press_msb.Type = READ_ONLY;

	return rslt;
}

BME280_ErrorTypeDef _BME280_ConfigRegisterInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Config Register.
	config.RegisterName = "config";
	config.Address = ADDRESS_CONFIG;
	config.Bits = *(uint8_t *) NULL;
	config.ResetState = 0x00;
	config.Type = READ_WRITE;

	return rslt;
}

BME280_ErrorTypeDef _BME280_CtrlRegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Ctrl Registers.
	ctrl_meas.RegisterName = "ctrl_meas";
	ctrl_meas.Address = ADDRESS_CTRL_MEAS;
	ctrl_meas.Bits = *(uint8_t *) NULL;
	ctrl_meas.ResetState = 0x00;
	ctrl_meas.Type = READ_WRITE;

	ctrl_hum.RegisterName = "ctrl_hum";
	ctrl_hum.Address = ADDRESS_CTRL_HUM;
	ctrl_hum.Bits = *(uint8_t *) NULL;
	ctrl_hum.ResetState = 0x00;
	ctrl_hum.Type = READ_WRITE;

	return rslt;
}

BME280_ErrorTypeDef _BME280_StatusRegisterInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Status Register.
	status.RegisterName = "status";
	status.Address = ADDRESS_STATUS;
	status.Bits = *(uint8_t *) NULL;
	status.ResetState = 0x00;
	status.Type = READ_ONLY;

	return rslt;
}

BME280_ErrorTypeDef _BME280_ResetRegisterInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Reset Register.
	reset.RegisterName = "reset";
	reset.Address = ADDRESS_RESET;
	reset.Bits = *(uint8_t *) NULL;
	reset.ResetState = 0x00;
	reset.Type = WRITE_ONLY;

	return rslt;
}

BME280_ErrorTypeDef _BME280_IdRegisterInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the Id Register.
	id.RegisterName = "id";
	id.Address = ADDRESS_ID;
	id.Bits = *(uint8_t *) NULL;
	id.ResetState = 0x60;
	id.Type = READ_ONLY;

	return rslt;
}

BME280_ErrorTypeDef _BME280_CalibXXRegistersInit(void)
{
	// Variables
	BME280_ErrorTypeDef rslt = BME280_OK;

	// Initialize the CalibXX Registers.
	calib00.RegisterName = "calib00";
	calib00.Address = ADDRESS_CALIB00;
	calib00.Bits = *(uint8_t *) NULL;
	calib00.ResetState = 0x00;
	calib00.Type = READ_ONLY;

	calib01.RegisterName = "calib01";
	calib01.Address = ADDRESS_CALIB01;
	calib01.Bits = *(uint8_t *) NULL;
	calib01.ResetState = 0x00;
	calib01.Type = READ_ONLY;

	return rslt;
}


/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
