/*
******************************************************************************
  * @file    	: Interrupt.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Xu ly cac ham ngat
******************************************************************************
*/

/* Includes */
#include "Led.h"
#include "main.h"
#include "GPS_Hardware.h"
#include "Configuration.h"

/*******************************************************************************
 * Function Name  	: SysTick_Handler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles SysTick Handler.
*******************************************************************************/
void SysTick_Handler(void)
{
	if(xSystem.Delay_ms)
		xSystem.Delay_ms--;
	
	xSystem.Tick1ms++;
	xSystem.Tick10ms++;
	xSystem.Tick100ms++;
	xSystem.Tick1000ms++;
	
	/* Tick 1ms xu ly module Config */
	Config_Tick1ms();
	/* Tick 1ms xu ly module GPS */
	GPS_Tick1ms();
}

/*******************************************************************************
 * Function Name  	: USART1_IRQHandler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles USART1 global interrupt request.
*******************************************************************************/
void USART1_IRQHandler(void)
{
	uint16_t Data;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		Data = USART_ReceiveData(USART1);
		Config_ReceiveData(Data);
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
	}
}

/*******************************************************************************
 * Function Name  	: USART2_IRQHandler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles USART2 global interrupt request.
*******************************************************************************/
void USART2_IRQHandler(void)
{
	uint16_t Data;
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		Data = USART_ReceiveData(USART2);
	}
}

/*******************************************************************************
 * Function Name  	: USART3_IRQHandler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles USART2 global interrupt request.
*******************************************************************************/
void USART3_IRQHandler(void)
{
	uint16_t Data;
	
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		Data = USART_ReceiveData(USART3);
		GPS_ReceiveData(Data);
	}
}

/*******************************************************************************
 * Function Name  	: UART4_IRQHandler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles UART4 global interrupt request.
*******************************************************************************/
void UART4_IRQHandler(void)
{
	uint16_t Data;
	
	if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(UART4, USART_IT_RXNE);
		Data = USART_ReceiveData(UART4);
	}
}

/*******************************************************************************
 * Function Name  	: EXTI0_IRQHandler
 * Return         	: None
 * Parameters 			: None
 * Description			: This function handles EXTI0 global interrupt request.
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line0);
		Led_Ctrl(2, LED_ON);
	}
	else
		Led_Ctrl(2, LED_OFF);
}

