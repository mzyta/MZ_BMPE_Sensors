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


#ifdef MZ_BMPE_HAL_I2C
#include "i2c.h"  //Path to I2C library
#endif

#ifdef MZ_BMPE_HAL_SPI
#include "spi.h" //Path to SPI library
#endif



//#include "main.h"

//Device types enum
typedef enum {
	BMP180 = 1,
	BMP280 = 2,
	BME280 = 3
} MZ_BMPE_DeviceType_t;


//Devices communication protocol enum
typedef enum {
	I2C = 1,
	SPI = 2
} MZ_BMPE_CommunicationProtocol_t;


//Device structure
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

	//Communication handlers for HAL communication
	#ifdef MZ_BMPE_HAL_I2C
	I2C_HandleTypeDef *i2cHandle;
	#endif

	#ifdef MZ_BMPE_HAL_SPI
	SPI_HandleTypeDef *spiHandle;
	#endif


} MZ_BMPE_Device_t;


//Errors enum
typedef enum{
	BMPE_OK = 0,
	BMPE_INIT_ERROR = 1,
	BMPE_DEVICE_POINTER_ERROR = 2,
	BMPE_WRONG_COMMUNICATION_PROTOCOL = 3,
	BMPE_COMMUNICATION_PROBLEM = 4,
	BMPE_I2C_HANDLE_ERROR = 5,
	BMPE_SPI_HANDLE_ERROR = 6,
	BMPE_OVERSAMPLING_ERROR = 7,
	BMPE_WRONG_DEVICE_TYPE = 8,
	BMPE_READ_REGISTER_ERROR = 9,
	BMPE_WRITE_REGISTER_ERROR = 10,
	BMPE_I2C_READ_REGISTER_ERROR = 11,
	BMPE_SPI_STATE_ERROR = 12
} MZ_BMPE_Errors_t;


//Device initialization function
MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceAddress, uint8_t DeviceType, uint8_t CommunicationProtocol);


//Registration of communication handlers for HAL
#ifdef MZ_BMPE_HAL_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_Registration(MZ_BMPE_Device_t *DevicePtr, I2C_HandleTypeDef *i2cHandle);
#endif

#ifdef MZ_BMPE_HAL_SPI
MZ_BMPE_Errors_t MZ_BMPE_SPI_Registration(MZ_BMPE_Device_t *DevicePtr, SPI_HandleTypeDef *spiHandle);
#endif


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------Setters functions--------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Pressure oversampling setter function for BMP180, BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling);
//Temperature oversampling setter function for BMP180, BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling);
//Mode setter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t Mode);
//Humadity oversampling setter function for BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling);
//SPI communication protocol setter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t SpiState);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------Getters functions--------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /* MZ_BMPE_SENSORS_H_ */
