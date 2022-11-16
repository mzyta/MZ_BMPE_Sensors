/*
 * MZ_BMPE_Interface.c
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */
#include "main.h"


#include "MZ_BMPE_Interface.h"

#ifdef MZ_BMPE_HAL_I2C
#include "MZ_BMPE_i2c.h"
#endif

#ifdef MZ_BMPE_HAL_SPI
#include "MZ_BMPE_spi.h"
#endif

MZ_BMPE_Errors_t MZ_BMPE_ReadRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue)
{
	#ifdef MZ_BMPE_HAL_I2C
	if(DevicePtr->CommunicationProtocol == I2C)
	{
		return MZ_BMPE_I2C_ReadRegister(DevicePtr->i2cHandle,DevicePtr->DeviceAddress, Register, RegisterValue);
	}
	#endif

	#ifdef MZ_BMPE_HAL_SPI
	if(DevicePtr->CommunicationProtocol == SPI)
	{
		return MZ_BMPE_SPI_ReadRegister(DevicePtr, Register, RegisterValue);
	}
	#endif

	return BMPE_READ_REGISTER_ERROR;
}

MZ_BMPE_Errors_t MZ_BMPE_WriteRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue)
{
	#ifdef MZ_BMPE_HAL_I2C
	if(DevicePtr->CommunicationProtocol == I2C)
	{
		return MZ_BMPE_I2C_WriteRegister(DevicePtr->i2cHandle,DevicePtr->DeviceAddress, Register, RegisterValue);
	}
	#endif

	#ifdef MZ_BMPE_HAL_SPI
	if(DevicePtr->CommunicationProtocol == SPI)
	{
		return MZ_BMPE_SPI_WriteRegister(DevicePtr, Register, RegisterValue);
	}
	#endif

	return BMPE_WRITE_REGISTER_ERROR;
}
