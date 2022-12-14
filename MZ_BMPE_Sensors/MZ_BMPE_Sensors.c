/*
 * MZ_BMPE_Sensors.c
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */


#include "MZ_BMPE_Sensors.h"
#include "MZ_BMPE_Interface.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------Static variables definitions----------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static uint8_t DeviceCount = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*----------------------------------------------Static functions headers------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Calibration values functions
static MZ_BMPE_Errors_t MZ_BMPE_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr);

#ifdef MZ_BMPE_BMP180
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr);
#endif

#ifdef MZ_BMPE_BMP280
static MZ_BMPE_Errors_t MZ_BMPE_BMP280_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr);
#endif

#ifdef MZ_BMPE_BME280
static MZ_BMPE_Errors_t MZ_BMPE_BME280_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr);
#endif

//Pressure oversaampling functions
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);

static MZ_BMPE_Errors_t MZ_BMPE_BMP180_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);

//Temperature oversampling sunctions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);

//Device mode functions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t Mode);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t *Mode);

//Humidity oversampling functions
static MZ_BMPE_Errors_t MZ_BMPE_BME280_SetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling);
static MZ_BMPE_Errors_t MZ_BMPE_BME280_GetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling);

//SPI state functions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t SpiState);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t *SpiState);

//Filter coefficient functions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t FilterCoefficient);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t *FilterCoefficient);

//Standby time functions
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t StandbyTime);
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t *StandbyTime);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------------------------------Functions-------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Device initialization function
MZ_BMPE_Errors_t MZ_BMPE_DeviceInit(MZ_BMPE_Device_t *DevicePtr, uint8_t DeviceAddress, MZ_BMPE_DeviceType_t DeviceType, MZ_BMPE_CommunicationProtocol_t CommunicationProtocol)
{
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{

		//Checking device address and writing it to device pointer
		if(DeviceAddress == 0)
		{
			if(CommunicationProtocol == SPI)
			{
				DevicePtr->DeviceAddress = DeviceAddress;
			}
			else
			{
				return BMPE_INIT_ERROR;
			}

		}
		else
		{
			DevicePtr->DeviceAddress = DeviceAddress;
		}

		//Checking device type and writing it to device pointer
		if(DeviceType == 0)
		{
			return BMPE_INIT_ERROR;
		}
		else
		{
			DevicePtr->DeviceType = DeviceType;
		}

		//Checking communication protocol and writing it to device pointer
		if(CommunicationProtocol == 0)
		{
			return BMPE_INIT_ERROR;
		}
		else
		{
			DevicePtr->CommunicationProtocol = CommunicationProtocol;
		}

		if(MZ_BMPE_GetCalibrationValues(DevicePtr) != BMPE_OK)
		{
			return BMPE_CALIBRATION_DATA_ERROR;
		}

		//Creating device Id
		DeviceCount += 1;
		DevicePtr->DeviceId = DeviceCount;

	}

	return BMPE_OK;

}

//Function to get calibration values for devices
static MZ_BMPE_Errors_t MZ_BMPE_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr)
{
	#ifdef MZ_BMPE_BMP180
	if(DevicePtr->DeviceType == BMP180)
	{
		return MZ_BMPE_BMP180_GetCalibrationValues(DevicePtr);
	}
	#endif

	#ifdef MZ_BMPE_BMP280
	if(DevicePtr->DeviceType == BMP180)
	{
		return MZ_BMPE_BMP280_GetCalibrationValues(DevicePtr);
	}
	#endif

	#ifdef MZ_BMPE_BME280
	if(DevicePtr->DeviceType == BME280)
	{
		return MZ_BMPE_BME280_GetCalibrationValues(DevicePtr);
	}
	#endif

	return BMPE_OK;
}


//Function to get calibration values for BMP180
#ifdef MZ_BMPE_BMP180
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr)
{
	return BMPE_OK;
}
#endif


//Function to get calibration values for BMP280
#ifdef MZ_BMPE_BMP280
static MZ_BMPE_Errors_t MZ_BMPE_BMP280_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr)
{
	return BMPE_OK;
}
#endif



//Function to get calibration values for BME280
#ifdef MZ_BMPE_BME280
static MZ_BMPE_Errors_t MZ_BMPE_BME280_GetCalibrationValues(MZ_BMPE_Device_t *DevicePtr)
{
	return BMPE_OK;
}
#endif


