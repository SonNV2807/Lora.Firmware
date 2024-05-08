/*
******************************************************************************
  * @file    	: HardwareManager.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong viec quan ly phan cung
******************************************************************************
*/

/* Includes */
#include "Debug.h"
#include "HardwareManager.h"

/*******************************************************************************
 * Function Name  	: Hardware_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao module phan cung
*******************************************************************************/
void Hardware_Initialize(void)
{
	Hardware_CheckResetReason();
	
	Hardware_CheckClockSource();
}

/*******************************************************************************
 * Function Name		: Hardware_SystemReset
 * Return						: None
 * Parameters				: None
 * Description			: Thuc hien viec reset thiet bi
*******************************************************************************/
void Hardware_SystemReset(uint8_t Reason)
{
	DebugPrint("\rSYSTEM: Tien hanh reset, nguyen nhan %d.", Reason);
	
	NVIC_SystemReset();
}

/*******************************************************************************
 * Function Name  	: Hardware_CheckResetReason
 * Return         	: None
 * Parameters 			: None
 * Description			: Kiem tra nguyen nhan reset
*******************************************************************************/ 
static void Hardware_CheckResetReason(void)
{
	xSystem.ResetReason = 0;
	if(RCC_GetFlagStatus(RCC_FLAG_OBLRST))
	{
		DebugPrint("\rNguyen nhan reset do OBL.");
		xSystem.ResetReason |= 1;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_PINRST))
	{
		DebugPrint("\rNguyen nhan reset do PIN.");
		xSystem.ResetReason |= 2;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_PORRST))
	{
		DebugPrint("\rNguyen nhan reset do POR.");
		xSystem.ResetReason |= 4;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_SFTRST))
	{
		DebugPrint("\rNguyen nhan reset do SFT.");
		xSystem.ResetReason |= 8;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST))
	{
		DebugPrint("\rNguyen nhan reset do IWDG.");
		xSystem.ResetReason |= 16;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_WWDGRST))
	{
		DebugPrint("\rNguyen nhan reset do WWDG.");
		xSystem.ResetReason |= 32;
	}
	
	if(RCC_GetFlagStatus(RCC_FLAG_LPWRRST))
	{
		DebugPrint("\rNguyen nhan reset do LPWR.");
		xSystem.ResetReason |= 64;
	}
	
	/* Clear co RCC */	
	RCC_ClearFlag();
}

/*******************************************************************************
 * Function Name  	: Hardware_CheckClockSource
 * Return         	: None
 * Parameters 			: None
 * Description			: Kiem tra nguon cap clock he thong
*******************************************************************************/ 
static void Hardware_CheckClockSource(void)
{
	uint8_t CLKSource;
	
	CLKSource = RCC_GetSYSCLKSource();
	
	if(CLKSource == 0x00)
		DebugPrint("\rCLOCK: Nguon clock MSI.");
	else if(CLKSource == 0x04)
		DebugPrint("\rCLOCK: Nguon clock HSI.");
	else if(CLKSource == 0x08)
		DebugPrint("\rCLOCK: Nguon clock HSE.");
	else
		DebugPrint("\rCLOCK: Nguon clock PLL.");
}

