/*
 * MZ_BMPE_Sensors.c
 *
 *  Created on: Nov 15, 2022
 *      Author: zytam
 */


#include "MZ_BMPE_Sensors.h"

static uint8_t DeviceCount = 0;


MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceId, uint8_t DeviceAddress, uint8_t DeviceType, uint8_t CommunicationProtocol)
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
			return BMPE_INIT_ERROR;
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
		DevicePtr->DeviceId = DeviceId;

	}

	return BMPE_OK;

}
