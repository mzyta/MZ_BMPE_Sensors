/*
 * MZ_BMPE_i2c.c
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */


#include "MZ_BMPE_i2c.h"

#ifdef MZ_BMPE_HAL_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_ReadRegister(I2C_HandleTypeDef *i2cHandle, uint8_t DeviceAddress, uint8_t Register, uint8_t *RegisterValue)
{
	if( (HAL_I2C_Mem_Read(i2cHandle, (DeviceAddress<<1), Register, 1, RegisterValue,1, 1000)) != HAL_OK)
	{
		return BMPE_I2C_READ_REGISTER_ERROR;
	}
	else
	{
		return BMPE_OK;
	}
	return BMPE_OK;
}
MZ_BMPE_Errors_t MZ_BMPE_I2C_WriteRegister(I2C_HandleTypeDef *i2cHandle, uint8_t DeviceAddress, uint8_t Register, uint8_t *RegisterValue)
{
	if( (HAL_I2C_Mem_Write(i2cHandle, (DeviceAddress<<1), Register, 1, RegisterValue,1, 1000)) != HAL_OK)
	{
		return BMPE_I2C_READ_REGISTER_ERROR;
	}
	else
	{
		return BMPE_OK;
	}
}
#elif

#endif

