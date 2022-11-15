/*
 * MZ_BMPE_Sensors.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_SENSORS_H_
#define MZ_BMPE_SENSORS_H_

#include <stdint.h>

#include "MZ_BMPE_Config.h"


#ifdef MZ_BMPE_I2C
#include "i2c.h"  //Path to I2C library
#endif

#ifdef MZ_BMPE_SPI
#include "spi.h" //Path to SPI library
#endif



//#include "main.h"

typedef enum {
	BMP180 = 1,
	BMP280 = 2,
	BME280 = 3
} MZ_BMPE_DeviceType_t;


typedef enum {
	I2C = 1,
	SPI = 2
} MZ_BMPE_CommunicationProtocol_t;

typedef struct{
	//Variable for future solutions
	uint8_t DeviceId;

	//Device address if it's need to communication protocol
	uint8_t DeviceAddress;

	/*Sensor type
	 * 1 = BMP180
	 * 2 = BMP280
	 * 3 = BME280
	 */
	MZ_BMPE_DeviceType_t DeviceType;

	/*Communication protocol for device
	 * 1 = I2C
	 * 2 = SPI
	 */
	MZ_BMPE_CommunicationProtocol_t CommunicationProtocol;

	//Communication handlers
	#ifdef MZ_BMPE_I2C
	I2C_HandleTypeDef *i2cHandle;
	#endif

	#ifdef MZ_BMPE_SPI
	SPI_HandleTypeDef *spiHandle;
	#endif


} MZ_BMPE_Device_t;

typedef enum{
	BMPE_OK = 0,
	BMPE_INIT_ERROR = 1,
	BMPE_DEVICE_POINTER_ERROR = 2,
	BMPE_WRONG_COMMUNICATION_PROTOCOL = 3,
	BMPE_COMMUNICATION_PROBLEM = 4,
	BMPE_I2C_HANDLE_ERROR = 5,
	BMPE_SPI_HANDLE_ERROR = 6
} MZ_BMPE_Errors_t;


MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceAddress, uint8_t DeviceType, uint8_t CommunicationProtocol);

#ifdef MZ_BMPE_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_Registration(MZ_BMPE_Device_t *DevicePtr, I2C_HandleTypeDef *i2cHandle);
#endif

#ifdef MZ_BMPE_SPI
MZ_BMPE_Errors_t MZ_BMPE_SPI_Registration(MZ_BMPE_Device_t *DevicePtr, SPI_HandleTypeDef *spiHandle);
#endif

#endif /* MZ_BMPE_SENSORS_H_ */
