/*
 * MZ_BMPE_spi.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_SPI_H_
#define MZ_BMPE_SPI_H_

#include "MZ_BMPE_Sensors.h"

#ifdef MZ_BMPE_HAL_SPI
MZ_BMPE_Errors_t MZ_BMPE_I2C_ReadRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue);
MZ_BMPE_Errors_t MZ_BMPE_I2C_WriteRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue);
#else

#endif

#endif /* MZ_BMPE_SPI_H_ */
