/*
******************************************************************************
  * @file    	: Debug.h
  * @version 	: V1.0.0
  * @date    	: 29/07/2023
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__DEBUG_H__
#define		__DEBUG_H__

/* Includes */
#include "main.h"

/* Khai bao phan cung cua module */
#define Debug_UART							USART1
#define Debug_UART_CLK					RCC_APB2Periph_USART1

#define Debug_USART_TX_GPIO			GPIOA
#define Debug_USART_TX_CLK			RCC_AHBPeriph_GPIOA
#define Debug_USART_TX_PIN			GPIO_Pin_9
#define Debug_USART_TX_Source		GPIO_PinSource9

#define Debug_USART_RX_GPIO			GPIOA
#define Debug_USART_RX_CLK			RCC_AHBPeriph_GPIOA
#define Debug_USART_RX_PIN			GPIO_Pin_10
#define Debug_USART_RX_Source		GPIO_PinSource10

/* Khai bao cac ham dung trong module */
void Debug_Initialize(uint32_t Baudrate);
void DebugPutc(char Byte);
void DebugPrint(const char* str, ...);

/* Layer 2 */
static void DebugPuts(const char* s);
static void DebugItoa(long val, int radix, int len);
static void DebugFtoa(double value, int precision);

#endif

