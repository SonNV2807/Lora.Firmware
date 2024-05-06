/*
******************************************************************************
  * @file    	: Configuration.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__CONFIGURATION_H__
#define		__CONFIGURATION_H__

/* Includes */
#include "main.h"

/* Dinh nghia macro dung luong bo dem */
#define	CONFIG_RX_BUFFER_SIZE		512

/* Dinh nghia cau truc du lieu dung trong module */
typedef struct
{
	uint8_t 	NewData;
	char 			RxBuffer[CONFIG_RX_BUFFER_SIZE];
	uint16_t 	RxCounter;
	uint8_t 	ReceiveTimeOut;
	
} ConfigStructure;

/* Khai bao cac ham dung trong module */
void Config_ReceiveData(uint8_t Byte);
void Config_Process(void);
void Config_Tick1ms(void);

#endif
