/*
******************************************************************************
  * @file    	: main.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__MAIN_H_
#define		__MAIN_H_

/* Includes */
#include "stm32l1xx.h"

typedef union
{
	uint32_t 	Value;
	uint8_t		Byte[4];
	
}	bLong;

typedef struct
{
	char 			Address[128];
	uint16_t 	Port;
} ServerAddress;

typedef struct
{
  uint8_t Year;
  uint8_t Month;
  uint8_t Date;
  uint8_t Hour;
  uint8_t Min;
  uint8_t Sec;
	
}	DateTime_t;

/* Khai bao cau truc du lieu sensor */
typedef struct
{
	uint16_t Temperature;
	uint16_t Humidity;
	uint16_t NoiseLevel;
	uint16_t Vac;
	uint32_t Iac;
	uint32_t Pac;
	uint16_t Vdc;
	uint16_t Idc;
	uint32_t Pdc;
	uint16_t Iht;
	uint16_t I3G;
	uint16_t I4G;
	uint16_t REC1;
	uint16_t REC2;
	uint16_t REC3;
	uint16_t BAT1;
	uint16_t BAT2;
	uint16_t BAT3;
	
}	SensorDataStructure;

/* Khai bao cau truc du lieu dung trong he thong */
typedef struct
{
	uint8_t		InitDone;
	uint32_t	Tick1ms;
	uint8_t		Tick10ms;
	uint16_t	Tick100ms;	
	uint16_t	Tick1000ms;
	uint32_t	Delay_ms;
	uint8_t		ResetReason;
	uint8_t		LoginReason;
	uint8_t		Connected;
	uint8_t		Logined;
	uint16_t	TimeNotLogin;
	uint8_t		Sent;
	uint8_t		RTCDebug;
	DateTime_t	Time;
	SensorDataStructure	Sensor;
	uint8_t		SensorDebug;
	uint8_t		TempDebug;
	
}	SystemStructure;

/* Khai bao cau truc mo ta thoi gian Release phien ban */
typedef struct
{
	uint8_t 	Ngay;
	uint8_t 	Thang;
	uint16_t 	Nam;
	uint8_t 	Gio;
	uint8_t		Phut;
	uint8_t 	Giay;
	
}	VersionStructure;

/* Khai bao cau truc du lieu dung trong he thong */
extern SystemStructure			xSystem;

/* Khai bao cac ham dung trong module */
void ProcessTask_10ms(void);
void ProcessTask_100ms(void);
void ProcessTask_1000ms(void);

#endif
