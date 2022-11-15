/*
 * MZ_BMPE_Interface.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_INTERFACE_H_
#define MZ_BMPE_INTERFACE_H_

#include "MZ_BMPE_Sensors.h"

MZ_BMPE_Errors_t MZ_BMPE_ReadRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue);
MZ_BMPE_Errors_t MZ_BMPE_WriteRegister(MZ_BMPE_Device_t *DevicePtr, uint8_t Register, uint8_t *RegisterValue);

#endif /* MZ_BMPE_INTERFACE_H_ */
