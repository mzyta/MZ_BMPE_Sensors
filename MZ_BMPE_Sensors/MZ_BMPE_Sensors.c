/*
 * MZ_BMPE_Sensors.c
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */


#include "MZ_BMPE_Sensors.h"

static uint8_t DeviceCount = 0;


//Device init function
MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceAddress, MZ_BMPE_DeviceType_t DeviceType, MZ_BMPE_CommunicationProtocol_t CommunicationProtocol)
{
	if(DevicePtr == 0)
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

#ifdef MZ_BMPE_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_Registration(MZ_BMPE_Device_t *DevicePtr, I2C_HandleTypeDef *i2cHandle)
{
	if(DevicePtr == 0)
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

#ifdef MZ_BMPE_SPI
MZ_BMPE_Errors_t MZ_BMPE_SPI_Registration(MZ_BMPE_Device_t *DevicePtr, SPI_HandleTypeDef *spiHandle)
{
	if(DevicePtr == 0)
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
