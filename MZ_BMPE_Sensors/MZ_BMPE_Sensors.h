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

	#if defined(MZ_BMPE_BMP280) || defined(MZ_BMPE_BME280)
	//Calibration variables for temperature BMP280, BME280
	uint16_t dig_T1;
	int16_t dig_T2;
	int16_t dig_T3;

	//Calibration variables for pressure BMP280, BME280
	uint16_t dig_P1;
	int16_t dig_P2;
	int16_t dig_P3;
	int16_t dig_P4;
	int16_t dig_P5;
	int16_t dig_P6;
	int16_t dig_P7;
	int16_t dig_P8;
	int16_t dig_P9;
	#endif

	#ifdef MZ_BMPE_BME280
	//Calibration variables for humidity BME280
	uint8_t dig_H1;
	int16_t dig_H2;
	uint8_t dig_H3;
	int16_t dig_H4;
	int16_t dig_H5;
	int8_t dig_H6;
	#endif

	#ifdef MZ_BMPE_BMP180
	//Calibration variables for BMP180
	int16_t AC1;
	int16_t AC2;
	int16_t AC3;
	uint16_t AC4;
	uint16_t AC5;
	uint16_t AC6;
	int16_t B1;
	int16_t B2;
	int16_t MB;
	int16_t MC;
	int16_t MD;
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
	BMPE_SPI_STATE_ERROR = 12,
	BMPE_FILTER_COEFFICIENT_ERROR = 13,
	BMPE_DATA_POINTER_ERROR = 14,
	BMPE_CALIBRATION_DATA_ERROR = 15
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
//Filter coefficient setter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t FilterCoefficient);
//Standby time setter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_SetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t StandbyTime);
//Reset setter function for BMP180, BMP280, BME280
MZ_BMPE_Errors_t MZ_BMPE_SetReset(MZ_BMPE_Device_t *DevicePtr);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------Getters functions--------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Pressure oversampling getter function for BMP180, BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);
//Temperrature oversampling getter function for BMP180, BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);
//Mode getter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t *Mode);
//Humadity oversampling getter function for BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);
//SPI communication protocol getter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t *SpiState);
//Filter coefficient getter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t *FilterCoefficient);
//Standby time getter function for BMP280, BME280 (for values check module datasheet)
MZ_BMPE_Errors_t MZ_BMPE_GetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t *StandbyTime);


#endif /* MZ_BMPE_SENSORS_H_ */
