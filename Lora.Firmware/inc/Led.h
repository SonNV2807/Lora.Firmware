/*
******************************************************************************
  * @file    	: Led.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__LED_H__
#define 	__LED_H__

/* Includes */
#include "main.h"

/* Khai bao so dau ra dieu khien Led */
#define LED_NBOF			4

/* Khai bao phan cung cua module */
#define LED1_GPIO			GPIOA
#define LED1_CLK			RCC_AHBPeriph_GPIOA
#define LED1_PIN			GPIO_Pin_7

#define LED2_GPIO			GPIOA
#define LED2_CLK			RCC_AHBPeriph_GPIOA
#define LED2_PIN			GPIO_Pin_6

#define LED3_GPIO			GPIOA
#define LED3_CLK			RCC_AHBPeriph_GPIOA
#define LED3_PIN			GPIO_Pin_5

/* Khai bao kieu enum cho Led Id */
typedef enum
{
	LED1_ID = 0,
	LED2_ID,
	LED3_ID,
	LED4_ID
	
}	LedIdEnum;

/* Khai bao kieu enum cho Led Status */
typedef enum
{
	LED_OFF = 0,
	LED_ON
	
}	LedStatusEnum;

/* Dinh nghia cau truc du lieu dung trong module */
typedef struct
{
	uint16_t Period;
	uint16_t Tstart;
	uint16_t Ton;
	uint16_t Tick100ms;
	
}	LedStructure;

/* Khai bao cac ham dung trong module */
void Led_Initialize(void);
void Led_HardwareInitialize(void);
void Led_SoftwareInitialize(void);
void Led_Tick100ms(void);
void Led_Ctrl(uint8_t Id, uint8_t Status);

#endif

