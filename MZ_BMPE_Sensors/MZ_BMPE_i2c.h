/*
 * MZ_BMPE_i2c.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_I2C_H_
#define MZ_BMPE_I2C_H_

#include "MZ_BMPE_Sensors.h"

MZ_BMPE_Errors_t MZ_BMPE_I2C_ReadRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValu);
MZ_BMPE_Errors_t MZ_BMPE_I2C_WriteRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValu);



#endif /* MZ_BMPE_I2C_H_ */
