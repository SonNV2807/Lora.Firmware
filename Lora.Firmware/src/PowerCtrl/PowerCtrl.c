/*
******************************************************************************
  * @file    	: PowerCtrl.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "RTC.h"
#include "time.h"
#include "Debug.h"
#include "Watchdog.h"
#include "PowerCtrl.h"
#include "Utilities.h"
#include "InitSystem.h"

/*******************************************************************************
 * Function Name  	: PWR_Process
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly cac che do Power
*******************************************************************************/
void PWR_Process(void)
{
	static uint32_t Tick1s = 0;
	
	Tick1s++;
	
	if(Tick1s != 5)
		return;
	
	Watchdog_Reset();
	
//	PWR_LowPowerRunMode(ENABLE);
	
//	PWR_SleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
	
//	PWR_LowPowerSleepMode();
	
//	PWR_STOPMode(PWR_SLEEPEntry_WFI);
	
//	PWR_STANDBYMode();
}

/*******************************************************************************
 * Function Name  	: PWR_LowPowerRunMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do low-power run cua MCU
*******************************************************************************/
void PWR_LowPowerRunMode(FunctionalState NewState)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
	if(NewState == ENABLE)
		RCC_MSIRangeConfig(RCC_MSIRange_0);
	else
		RCC_MSIRangeConfig(RCC_MSIRange_5);
	
	SysTickConfig();
	Debug_Initialize(115200);
	
	if(NewState == ENABLE)
		DebugPrint("\rEnter Low-power Run mode.");
	else
		DebugPrint("\rExit Low-power Run mode.");
	
	PWR_EnterLowPowerRunMode(NewState);
}

/*******************************************************************************
 * Function Name  	: PWR_SleepMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do sleep cua MCU
*******************************************************************************/
void PWR_SleepMode(uint8_t EntryMode)
{	
	struct tm time;
	
	DebugPrint("\rEnter Sleep mode.");
	
	rtc_get_time(&time);
	time.tm_sec  += 3;
  rtc_set_alarm(&time, NULL, NULL);
	
	PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
}	

/*******************************************************************************
 * Function Name  	: PWR_LowPowerSleepMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do Low-power Sleep cua MCU
*******************************************************************************/
void PWR_LowPowerSleepMode(uint8_t EntryMode)
{
	FLASH_SLEEPPowerDownCmd(ENABLE);
	
	RCC_MSIRangeConfig(RCC_MSIRange_0);
	
	SysTickConfig();
	Debug_Initialize(115200);
	
	DebugPrint("\rEnter Low-power Sleep mode.");
	PWR_EnterSleepMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);
}	

/*******************************************************************************
 * Function Name  	: PWR_StopMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do stop cua MCU
*******************************************************************************/
void PWR_StopMode(uint8_t EntryMode)
{	    
	DebugPrint("\rEnter Stop mode.");
	
//	DBGMCU_Config(DBGMCU_IWDG_STOP, DISABLE);

//	/* Disable PVD */
//	PWR_PVDCmd(DISABLE);   
//	/* Enable Ultra low power mode */   
//	PWR_UltraLowPowerCmd(ENABLE);   
//	RCC->AHBENR = 0x05;   
//	RCC->AHBLPENR = 0x05;   
//	RCC->APB1ENR = RCC_APB1ENR_PWREN;   
//	RCC->APB2ENR = 0;   
//	/* To stop the sys tick for avoid IT */   
//	SysTick->CTRL = 0;   
//	SysTick->CTRL  &= ~SysTick_CTRL_TICKINT_Msk;  
//	// systick IRQ off   
//	PWR_ClearFlag(PWR_FLAG_WU);   
//	/* RCC system reset */   
//	RCC_DeInit();   
//	/* Flash no latency*/   
//	FLASH_SetLatency(FLASH_Latency_0);   
//	/* Disable Prefetch Buffer */   
//	FLASH_PrefetchBufferCmd(DISABLE);   
//	/* Disable 64-bit access */   
//	FLASH_ReadAccess64Cmd(DISABLE);   
//	/* Disable FLASH during SLeep  */   
//	FLASH_SLEEPPowerDownCmd(ENABLE);   
//	/* Enable the PWR APB1 Clock */   
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);   
//	/* Select the Voltage Range 3 (1.2V) */   
//	PWR_VoltageScalingConfig(PWR_VoltageScaling_Range3);   
//	/* Wait Until the Voltage Regulator is ready */   
//	while (PWR_GetFlagStatus(PWR_FLAG_VOS) != RESET) {};   
//	/* Configure the MSI frequency */   
//	RCC_MSIRangeConfig(RCC_ICSCR_MSIRANGE_0);   
//	/* Select MSI as system clock source */   
//	RCC_SYSCLKConfig(RCC_SYSCLKSource_MSI);   
//	/* Wait until MSI is used as system clock source */   
//	while (RCC_GetSYSCLKSource() != 0x00) {};   
//	/* Disable HSI clock */   
//	RCC_HSICmd(DISABLE);   
//	/* Disable HSE clock */   
//	RCC_HSEConfig(RCC_HSE_OFF);   
//	/* Disable LSI clock */   
//	RCC_LSICmd(DISABLE); 	
	
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, EntryMode);
}

/*******************************************************************************
 * Function Name  	: PWR_StandbyMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do standby cua MCU
*******************************************************************************/
void PWR_StandbyMode(void)
{
	DebugPrint("\rEnter Standby mode.");
	
	PWR_WakeUpPinCmd(PWR_WakeUpPin_1, ENABLE);
	
	PWR_EnterSTANDBYMode();
}

/*******************************************************************************
 * Function Name  	: PWR_ProcessCommand
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly lenh dieu khien PWR
*******************************************************************************/
void PWR_ProcessCommand(char* Cmd)
{
	uint8_t Id, Index;
	
	Index = FindIndexOfCharacter(',', Cmd);
	Index++;
	Id = GetNumberFromString(Index, Cmd);
	
	switch(Id)
	{
		case 0: 
			PWR_LowPowerRunMode(DISABLE);
		break;
		
		case 1: 
			PWR_LowPowerRunMode(ENABLE);
		break;
		
		case 2:
			PWR_SleepMode(PWR_SLEEPEntry_WFI);
		break;
		
		case 3: 
			PWR_LowPowerSleepMode(PWR_SLEEPEntry_WFI);
		break;
		
		case 4: 
			PWR_StopMode(PWR_SLEEPEntry_WFI);
		break;
		
		case 5:
			PWR_StandbyMode();
		break;
		
		default:
		break;
	}
}

