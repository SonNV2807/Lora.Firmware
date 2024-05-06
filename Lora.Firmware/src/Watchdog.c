/*
******************************************************************************
  * @file    	: WatchDog.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module 
******************************************************************************
*/

/* Includes */
#include "Watchdog.h"

/*******************************************************************************
 * Function Name  	: WatchDog_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao Internal WatchDog
*******************************************************************************/
void WatchDog_Initialize(void)
{
	/* Enable write access to IWDG_PR and IWDG_RLR registers */ 
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	
	/* Configure the IWDG prescaler */
	IWDG_SetPrescaler(IWDG_Prescaler_32);
	
	/* Configure the IWDG counter */
	IWDG_SetReload(0xFFF);
	
	/* Reload the IWDG counter */
	IWDG_ReloadCounter();
	
	/* Enable IWDG */
	IWDG_Enable();
}

/*******************************************************************************
 * Function Name  	: WatchDog_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Dat lai gia tri WatchDog Counter
*******************************************************************************/
void Watchdog_Reset(void)
{
	IWDG_ReloadCounter();
}
