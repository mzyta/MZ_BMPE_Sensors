/*
 * MZ_BMPE_i2c.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_I2C_H_
#define MZ_BMPE_I2C_H_

#include "MZ_BMPE_Sensors.h"

#ifdef MZ_BMPE_HAL_I2C
//Headers for HAL I2C protocol
MZ_BMPE_Errors_t MZ_BMPE_I2C_ReadRegister(I2C_HandleTypeDef *i2cHandle, uint8_t DeviceAddress, uint8_t Register, uint8_t *RegisterValue);
MZ_BMPE_Errors_t MZ_BMPE_I2C_WriteRegister(I2C_HandleTypeDef *i2cHandle, uint8_t DeviceAddress, uint8_t Register, uint8_t *RegisterValue);
#else

#endif



#endif /* MZ_BMPE_I2C_H_ */
