/*
******************************************************************************
  * @file    	: InitSystem.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Led.h"
#include "Debug.h"
#include "Watchdog.h"
#include "PowerCtrl.h"
#include "InitSystem.h"
#include "GPS_Hardware.h"
#include "Configuration.h"
#include "HardwareManager.h"

/* Khai bao cac bien dung trong module */
extern	SystemStructure 		xSystem;

/*******************************************************************************
 * Function Name  	: System_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao he thong
*******************************************************************************/
void System_Initialize(void)
{
	xSystem.InitDone = 0;
	
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
	
	SysTickConfig();
	
	WatchDog_Initialize();
//	Led_Initialize();
	Debug_Initialize(115200);
	DebugPrint("\rKhoi tao he thong...");
	Hardware_Initialize();
//	EXTI_Configuration();
//	GPS_Initialize(9600);
	
	DebugPrint("\rKhoi tao xong.");
	System_VariableInit();
	xSystem.InitDone = 1;
}

/*******************************************************************************
 * Function Name  	: System_VariableInit
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao cac bien he thong
*******************************************************************************/
void System_VariableInit(void)
{
	xSystem.Tick10ms		= 0;
	xSystem.Tick100ms 	= 0;
	xSystem.Tick1000ms 	= 0;
	xSystem.Delay_ms 		= 0;
}

/*******************************************************************************
 * Function Name  	: SysTickConfig
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao ngat he thong
*******************************************************************************/
void SysTickConfig(void)
{
	/* Cau hinh ngat he thong 1ms */
	if(SysTick_Config(SystemCoreClock/1000))
	{
		while(1);
	}
	
	/* Cau hinh muc do uu tien cua trinh xu ly ngat */
	NVIC_SetPriority(SysTick_IRQn, 0x0);
}

