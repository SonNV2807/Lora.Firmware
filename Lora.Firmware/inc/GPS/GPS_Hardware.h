/*
******************************************************************************
  * @file    	: GPS_Hardware.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__GPS_HARDWARE_H__
#define		__GPS_HARDWARE_H__

/* Includes */
#include "main.h"

#define	GPS_RX_BUFFER_SIZE					1400

/* Khai bao phan cung module */
#define GPS_USART										USART3
#define GPS_USART_CLK								RCC_APB1Periph_USART3

#define	GPS_USART_TX_GPIO						GPIOB
#define	GPS_USART_TX_CLK						RCC_AHBPeriph_GPIOB
#define	GPS_USART_TX_PIN						GPIO_Pin_10
#define	GPS_USART_TX_Source					GPIO_PinSource10

#define	GPS_USART_RX_GPIO						GPIOB
#define	GPS_USART_RX_CLK						RCC_AHBPeriph_GPIOB
#define	GPS_USART_RX_PIN						GPIO_Pin_11
#define	GPS_USART_RX_Source					GPIO_PinSource11

#define	GPS_PWRCTRL_GPIO						GPIOB
#define	GPS_PWRCTRL_CLK							RCC_AHBPeriph_GPIOB
#define	GPS_PWRCTRL_PIN							GPIO_Pin_2

#define	GPS_PPS_GPIO								GPIOB
#define	GPS_PPS_CLK									RCC_AHBPeriph_GPIOB
#define	GPS_PPS_PIN									GPIO_Pin_1

#define	GPS_STANDBY_GPIO						GPIOB
#define	GPS_STANDBY_CLK							RCC_AHBPeriph_GPIOB
#define	GPS_STANDBY_PIN							GPIO_Pin_0

#define GPS_PWRCTRL_High()					GPIO_SetBits(GPS_PWRCTRL_GPIO, GPS_PWRCTRL_PIN)
#define GPS_PWRCTRL_Low()						GPIO_ResetBits(GPS_PWRCTRL_GPIO, GPS_PWRCTRL_PIN)

#define GPS_STANDBY_High()					GPIO_SetBits(GPS_STANDBY_GPIO, GPS_STANDBY_PIN)
#define GPS_STANDBY_Low()						GPIO_ResetBits(GPS_STANDBY_GPIO, GPS_STANDBY_PIN)

/* Khai bao cau truc du lieu module */
typedef struct
{
	uint8_t		Debug;
	uint8_t 	NewData;
	uint16_t	RxCounter;
	uint8_t		RxBuffer[GPS_RX_BUFFER_SIZE];
	uint16_t	ReceiveTimeOut;
	uint16_t	Tick1ms;
	
}	GPSStructure;

/* Khai bao bien dung trong module */
extern GPSStructure				GPS;

/* Khai bao cac ham dung trong module */
void GPS_Initialize(uint32_t Baudrate);
void GPS_SendByte(char Byte);
void GPS_SendBytes(uint8_t* Buffer, uint16_t Length);
void GPS_SendSDKCommand(const char* Cmd);
void GPS_ReceiveData(uint8_t Data);
void GPS_Tick1ms(void);
void GPS_Process(void);
void GPS_ClearRxBuffer(void);
void GPS_ToggleDebug(void);

/* Layer 2 */
static void GPS_HardwareInitialize(uint32_t Baudrate);
static void GPS_IOInitialize(void);

#endif

