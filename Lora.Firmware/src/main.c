/*
******************************************************************************
  * @file    	main.c
  * @version 	V1.0.0
  * @date    	??/??/20??
  * @brief   	Main program
******************************************************************************
*/

/* Includes */
#include "Led.h"
#include "main.h"
#include "Debug.h"
#include "Watchdog.h"
#include "PowerCtrl.h"
#include "InitSystem.h"
#include "GPS_Hardware.h"
#include "Configuration.h"

/* Khai bao cac bien dung trong module */
SystemStructure			xSystem;

/**************************************************************************************
* Function Name  	: main
* Return         	: None
* Parameters 			: None
* Description			: Khoi tao va xu ly hoat dong cua thiet bi
**************************************************************************************/
int main(void)
{
	/* Khoi tao he thong */
	System_Initialize();
	
	while(1)
	{				
		Watchdog_Reset();
		
		if(xSystem.Tick10ms >= 10)
		{
			xSystem.Tick10ms = 0;
			ProcessTask_10ms();
		}
		
		if(xSystem.Tick100ms >= 100)
		{
			xSystem.Tick100ms = 0;
			ProcessTask_100ms();
		}
		
		if(xSystem.Tick1000ms >= 1000)
		{
			xSystem.Tick1000ms = 0;
			ProcessTask_1000ms();
		}
		
		/* Xu ly du lieu nhan duoc tu cong Debug */
		Config_Process();
		/* Xu ly du lieu nhan duoc tu cong GPS */
//		GPS_Process();
		
		Watchdog_Reset();
	}	
}

/*******************************************************************************
 * Function Name  	: ProcessTask_10ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly task chu ky 10ms
*******************************************************************************/
void ProcessTask_10ms(void)
{

}

/*******************************************************************************
 * Function Name  	: ProcessTask_100ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly task chu ky 100ms
*******************************************************************************/
void ProcessTask_100ms(void)
{
	Led_Tick100ms();
}

/*******************************************************************************
 * Function Name  	: ProcessTask_1000ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly task chu ky 1000ms
*******************************************************************************/
void ProcessTask_1000ms(void)
{	
//	DebugPrint("\rXin chao cac ban");
//	DebugPrint("\rHere.");
	PWR_Process();
}

