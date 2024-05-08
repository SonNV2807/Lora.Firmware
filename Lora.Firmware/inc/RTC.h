/*
******************************************************************************
  * @file    	: PowerCtrl.h
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Khai bao cac bien va cac ham dung trong module
******************************************************************************
*/

#ifndef		__RTC_H__
#define		__RTC_H__

/* Includes */
#include "main.h"
#include "time.h"

#define RTC_WRITE_PROTECTION_KEY1   		0xCA
#define RTC_WRITE_PROTECTION_KEY2   		0x53
#define RTC_SYNC_PRESCALER          		0xff 			/**< prescaler for 32.768 kHz oscillator */
#define RTC_ASYNC_PRESCALER         		0x7f 			/**< prescaler for 32.768 kHz oscillator */
#define MCU_YEAR_OFFSET									100

typedef void(*rtc_alarm_cb_t)(void *arg);

typedef struct {
    rtc_alarm_cb_t cb;        /**< callback called from RTC interrupt */
    void *arg;                /**< argument passed to the callback */
} rtc_state_t;

/* Khai bao cac ham dung trong module */
void RTC_Initialize(void);
void RTC_Configuration(void);

void RTC_POWERON(void);
uint8_t rtc_get_time(struct tm *time);
uint8_t rtc_set_alarm(struct tm *time, rtc_alarm_cb_t cb, void *arg);
static uint8_t byte2bcd(uint8_t value);

#endif

