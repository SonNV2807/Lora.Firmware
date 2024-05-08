/*
******************************************************************************
  * @file    	: PowerCtrl.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "RTC.h"
#include "time.h"

static rtc_state_t rtc_callback;

void RTC_POWERON(void)
{
    /* Enable write access to RTC registers */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_DBP;

    /* Reset RTC domain */
    RCC->CSR |= RCC_CSR_RTCRST;
    RCC->CSR &= ~(RCC_CSR_RTCRST);

    /* Enable the LSE clock (external 32.768 kHz oscillator) */
    RCC->CSR &= ~(RCC_CSR_LSEON);
    RCC->CSR &= ~(RCC_CSR_LSEBYP);
    RCC->CSR |= RCC_CSR_LSEON;
    while ( (RCC->CSR & RCC_CSR_LSERDY) == 0 );

    /* Switch RTC to LSE clock source */
    RCC->CSR &= ~(RCC_CSR_RTCSEL);
    RCC->CSR |= RCC_CSR_RTCSEL_LSE;

    /* Enable the RTC */
    RCC->CSR |= RCC_CSR_RTCEN;
}

/*******************************************************************************
 * Function Name  	: RTC_Initialize
 * Return         	: None
 * Parameters 			: None
 * Description			: Khoi tao RTC
*******************************************************************************/
void RTC_Initialize(void)
{	
		RTC_POWERON();

    /* Unlock RTC write protection */
    RTC->WPR = RTC_WRITE_PROTECTION_KEY1;
    RTC->WPR = RTC_WRITE_PROTECTION_KEY2;

    /* Enter RTC Init mode */
    RTC->ISR = 0;
    RTC->ISR |= RTC_ISR_INIT;
    while ( (RTC->ISR & RTC_ISR_INITF) == 0 );

    /* Set 24-h clock */
    RTC->CR |= RTC_CR_FMT;
    /* Timestamps enabled */
    RTC->CR |= RTC_CR_TSE;

    /* Configure the RTC PRER */
    RTC->PRER = RTC_SYNC_PRESCALER;
    RTC->PRER |= (RTC_ASYNC_PRESCALER << 16);

    /* Exit RTC init mode */
    RTC->ISR &= (uint32_t)~RTC_ISR_INIT;

    /* Enable RTC write protection */
    RTC->WPR = 0xff;     
}

/*******************************************************************************
 * Function Name  	: RTC_Configuration
 * Return         	: None
 * Parameters 			: None
 * Description			: Cau hinh RTC
*******************************************************************************/
void RTC_Configuration(void)
{
	EXTI_InitTypeDef		EXTI_InitStructure;
	NVIC_InitTypeDef		NVIC_InitStructure;
	
	EXTI_DeInit();
	EXTI_InitStructure.EXTI_Line 			= EXTI_Line20;
	EXTI_InitStructure.EXTI_Mode 			= EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger 	= EXTI_Trigger_Rising;	
	EXTI_InitStructure.EXTI_LineCmd 	= ENABLE;						
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	
	NVIC_InitStructure.NVIC_IRQChannel 										= RTC_WKUP_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;	
	NVIC_Init(&NVIC_InitStructure);	
	
	/* Enable RTC Wakeup Interrupt */
	RTC_ITConfig(RTC_IT_WUT, ENABLE);
	/* Disable RTC WakeUp */
	RTC_WakeUpCmd(DISABLE);
	/* Config RTC WakeUp clock source */
	RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);
	/* Config RTC WakeUp counter */
	RTC_SetWakeUpCounter(0x500B);
	/* Enable RTC WakeUp */
	RTC_WakeUpCmd(ENABLE);
}

