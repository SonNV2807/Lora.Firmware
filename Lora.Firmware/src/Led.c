/*
******************************************************************************
  * @file    	: Led.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Led.h"

/* Khai bao cac bien dung trong module */
LedStructure		LED[LED_NBOF];

GPIO_TypeDef*		LED_GPIO 			= GPIOA;
uint32_t	LED_CLK 						= RCC_AHBPeriph_GPIOA;
uint16_t	LED_PIN[LED_NBOF] 	= {LED1_PIN, LED2_PIN, LED3_PIN};

/*******************************************************************************
 * Function Name  	: Led_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao module Led
*******************************************************************************/
void Led_Initialize(void)
{
	Led_HardwareInitialize();
	
	Led_SoftwareInitialize();
}

/*******************************************************************************
 * Function Name  	: Led_HardwareInitialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao phan cung module Led
*******************************************************************************/
void Led_HardwareInitialize(void)
{
	uint8_t i;
	
	/* Khai bao bien cau truc */
	GPIO_InitTypeDef		GPIO_InitStructure;
	
	/* Cap clock cho ngoai vi */
	RCC_AHBPeriphClockCmd(LED_CLK, ENABLE);
	
	/* Cau hinh GPIO */
	GPIO_InitStructure.GPIO_Mode	= GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_DOWN;
	
	for(i = 0 ; i < LED_NBOF ; i++) 
	{	
		GPIO_InitStructure.GPIO_Pin = LED_PIN[i];
		GPIO_Init(LED_GPIO, &GPIO_InitStructure);
		
		GPIO_SetBits(LED_GPIO, LED_PIN[i]);
	}
}

/*******************************************************************************
 * Function Name  	: Led_SoftwareInitialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao cac bien trong module Led
*******************************************************************************/
void Led_SoftwareInitialize(void)
{
	uint8_t i = 0;
	
	for(i = 0 ; i < LED_NBOF ; i++)
	{
		LED[i].Period 		= 10;
		LED[i].Tstart 		= 0;
		LED[i].Ton 				= (i + 1) * 2;
		LED[i].Tick100ms 	= 0;
		
		Led_Ctrl(i, LED_OFF);
	}
}

/*******************************************************************************
 * Function Name  	: Led_Tick10ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly Tick 10ms module Led
*******************************************************************************/
void Led_Tick100ms(void)
{
	uint8_t i = 0;
	
	for (i = 0; i < LED_NBOF - 2; i++) 
	{
		LED[i].Tick100ms++;
		
		if(LED[i].Tick100ms <= LED[i].Ton)
			Led_Ctrl(i, LED_ON);
		else
			Led_Ctrl(i, LED_OFF);
		
		if(LED[i].Tick100ms >= LED[i].Period)
			LED[i].Tick100ms = 0;
	}
}

/*******************************************************************************
 * Function Name  	: Led_Ctrl
 * Return         	: None
 * Parameters 			: Id va trang thai Led
 * Description			: Xu ly trang thai Led
*******************************************************************************/
void Led_Ctrl(uint8_t Id, uint8_t Status)
{
	if(Id >= LED_NBOF)
		return;
	
	switch(Status)
	{
		case LED_ON:
			GPIO_SetBits(LED_GPIO, LED_PIN[Id]);
			break;
		case LED_OFF:
			GPIO_ResetBits(LED_GPIO, LED_PIN[Id]);
			break;
	}
}

