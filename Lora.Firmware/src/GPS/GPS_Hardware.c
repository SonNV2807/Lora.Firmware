/*
******************************************************************************
  * @file    	: GPS_Hardware.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Debug.h"
#include "string.h"
#include "Watchdog.h"
#include "Utilities.h"
#include "GPS_Process.h"
#include "GPS_Hardware.h"

/* Khai bao cac bien dung trong module */
GPSStructure				GPS;

/*******************************************************************************
 * Function Name  	: GPS_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao module GPS
*******************************************************************************/
void GPS_Initialize(uint32_t Baudrate)
{
	GPS_HardwareInitialize(Baudrate);
	
	GPS_IOInitialize();
}

/*******************************************************************************
 * Function Name  	: GPS_HardwareInitialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao UART cua module GPS
*******************************************************************************/
static void GPS_HardwareInitialize(uint32_t Baudrate)
{
	/* Khai bao bien cau truc */
	GPIO_InitTypeDef				GPIO_InitStructure;
	USART_InitTypeDef				USART_InitStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;
	
	/* Disable */
	USART_DeInit(GPS_USART);
	USART_Cmd(GPS_USART, DISABLE);
	USART_ITConfig(GPS_USART, USART_IT_RXNE, DISABLE);
	
	/* Cap clock */
	RCC_APB1PeriphClockCmd(GPS_USART_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(GPS_USART_TX_CLK | GPS_USART_RX_CLK, ENABLE);
	
	/* Connect Pin to USART */
	GPIO_PinAFConfig(GPS_USART_TX_GPIO, GPS_USART_TX_Source, GPIO_AF_USART3);
	GPIO_PinAFConfig(GPS_USART_RX_GPIO, GPS_USART_RX_Source, GPIO_AF_USART3);
	
	/* Cau hinh GPIO */
	GPIO_InitStructure.GPIO_Pin 	= GPS_USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;											
	GPIO_Init(GPS_USART_TX_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPS_USART_RX_PIN;										
	GPIO_Init(GPS_USART_RX_GPIO, &GPIO_InitStructure);
	
	/* Cau hinh USART */
	USART_InitStructure.USART_BaudRate 							= Baudrate;					
	USART_InitStructure.USART_WordLength 						= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 							= USART_StopBits_1;	
	USART_InitStructure.USART_Parity 								= USART_Parity_No;									
	USART_InitStructure.USART_Mode 									= USART_Mode_Tx | USART_Mode_Rx;	
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;						
	USART_Init(GPS_USART, &USART_InitStructure);	
	
	/* Cau hinh Interrupt */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);						
	NVIC_InitStructure.NVIC_IRQChannel 										= USART3_IRQn;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;			
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 1;							
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;				
	NVIC_Init(&NVIC_InitStructure);	
	
	/* Enable */
	USART_ITConfig(GPS_USART, USART_IT_RXNE, ENABLE);
	USART_Cmd(GPS_USART, ENABLE);
}	

/*******************************************************************************
 * Function Name  	: GPS_IOInitialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao cac chan dieu khien cua module GPS
*******************************************************************************/
static void GPS_IOInitialize(void)
{
	/* Khai bao bien cau truc */
	GPIO_InitTypeDef				GPIO_InitStructure;
	
	/* Cap clock */
	RCC_AHBPeriphClockCmd(GPS_PWRCTRL_CLK | GPS_PPS_CLK | GPS_STANDBY_CLK, ENABLE);
	
	/* Cau hinh GPIO */
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;	
	
	GPIO_InitStructure.GPIO_Pin 	= GPS_PWRCTRL_PIN;										
	GPIO_Init(GPS_PWRCTRL_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= GPS_STANDBY_PIN;										
	GPIO_Init(GPS_STANDBY_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin 	= GPS_PPS_PIN;
	GPIO_Init(GPS_PPS_GPIO, &GPIO_InitStructure);
	
	GPS_PWRCTRL_High();
	Delay_ms(100);
	GPS_STANDBY_High();
}

/*******************************************************************************
 * Function Name  	: GPS_SendByte
 * Return         	: None
 * Parameters 			: None
 * Description			: Gui 1 byte du lieu sang module GPS
*******************************************************************************/
void GPS_SendByte(char Byte)
{
	while(USART_GetFlagStatus(GPS_USART, USART_FLAG_TC) == 0) {}
		
	USART_SendData(GPS_USART, (uint16_t)Byte);
}

/*******************************************************************************
 * Function Name  	: GPS_SendBytes
 * Return         	: None
 * Parameters 			: None
 * Description			: Gui 1 mang byte sang module GPS
*******************************************************************************/
void GPS_SendBytes(uint8_t* Buffer, uint16_t Length)
{
	uint16_t i;
	for(i = 0; i < Length; i++)
		GPS_SendByte((char)Buffer[i]);
}

/*******************************************************************************
 * Function Name  	: GPS_SendSDKCommand
 * Return         	: None
 * Parameters 			: None
 * Description			: Gui lenh SDK sang module GPS
*******************************************************************************/
void GPS_SendSDKCommand(const char* Cmd)
{
	uint16_t Length = strlen(Cmd);
	uint16_t i = 0;
	for(i = 0; i < Length; i++)
	{
		GPS_SendByte(Cmd[i]);					
		Watchdog_Reset();
    if(GPS.Debug)
			DebugPutc(Cmd[i]);
	}
}

/*******************************************************************************
 * Function Name  	: GPS_ReceiveData
 * Return         	: None
 * Parameters 			: None
 * Description			: Nhan du lieu tu module GPS va dong goi vao bo dem
*******************************************************************************/
void GPS_ReceiveData(uint8_t Data)
{
	GPS.RxBuffer[GPS.RxCounter++] = Data;
	
	GPS.RxBuffer[GPS.RxCounter] 	= 0;
	
	if(GPS.RxCounter >= GPS_RX_BUFFER_SIZE)
		GPS.RxCounter = 0;
	
	GPS.ReceiveTimeOut						= 70;
}

/*******************************************************************************
 * Function Name  	: GPS_Tick1ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Tick 1ms xu ly module GPS
*******************************************************************************/
void GPS_Tick1ms(void)
{
	GPS.Tick1ms++;
	if(GPS.ReceiveTimeOut > 0)
	{
		GPS.ReceiveTimeOut--;
		if(GPS.ReceiveTimeOut == 0)
			GPS.NewData = 1;
	}
}

/*******************************************************************************
 * Function Name  	: GPS_Process
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly du lieu nhan duoc tu module GPS
*******************************************************************************/
void GPS_Process(void)
{
	uint16_t i;
	
	if(GPS.NewData == 0)
		return;
	
	if(GPS.Debug)
	{
		DebugPrint("\rGPS: Du lieu nhan: \r");
		for(i = 0; i < GPS.RxCounter; i++)
			DebugPutc(GPS.RxBuffer[i]);
	}
	
	GPS_ProcessData((char*)GPS.RxBuffer);
	
	GPS_ClearRxBuffer();
}

/*******************************************************************************
 * Function Name  	: GPS_ClearRxBuffer
 * Return         	: None
 * Parameters 			: None
 * Description			: Xoa bo dem nhan du lieu GPS
*******************************************************************************/
void GPS_ClearRxBuffer(void)
{
	GPS.NewData 	= 0;
	GPS.RxCounter = 0;
	memset(GPS.RxBuffer, 0, sizeof(GPS.RxBuffer));
}

/*******************************************************************************
 * Function Name  	: GPS_ToggleDebug
 * Return         	: None
 * Parameters 			: None
 * Description			: Bat/tat che do debug GPS
*******************************************************************************/
void GPS_ToggleDebug(void)
{
	GPS.Debug = 1 - GPS.Debug;
}