uint8_t rtc_get_time(struct tm *time)
{
    time->tm_year = MCU_YEAR_OFFSET;
    time->tm_year +=(((RTC->DR & RTC_DR_YT)  >> 20) * 10) + ((RTC->DR & RTC_DR_YU)  >> 16);
    time->tm_mon  = (((RTC->DR & RTC_DR_MT)  >> 12) * 10) + ((RTC->DR & RTC_DR_MU)  >>  8) - 1;
    time->tm_mday = (((RTC->DR & RTC_DR_DT)  >>  4) * 10) + ((RTC->DR & RTC_DR_DU)  >>  0);
    time->tm_hour = (((RTC->TR & RTC_TR_HT)  >> 20) * 10) + ((RTC->TR & RTC_TR_HU)  >> 16);
    if ( RTC->TR & RTC_TR_PM )
        time->tm_hour += 12;
    time->tm_min  = (((RTC->TR & RTC_TR_MNT) >> 12) * 10) + ((RTC->TR & RTC_TR_MNU) >>  8);
    time->tm_sec  = (((RTC->TR & RTC_TR_ST)  >>  4) * 10) + ((RTC->TR & RTC_TR_SU)  >>  0);
    return 0;
}

uint8_t rtc_set_alarm(struct tm *time, rtc_alarm_cb_t cb, void *arg)
{
    /* Enable write access to RTC registers */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR |= PWR_CR_DBP;

    /* Unlock RTC write protection */
    RTC->WPR = RTC_WRITE_PROTECTION_KEY1;
    RTC->WPR = RTC_WRITE_PROTECTION_KEY2;

    /* Enter RTC Init mode */
    RTC->ISR |= RTC_ISR_INIT;
    while ( (RTC->ISR & RTC_ISR_INITF) == 0 );

    RTC->CR &= ~(RTC_CR_ALRAE);
    while ( (RTC->ISR & RTC_ISR_ALRAWF) == 0 );
    RTC->ALRMAR &= ~(RTC_ALRMAR_MSK1 | RTC_ALRMAR_MSK2 | RTC_ALRMAR_MSK3 | RTC_ALRMAR_MSK4);
    RTC->ALRMAR = ( (((uint32_t)byte2bcd(time->tm_mday) << 24) & (RTC_ALRMAR_DT | RTC_ALRMAR_DU) ) |
                    (((uint32_t)byte2bcd(time->tm_hour) << 16) & (RTC_ALRMAR_HT | RTC_ALRMAR_HU) ) |
                    (((uint32_t)byte2bcd(time->tm_min)  <<  8) & (RTC_ALRMAR_MNT| RTC_ALRMAR_MNU)) |
                    (((uint32_t)byte2bcd(time->tm_sec)  <<  0) & (RTC_ALRMAR_ST | RTC_ALRMAR_SU) ) );
    /* Enable Alarm A */
    RTC->CR |= RTC_CR_ALRAE;
    RTC->CR |= RTC_CR_ALRAIE;
    RTC->ISR &= ~(RTC_ISR_ALRAF);

    /* Exit RTC init mode */
    RTC->ISR &= (uint32_t)~RTC_ISR_INIT;
    /* Enable RTC write protection */
    RTC->WPR = 0xFF;

    EXTI->IMR  |= EXTI_IMR_MR17;
    EXTI->RTSR |= EXTI_RTSR_TR17;
    NVIC_SetPriority(RTC_Alarm_IRQn, 5);
    NVIC_EnableIRQ(RTC_Alarm_IRQn);

    rtc_callback.cb = cb;
    rtc_callback.arg = arg;

    return 0;
}

static uint8_t byte2bcd(uint8_t value)
{
  uint8_t bcdhigh = 0;

  while (value >= 10)
  {
    bcdhigh++;
    value -= 10;
  }

  return  ((uint8_t)(bcdhigh << 4) | value);
}

void RTC_ClockConfig(void)
{
	/* Enable Clock for Power interface */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	/* Disable backup domain write protection */
	PWR->CR |= PWR_CR_DBP;
	
	while((PWR->CR & PWR_CR_DBP) == 0);
}