//Function binding I2C handle with device. If you comment I2C definition in MZ_BMPE_Config.h this function will be not compiled
#ifdef MZ_BMPE_HAL_I2C
MZ_BMPE_Errors_t MZ_BMPE_I2C_Registration(MZ_BMPE_Device_t *DevicePtr, I2C_HandleTypeDef *i2cHandle)
{
	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking I2C handler
		if(i2cHandle == 0)
		{
			return BMPE_I2C_HANDLE_ERROR;
		}
		else
		{
			//Set I2C handler in device structure
			DevicePtr->i2cHandle = i2cHandle;
		}
	}

	return BMPE_OK;
}
#endif

//Function binding SPI handle with device. If you comment SPI definition in MZ_BMPE_Config.h this function will be not compiled
#ifdef MZ_BMPE_HAL_SPI
MZ_BMPE_Errors_t MZ_BMPE_SPI_Registration(MZ_BMPE_Device_t *DevicePtr, SPI_HandleTypeDef *spiHandle)
{
	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking SPI handler
		if(i2cHandle == 0)
		{
			return BMPE_SPI_HANDLE_ERROR;
		}
		else
		{
			//Set SPI handler in device structure
			DevicePtr->spiHandle = spiHandle;
		}
	}

	return BMPE_OK;
}
#endif


//Function to set pressure oversampling for devices
MZ_BMPE_Errors_t MZ_BMPE_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Validation device type to variable of oversampling
		if(((DevicePtr->DeviceType == BMP280) && OversamplingValue > 7) || ((DevicePtr->DeviceType == BME280) && OversamplingValue > 7) || ((DevicePtr->DeviceType == BMP180) && OversamplingValue > 3))
		{
			return BMPE_OVERSAMPLING_ERROR;
		}
		else
		{
			//Check the device type and use the appropriate function
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = MZ_BMPE_BMP180_SetPressureOversampling(DevicePtr, OversamplingValue);
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetPressureOversampling(DevicePtr, OversamplingValue);
			}
		}

	}


	return Result;
}

//Function to set pressure oversampling for BMP180
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMP180_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}
	else
	{
		//Bit mask for pressure oversampling
		CtrlMeasRegVal &= 0x3F;

		//Setting oversampling bits in register value
		CtrlMeasRegVal |= (OversamplingValue<<6);

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMP180_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}

	}


}


//Function to set pressure oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for pressure oversampling
		CtrlMeasRegVal &= 0xE3;

		//Setting oversampling bits in register value
		CtrlMeasRegVal |= (OversamplingValue<<2);

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}

	}

}

//Function to set temperature oversampling for devices
MZ_BMPE_Errors_t MZ_BMPE_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking oversampling value
		if(OversamplingValue > 7)
		{
			return BMPE_OVERSAMPLING_ERROR;
		}
		else
		{
			//Checking device type and use set temperature oversampling function for correct device
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = BMPE_WRONG_DEVICE_TYPE;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetTemperatureOversampling(DevicePtr, OversamplingValue);
			}
		}

	}


	return Result;
}


//Function to set temperature oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t OversamplingValue)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for temperature oversampling
		CtrlMeasRegVal &= 0x1F;

		//Setting oversampling bits in register value
		CtrlMeasRegVal |= (OversamplingValue<<5);

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}

//Function to set mode for devices
MZ_BMPE_Errors_t MZ_BMPE_SetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t Mode)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set mode functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			Result = MZ_BMPE_BMPE280_SetMode(DevicePtr, Mode);

		}

	}


	return Result;
}


//Function to set temperature oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t Mode)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for mode
		CtrlMeasRegVal &= 0xFC;

		//Setting mode bits in register value
		CtrlMeasRegVal |= Mode;

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}

//Function to set humadity oversmpling for devices
MZ_BMPE_Errors_t MZ_BMPE_SetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set humidity oversampling functions for correct device
		if(DevicePtr->DeviceType != BME280)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			Result = MZ_BMPE_BME280_SetHumidityOversampling(DevicePtr, Oversampling);

		}

	}


	return Result;
}


//Function to set humadity oversmpling for BME280
static MZ_BMPE_Errors_t MZ_BMPE_BME280_SetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t Oversampling)
{
	//Variable for control humidity register value
	uint8_t CtrlHumRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_HUM, &CtrlHumRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for humidity oversampling
		CtrlHumRegVal &= 0xF8;

		//Setting mode bits in register value
		CtrlHumRegVal |= Oversampling;

		//Writing value to control humidity register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CTRL_HUM, &CtrlHumRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}


//Function to set SPI state for devices
MZ_BMPE_Errors_t MZ_BMPE_SetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t SpiState)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set SPI state functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			//Checking SPI state value and use set SPI state function for correct value
			if(SpiState > 1)
			{
				return BMPE_SPI_STATE_ERROR;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetSpiState(DevicePtr, SpiState);
			}


		}

	}


	return Result;
}


