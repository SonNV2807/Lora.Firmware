/*
******************************************************************************
  * @file    	: PowerCtrl.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Debug.h"
#include "Watchdog.h"
#include "PowerCtrl.h"
#include "InitSystem.h"

/*******************************************************************************
 * Function Name  	: PWR_Process
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly cac che do Power
*******************************************************************************/
void PWR_Process(void)
{
	static uint32_t Tick1s = 0;
	
	Tick1s++;
	
	if(Tick1s != 5)
		return;
	
	Watchdog_Reset();
	
	PWR_LowPowerRunMode(ENABLE);
	
//	PWR_SleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
	
//	PWR_LowPowerSleepMode();
	
//	PWR_STOPMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);
	
//	DebugPrint("\rEnter Standby mode.");
//	PWR_EnterSTANDBYMode();
}

/*******************************************************************************
 * Function Name  	: PWR_LowPowerRunMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do low-power run cua MCU
*******************************************************************************/
void PWR_LowPowerRunMode(FunctionalState NewState)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
	RCC_MSIRangeConfig(RCC_MSIRange_0);
	
	SysTickConfig();
	Debug_Initialize(115200);
	
	DebugPrint("\rEnter Low-power Run mode.");
	
	PWR_EnterLowPowerRunMode(NewState);
}

/*******************************************************************************
 * Function Name  	: PWR_SleepMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do sleep cua MCU
*******************************************************************************/
void PWR_SleepMode(uint8_t SleepMode, uint8_t EntryMode)
{
//	/* Configure low-power mode */
//  SCB->SCR &= ~( SCB_SCR_SLEEPDEEP_Msk );  	// clear bit SLEEPDEEP
//  SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;     	// set bit SLEEPONEXIT
//     
//  /* Ensure Flash memory stays on */
//  FLASH->ACR &= ~FLASH_ACR_SLEEP_PD;
//  __WFE();  																	// enter low-power mode
	
//	SCB->SCR &= ~( SCB_SCR_SLEEPDEEP_Msk );  			// clear SLEEPDEEP bit
//	
//	if(SleepMode == SLEEP_ON_EXIT)
//		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;     		// set SLEEPONEXIT bit
//	else	
//		SCB->SCR &= ~(SCB_SCR_SLEEPONEXIT_Msk);     // clear SLEEPONEXIT bit
//	
//	if(EntryMode == WAIT_FOR_INTERRUPT)
//		__WFI();
//	else
//		__WFE();
	
	DebugPrint("\rEnter Sleep mode.");
	PWR_EnterSleepMode(PWR_Regulator_ON, PWR_SLEEPEntry_WFI);
}	

/*******************************************************************************
 * Function Name  	: PWR_LowPowerSleepMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do Low-power Sleep cua MCU
*******************************************************************************/
void PWR_LowPowerSleepMode(void)
{
	FLASH_SLEEPPowerDownCmd(ENABLE);
	
	RCC_MSIRangeConfig(RCC_MSIRange_0);
	
	SysTickConfig();
	Debug_Initialize(115200);
	
	DebugPrint("\rEnter Low-power Sleep mode.");
	PWR_EnterSleepMode(PWR_Regulator_LowPower, PWR_SLEEPEntry_WFI);
}	

/*******************************************************************************
 * Function Name  	: PWR_StopMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do stop cua MCU
*******************************************************************************/
void PWR_StopMode(uint8_t EntryMode)
{	
//	 /* Enable Clocks */
//    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
//    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
//     
//    /* Configure PA0 as External Interrupt */
//    GPIOA->MODER &= ~( GPIO_MODER_MODE0 ); // PA0 is in Input mode
//    EXTI->IMR |= EXTI_IMR_IM0; // interrupt request from line 0 not masked
//    EXTI->RTSR |= EXTI_RTSR_TR0; // rising trigger enabled for input line 0
//     
//    // Enable interrupt in the NVIC
//    NVIC_EnableIRQ( EXTI0_1_IRQn );
//    NVIC_SetPriority( EXTI0_1_IRQn, BTN_INT_PRIO );
//     
//    /* Prepare to enter stop mode */
//    PWR->CR |= PWR_CR_CWUF; // clear the WUF flag after 2 clock cycles
//    PWR->CR &= ~( PWR_CR_PDDS ); // Enter stop mode when the CPU enters deepsleep
//    RCC->CFGR |= RCC_CFGR_STOPWUCK; // HSI16 oscillator is wake-up from stop clock
//    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk; // low-power mode = stop mode
//    __WFI(); // enter low-power mode
	
//	PWR->CR |= PWR_CR_CWUF;									// clear wake up flag
//	
//	PWR->CR &= ~(PWR_CR_PDDS);							// clear PDDS bit
//	
//	PWR->CR &= ~(PWR_CR_LPSDSR);						// set LPSDSR bit
//	
//	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;  		// set SLEEPDEEP bit
//	
//	if(EntryMode == WAIT_FOR_INTERRUPT)
//		__WFI();
//	else
//		__WFE();
//	
//	FLASH->OBR |= FLASH_OBR_IWDG_SW;
//	
//	SCB->SCR &= ~(SCB_SCR_SLEEPDEEP_Msk);  	// reset SLEEPDEEP bit
  
  /* Check the parameters */
  assert_param(IS_PWR_REGULATOR(PWR_Regulator));
  assert_param(IS_PWR_STOP_ENTRY(PWR_STOPEntry));
  
  /* Clear PDDS and LPDSR bits */
  PWR->CR &= ~(PWR_CR_PDDS);
  
  /* Set LPDSR bit according to PWR_Regulator value */
  PWR->CR &= ~(PWR_CR_LPSDSR);
  
  /* Set SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR |= SCB_SCR_SLEEPDEEP;
  
  /* Select STOP mode entry --------------------------------------------------*/
	if(EntryMode == WAIT_FOR_INTERRUPT)
		__WFI();
	else
		__WFE();
	
  /* Reset SLEEPDEEP bit of Cortex System Control Register */
  SCB->SCR &= (uint32_t)~((uint32_t)SCB_SCR_SLEEPDEEP);  
	
	
}

/*******************************************************************************
 * Function Name  	: PWR_StandbyMode
 * Return         	: None
 * Parameters 			: None
 * Description			: Che do standby cua MCU
*******************************************************************************/
void PWR_StandbyMode(void)
{
	PWR_EnterSTANDBYMode();
}

/*******************************************************************************
 * Function Name  	: EXTI_Configuration
 * Return         	: None
 * Parameters 			: None
 * Description			: Cau hinh ngat EXTI
*******************************************************************************/
void EXTI_Configuration(void)
{
	/* Khai bao bien cau truc */
	GPIO_InitTypeDef		GPIO_InitStructure;
	EXTI_InitTypeDef		EXTI_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	
	/* Cap clock cho ngoai vi */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	/* Configure PA0 pin as input floating */	
	GPIO_InitStructure.GPIO_Pin 	= GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd 	= GPIO_PuPd_NOPULL;											
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	/* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line 		= EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode 		= EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel 										= EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	EXTI_GenerateSWInterrupt(EXTI_Line0);
}

