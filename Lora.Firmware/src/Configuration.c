/*
******************************************************************************
  * @file    	: Configuration.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Debug.h"
#include "string.h"
#include "PowerCtrl.h"
#include "GPS_Hardware.h"
#include "Configuration.h"
#include "HardwareManager.h"

/* Khai bao cac bien dung trong module */
ConfigStructure						Config;

/**************************************************************************************
 * Function Name  	: Config_ReceiveData
 * Return         	: None
 * Parameters 			: None
 * Description			: Dong goi du lieu nhan duoc tu cong Com
**************************************************************************************/
void Config_ReceiveData(uint8_t Byte)
{
	Config.RxBuffer[Config.RxCounter] = Byte;
	Config.RxCounter = (Config.RxCounter + 1) % CONFIG_RX_BUFFER_SIZE;
	Config.ReceiveTimeOut = 70;
}

/**************************************************************************************
 * Function Name  	: Config_Process
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly du lieu nhan duoc tu cong Com
**************************************************************************************/
void Config_Process(void)
{
	/* Neu khong co du lieu thi khong xu ly */
	if(Config.NewData == 0)
		return;
	
	/* Xoa co bao du lieu */
	Config.NewData = 0;
	DebugPrint("\rNhan duoc du lieu tu cong Debug. Chieu dai %d. Noi dung: %s", Config.RxCounter, Config.RxBuffer);
	
	/* Debug GPS */
	if(strstr((char*) Config.RxBuffer, "RESET#"))
		Hardware_SystemReset(1);
	
	/* Debug GPS */
	if(strstr((char*) Config.RxBuffer, "DEBUG,1"))
		GPS_ToggleDebug();
	
	if(strstr((char*) Config.RxBuffer, "LP,"))
		PWR_ProcessCommand(strstr((char*) Config.RxBuffer, "LP,"));
	
	/* Xoa bo dem nhan */
	Config.RxCounter = 0;
	memset(Config.RxBuffer, 0, CONFIG_RX_BUFFER_SIZE);
}

/**************************************************************************************
 * Function Name  	: Config_Tick1ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Tick 1ms xu ly module config
**************************************************************************************/
void Config_Tick1ms(void)
{
	if(Config.ReceiveTimeOut > 0)
	{
		Config.ReceiveTimeOut--;
		if(Config.ReceiveTimeOut == 0)
			Config.NewData = 1;
	}
}