//Function to set SPI state for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t SpiState)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for SPI state
		ConfigRegVal &= 0xFE;

		//Setting SPI state bits in register value
		ConfigRegVal |= SpiState;

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}

//Function to set filter coefficient for devices
MZ_BMPE_Errors_t MZ_BMPE_SetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t FilterCoefficient)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set filter coefficient functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			//Checking SPI state value and use set filter coefficient function for correct value
			if(FilterCoefficient > 7)
			{
				return BMPE_FILTER_COEFFICIENT_ERROR;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetFilterCoefficient(DevicePtr, FilterCoefficient);
			}


		}

	}


	return Result;
}


//Function to set filter coefficient for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t FilterCoefficient)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for filter coefficient
		ConfigRegVal &= 0xE3;

		//Setting filter coefficient bits in register value
		ConfigRegVal |= (FilterCoefficient<<2);

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}


//Function to set standby time for devices
MZ_BMPE_Errors_t MZ_BMPE_SetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t StandbyTime)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set standby time functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			//Checking SPI state value and use set standby time function for correct value
			if(StandbyTime > 7)
			{
				return BMPE_FILTER_COEFFICIENT_ERROR;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_SetStanbyTime(DevicePtr, StandbyTime);
			}


		}

	}


	return Result;
}


//Function to set standby time for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_SetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t StandbyTime)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for standby time
		ConfigRegVal &= 0x1F;

		//Setting standby time bits in register value
		ConfigRegVal |= (StandbyTime<<5);

		//Writing value to control register
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}
	}

}

//Function to set reset register for BMP180, BMP280, BME280
MZ_BMPE_Errors_t MZ_BMPE_SetReset(MZ_BMPE_Device_t *DevicePtr)
{
	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Need variable for pointer to write register function
		uint8_t ResetRegisterValue = 0xB6;

		//Set reset register for all devices
		if(MZ_BMPE_WriteRegister(DevicePtr, MZ_BMPE280_SOFTRESET, &ResetRegisterValue) != BMPE_OK)
		{
			return BMPE_WRITE_REGISTER_ERROR;
		}

		else
		{
			return BMPE_OK;
		}

	}
}


//Get pressure oversampling value for devices
MZ_BMPE_Errors_t MZ_BMPE_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Validation device type to variable of oversampling
		if(Oversampling == NULL)
		{
			return BMPE_DATA_POINTER_ERROR;
		}
		else
		{
			//Check the device type and use the appropriate function
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = MZ_BMPE_BMP180_GetPressureOversampling(DevicePtr, Oversampling);
			}
			else
			{
				Result = MZ_BMPE_BMPE280_GetPressureOversampling(DevicePtr, Oversampling);
			}
		}

	}


	return Result;
}


//Function to get pressure oversampling for BMP180
static MZ_BMPE_Errors_t MZ_BMPE_BMP180_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMP180_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}
	else
	{
		//Bit mask for pressure oversampling
		CtrlMeasRegVal &= 0xC0;

		//Set pressure oversampling value to oversampling pointer
		*Oversampling = (CtrlMeasRegVal>>6);

		return BMPE_OK;

	}


}


//Function to get pressure oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetPressureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}
	else
	{
		//Bit mask for pressure oversampling
		CtrlMeasRegVal &= 0x1C;

		//Set pressure oversampling value to oversampling pointer
		*Oversampling = (CtrlMeasRegVal>>2);

		return BMPE_OK;

	}

}


//Function to get temperature oversampling value for devices
MZ_BMPE_Errors_t MZ_BMPE_GetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Validation device type to variable of oversampling
		if(Oversampling == NULL)
		{
			return BMPE_DATA_POINTER_ERROR;
		}
		else
		{
			//Check the device type and use the appropriate function
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = BMPE_WRONG_DEVICE_TYPE;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_GetTemperatureOversampling(DevicePtr, Oversampling);
			}
		}

	}


	return Result;
}


//Function to get temperature oversampling for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetTemperatureOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}
	else
	{
		//Bit mask for temperature oversampling
		CtrlMeasRegVal &= 0xE0;

		//Set pressure oversampling value to oversampling pointer
		*Oversampling = (CtrlMeasRegVal>>5);

		return BMPE_OK;

	}

}

