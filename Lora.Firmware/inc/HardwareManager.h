/*
******************************************************************************
  * @file    	: HardwareManager.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__HARDWARE_MANAGER_H__
#define		__HARDWARE_MANAGER_H__

/* Includes */
#include "main.h"

/* Khai bao cac ham dung trong module */
void Hardware_Initialize(void);
void Hardware_SystemReset(uint8_t Reason);

/* Layer 2 */
static void Hardware_CheckResetReason(void);
static void Hardware_CheckClockSource(void);

#endif

