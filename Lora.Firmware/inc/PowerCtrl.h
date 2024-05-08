/*
******************************************************************************
  * @file    	: PowerCtrl.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__POWER_CTRL_H__
#define		__POWER_CTRL_H__

/* Includes */
#include "main.h"

/* Khai bao enum mo ta sleep mode */
typedef enum
{
	SLEEP_NOW = 0,
	SLEEP_ON_EXIT
	
}	SleepModeEnum;

/* Khai bao enum mo ta entry mode */
typedef enum
{
	WAIT_FOR_INTERRUPT = 0,
	WAIT_FOR_EVENT
	
}	EntryModeEnum;

/* Khai bao cac ham dung trong module */
void PWR_Process(void);
void PWR_LowPowerRunMode(FunctionalState NewState);
void PWR_SleepMode(uint8_t EntryMode);
void PWR_LowPowerSleepMode(uint8_t EntryMode);
void PWR_StopMode(uint8_t EntryMode);
void PWR_StandbyMode(void);
void PWR_ProcessCommand(char* Cmd);

#endif