//Function to get mode value for devices
MZ_BMPE_Errors_t MZ_BMPE_GetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t *Mode)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Validation device type to variable of mode
		if(Mode == NULL)
		{
			return BMPE_DATA_POINTER_ERROR;
		}
		else
		{
			//Check the device type and use the appropriate function
			if(DevicePtr->DeviceType == BMP180)
			{
				Result = BMPE_WRONG_DEVICE_TYPE;
			}
			else
			{
				Result = MZ_BMPE_BMPE280_GetMode(DevicePtr, Mode);
			}
		}

	}


	return Result;
}


//Function to get mode for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetMode(MZ_BMPE_Device_t *DevicePtr, uint8_t *Mode)
{
	//Variable for control register value
	uint8_t CtrlMeasRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_MEAS, &CtrlMeasRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}
	else
	{
		//Bit mask for mode
		CtrlMeasRegVal &= 0x03;

		//Set mode value to mode pointer
		*Mode = (CtrlMeasRegVal>>0);

		return BMPE_OK;

	}

}



//Function to get humadity oversmpling for devices
MZ_BMPE_Errors_t MZ_BMPE_GetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set humidity oversampling functions for correct device
		if(DevicePtr->DeviceType != BME280)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{
			Result = MZ_BMPE_BME280_GetHumidityOversampling(DevicePtr, Oversampling);

		}

	}


	return Result;
}


//Function to get humadity oversmpling for BME280
static MZ_BMPE_Errors_t MZ_BMPE_BME280_GetHumidityOversampling(MZ_BMPE_Device_t *DevicePtr, uint8_t *Oversampling)
{
	//Variable for control humidity register value
	uint8_t CtrlHumRegVal = 0;

	//Get control register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CTRL_HUM, &CtrlHumRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for humidity oversampling
		CtrlHumRegVal &= 0x03;

		//Setting mode bits in register value
		*Oversampling = (CtrlHumRegVal>>0);


		return BMPE_OK;
	}

}


//Function to get SPI state for devices
MZ_BMPE_Errors_t MZ_BMPE_GetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t *SpiState)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use set SPI state functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{

			Result = MZ_BMPE_BMPE280_GetSpiState(DevicePtr, SpiState);

		}

	}


	return Result;
}


//Function to get SPI state for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetSpiState(MZ_BMPE_Device_t *DevicePtr, uint8_t *SpiState)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for SPI state
		ConfigRegVal &= 0x01;

		//Setting SPI state bits in variable
		*SpiState = (ConfigRegVal>>0);

		return BMPE_OK;

	}

}

//Function to set filter coefficient for devices
MZ_BMPE_Errors_t MZ_BMPE_GetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t *FilterCoefficient)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use get filter coefficient functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{

			Result = MZ_BMPE_BMPE280_GetFilterCoefficient(DevicePtr, FilterCoefficient);

		}

	}


	return Result;
}


//Function to set filter coefficient for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetFilterCoefficient(MZ_BMPE_Device_t *DevicePtr, uint8_t *FilterCoefficient)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for filter coefficient
		ConfigRegVal &= 0x1C;

		//Setting filter coefficient bits in variable pointer
		*FilterCoefficient = (ConfigRegVal>>2);

		return BMPE_OK;

	}

}


//Function to set standby time for devices
MZ_BMPE_Errors_t MZ_BMPE_GetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t *StandbyTime)
{
	//Variable for functions result
	MZ_BMPE_Errors_t Result;

	//Checking device pointer
	if(DevicePtr == NULL)
	{
		return BMPE_DEVICE_POINTER_ERROR;
	}
	else
	{
		//Checking device type and use get standby time functions for correct device
		if(DevicePtr->DeviceType == BMP180)
		{
			return BMPE_WRONG_DEVICE_TYPE;
		}
		else
		{

			Result = MZ_BMPE_BMPE280_GetStanbyTime(DevicePtr, StandbyTime);

		}

	}


	return Result;
}


//Function to set standby time for BMP280 and BME280
static MZ_BMPE_Errors_t MZ_BMPE_BMPE280_GetStanbyTime(MZ_BMPE_Device_t *DevicePtr, uint8_t *StandbyTime)
{
	//Variable for config register value
	uint8_t ConfigRegVal = 0;

	//Get config register value
	if(MZ_BMPE_ReadRegister(DevicePtr, MZ_BMPE280_CONFIG, &ConfigRegVal) != BMPE_OK)
	{
		return BMPE_READ_REGISTER_ERROR;
	}

	else
	{
		//Bit mask for standby time
		ConfigRegVal &= 0xE0;

		//Setting standby time bits in variable pointer
		*StandbyTime = (ConfigRegVal>>5);

		return BMPE_OK;

	}

}
