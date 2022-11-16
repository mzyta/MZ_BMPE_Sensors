/*
 * MZ_BMPE_Sensors.c
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */


#include "MZ_BMPE_Sensors.h"
#include "MZ_BMPE_Interface.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------Static variables definitions----------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t DeviceCount = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------Static functions headers------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Pressure oversaampling functions
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);

//Temperature oversampling sunctions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------Functions-------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Device init function
MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceAddress, MZ_BMPE_DeviceType_t DeviceType, MZ_BMPE_CommunicationProtocol_t CommunicationProtocol)
{
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{

		//Checking device address and writing it to device pointer
		if(DeviceAddress == 0)
		{
			if(CommunicationProtocol == SPI)
			{
				DevicePtr->DeviceAddress = DeviceAddress;
			}
			else
			{
				return BMPE_INIT_ERROR;
			}

		}
		else
		{
			DevicePtr->DeviceAddress = DeviceAddress;
		}

		//Checking device type and writing it to device pointer
		if(DeviceType == 0)
		{
			return BMPE_INIT_ERROR;
		}
		else
		{
			DevicePtr->DeviceType = DeviceType;
		}

		//Checking communication protocol and writing it to device pointer
		if(CommunicationProtocol == 0)
		{
			return BMPE_INIT_ERROR;
		}
		else
		{
			DevicePtr->CommunicationProtocol = CommunicationProtocol;
		}

		//Creating device Id
		DeviceCount += 1;
		DevicePtr->DeviceId = DeviceCount;

	}

	return BMPE_OK;

}

//Function binding I2C handle with device. If you comment I2C definition in MZ_BMPE_Config.h this function will be not compiled
#ifdef MZ_BMPE_HAL_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_Registration(MZ_BMPE_Device_t *DevicePtr, I2C_HandleTypeDef *i2cHandle)
{
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		if(i2cHandle == 0)
		{
			return BMPE_I2C_HANDLE_ERROR;
		}
		else
		{
			DevicePtr->i2cHandle = i2cHandle;
		}
	}

	return BMPE_OK;
}
#endif

//Function binding SPI handle with device. If you comment SPI definition in MZ_BMPE_Config.h this function will be not compiled
#ifdef MZ_BMPE_HAL_SPI
MZ_BMPE_Errors_t MZ_BMPE_SPI_Registration(MZ_BMPE_Device_t *DevicePtr, SPI_HandleTypeDef *spiHandle)
{
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		if(i2cHandle == 0)
		{
			return BMPE_SPI_HANDLE_ERROR;
		}
		else
		{
			DevicePtr->spiHandle = spiHandle;
		}
	}

	return BMPE_OK;
}
#endif


//Function to set pressure oversampling for devices
MZ_BMPE_Errors_t MZ_BMPE_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	MZ_BMPE_Errors_t Result;

	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		if(((DevicePtr->DeviceType == BMP280) && OversamplingValue > 7) || ((DevicePtr->DeviceType == BME280) && OversamplingValue > 7) || ((DevicePtr->DeviceType == BMP180) && OversamplingValue > 3))
		{
			return BMPE_OVERSAMPLING_ERROR;
		}
		else
		{
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = MZ_BMPE_BMP180_SetPressureOversampling(DevicePtr, OversamplingValue);
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetPressureOversampling(DevicePtr, OversamplingValue);
			}
		}

	}


	return Result;
}

//Function to set pressure oversampling for BMP180
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	MZ_BMPE_Errors_t Result = 0;

	uint8_t CtrlMeasRegVal = 0;

	Result = MZ_BMPE_ReadRegister(DevicePtr, MZ_BMP180_CTRL_MEAS, &CtrlMeasRegVal);

	CtrlMeasRegVal &= 0x3F;

	CtrlMeasRegVal |= (OversamplingValue<<6);

	Result = MZ_BMPE_WriteRegister(DevicePtr, MZ_BMP180_CTRL_MEAS, &CtrlMeasRegVal);

	return Result;
}


//Function to set pressure oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	MZ_BMPE_Errors_t Result = 0;

	uint8_t CtrlMeasRegVal = 0;

	Result = MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal);

	CtrlMeasRegVal &= 0xE3;

	CtrlMeasRegVal |= (OversamplingValue<<2);

	Result = MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal);

	return Result;
}

//Function to set temperature oversampling for devices
MZ_BMPE_Errors_t MZ_BMPE_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	MZ_BMPE_Errors_t Result;

	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		if(OversamplingValue > 7)
		{
			return BMPE_OVERSAMPLING_ERROR;
		}
		else
		{
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = BMPE_WRONG_DEVICE_TYPE;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetTemperatureOversampling(DevicePtr, OversamplingValue);
			}
		}

	}


	return Result;
}


//Function to set temperature oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	MZ_BMPE_Errors_t Result = 0;

	uint8_t CtrlMeasRegVal = 0;

	Result = MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal);

	CtrlMeasRegVal &= 0x1F;

	CtrlMeasRegVal |= (OversamplingValue<<5);

	Result = MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal);

	return Result;
}
