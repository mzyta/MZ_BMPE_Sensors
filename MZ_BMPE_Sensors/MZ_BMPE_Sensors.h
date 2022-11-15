/*
 * MZ_BMPE_Sensors.h
 *
 *  Created on: Nov 15, 2022
 *      Author: zytam
 */

#ifndef MZ_BMPE_SENSORS_H_
#define MZ_BMPE_SENSORS_H_

#include <stdint.h>

//#include "main.h"

typedef struct{
	//Variable for future solutions
	uint8_t DeviceId;

	//Device address if it's need to communication protocol
	uint8_t DeviceAddress;

	/*Sensor type
	 * 1= BMP180
	 * 2= BMP280
	 * 3= BME280
	 */
	uint8_t DeviceType;

	/*Communication protocol for device
	 * 1= I2C
	 * 2= SDI
	 */
	uint8_t CommunicationProtocol;

} MZ_BMPE_Device_t;

typedef enum{
	BMPE_OK = 0,
	BMPE_DEVICE_POINTER_ERROR = 1,
	BMPE_INIT_ERROR = 2,
	BMPE_WRONG_COMMUNICATION_PROTOCOL = 3,
	BMPE_COMMUNICATION_PROBLEM = 4
}MZ_BMPE_Errors_t;


MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceId, uint8_t DeviceAddress, uint8_t DeviceType, uint8_t CommunicationProtocol);

#endif /* MZ_BMPE_SENSORS_H_ */
