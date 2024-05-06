/*
******************************************************************************
  * @file    	: LTE_Hardware.h
  * @version 	: V1.0.0
  * @date    	: 23/04/2024
  * @brief   	: Khai bao cac macro va cac ham dung trong module
******************************************************************************
*/

#ifndef		__GPS_PROCESS_H__
#define		__GPS_PROCESS_H__

/* Includes */
#include "main.h"

/* Khai bao cau truc du lieu module */
typedef struct
{
	DateTime_t	UTCTime;				// Thoi gian UTC
	uint8_t			Valid;					// 0 - Invalid, 1 - Valid
	float 			Lat;						// Latitude - vi do
	uint8_t			NorS;						// 1 - North, 0 - South
	float				Long;						// Longitude - kinh do
	uint8_t			EorW;						// 1 - East, 0 - West
	float				Speed;					// Toc do (hai ly / gio)
	float				COG;						// Huong di chuyen
	uint8_t			NbofSV;					// So ve tinh
	
}	GPSDataStructure;

/* Khai bao cac bien dung trong module */
extern GPSDataStructure				GPSData;


/* Khai bao cac ham dung trong module */
void GPS_ProcessData(char* Data);
void GPS_RMCMessageProcess(char* Message);

#endif

