/*
 * MZ_BMPE_Config.h
 *
 *  Created on: Nov 15, 2022
 *      Author: Mateusz Żyta (mateusz@mzyta.pl)
 */

#ifndef MZ_BMPE_CONFIG_H_
#define MZ_BMPE_CONFIG_H_

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*-------------------------------------------LIBRARY CONFIGURATION------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Communication protocols definitions

//Uncomment this definition if you want use SPI
//#define MZ_BMPE_SPI

//Uncomment this definition if you want use I2C
#define MZ_BMPE_I2C

//Uncomment this definition if you want use low leyer communication functions (you find callback definitions in MZ_BMPE_spi.h and MZ_BMPE_i2c.h
//#define MZ_BMPE_LL_COMMUNICATION




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------BMP280 AND BME280 DEFINITIONS--------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Registers
//
#define	MZ_BMPE280_CHIPID				0xD0
#define MZ_BMPE280_VERSION				0xD1
#define	MZ_BMPE280_SOFTRESET			0xE0
#define	MZ_BMPE280_CAL26				0xE1  // R calibration stored in 0xE1-0xF0
#define	MZ_BMPE280_CTRL_HUM				0xF2
#define	MZ_BMPE280_STATUS				0xF3
#define	MZ_BMPE280_CTRL_MEAS			0xF4
#define	MZ_BMPE280_CONFIG				0xF5
#define	MZ_BMPE280_PRESSUREDATA			0xF7
#define	MZ_BMPE280_TEMPDATA				0xFA




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*--------------------------------------------BMP180 DEFINITIONS-------------------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Registers
//
#define	MZ_BMP180_CHIPID				0xD0
#define	MZ_BMP180_SOFTRESET				0xE0
#define	MZ_BMP180_CTRL_MEAS				0xF4
#define	MZ_BMP180_PRESSUREDATA			0xF6



#endif /* MZ_BMPE_CONFIG_H_ */
