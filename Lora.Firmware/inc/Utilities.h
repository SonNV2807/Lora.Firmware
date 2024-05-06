/*
******************************************************************************
  * @file    	: Utilities.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__UTILITIES_H__
#define		__UTILITIES_H__

/* Includes */
#include "main.h"

/* Khai bao cac ham dung trong module */
void Delay_us(uint16_t Time);
void Delay_ms(uint16_t Time);
void CountTime(void);
uint32_t GetNumberFromString(uint16_t BeginIndex, char* Buffer);
int16_t FindIndexOfCharacter(char Character, char* Buffer);
uint8_t SplitString(char* Data, char* Result, char CharBegin, char CharEnd);
uint32_t GetCheckSum(uint8_t *Buffer, uint32_t Length);
uint16_t GetCRC_16_Modbus(uint8_t* Buffer, uint16_t Length);
float ConvertMinToDegree(float Min);

#endif

