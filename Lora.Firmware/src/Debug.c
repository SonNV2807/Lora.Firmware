/*
******************************************************************************
  * @file    	: Debug.c
  * @version 	: V1.0.0
  * @date    	: ??/??/20??
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "stdio.h"
#include "Debug.h"
#include "stdarg.h"

/*******************************************************************************
 * Function Name  	: Debug_Initialize
 * Return         	: None
 * Parameters 			: Toc do truyen du lieu
 * Description			: Khoi tao module Debug
*******************************************************************************/
void Debug_Initialize(uint32_t Baudrate)
{
	/* Khai bao bien cau truc */
	GPIO_InitTypeDef			GPIO_InitStructure;
	USART_InitTypeDef			USART_InitStructure;
	EXTI_InitTypeDef			EXTI_InitStructure;
	NVIC_InitTypeDef			NVIC_InitStructure;
	
	/* Disable */
	USART_DeInit(Debug_UART);
	USART_Cmd(Debug_UART, DISABLE);														
	USART_ITConfig(Debug_UART, USART_IT_RXNE, DISABLE);
	
	/* Cap clock cho ngoai vi */
	RCC_APB2PeriphClockCmd(Debug_UART_CLK, ENABLE);
	RCC_AHBPeriphClockCmd(Debug_USART_TX_CLK | Debug_USART_RX_CLK, ENABLE);
	
	/* Connect Pin to USART */
	GPIO_PinAFConfig(Debug_USART_TX_GPIO, Debug_USART_TX_Source, GPIO_AF_USART1);
	GPIO_PinAFConfig(Debug_USART_RX_GPIO, Debug_USART_RX_Source, GPIO_AF_USART1);
	
	/* Cau hinh GPIO */
	GPIO_InitStructure.GPIO_Pin 	= Debug_USART_TX_PIN;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd	= GPIO_PuPd_UP;											
	GPIO_Init(Debug_USART_TX_GPIO, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= Debug_USART_RX_PIN;										
	GPIO_Init(Debug_USART_RX_GPIO, &GPIO_InitStructure);
	
	/* Cau hinh USART */
	USART_InitStructure.USART_BaudRate 							= Baudrate;					
	USART_InitStructure.USART_WordLength 						= USART_WordLength_8b;
	USART_InitStructure.USART_StopBits 							= USART_StopBits_1;	
	USART_InitStructure.USART_Parity 								= USART_Parity_No;									
	USART_InitStructure.USART_Mode 									= USART_Mode_Rx | USART_Mode_Tx;	
	USART_InitStructure.USART_HardwareFlowControl 	= USART_HardwareFlowControl_None;	
	USART_Init(Debug_UART, &USART_InitStructure);	
	
	/* Cau hinh Interrupt */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);						
	NVIC_InitStructure.NVIC_IRQChannel 										= USART1_IRQn;				
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority 	= 1;			
	NVIC_InitStructure.NVIC_IRQChannelSubPriority 				= 0;							
	NVIC_InitStructure.NVIC_IRQChannelCmd 								= ENABLE;				
	NVIC_Init(&NVIC_InitStructure);			
	
	/* Enable */
	USART_ITConfig(Debug_UART, USART_IT_RXNE, ENABLE);							
	USART_Cmd(Debug_UART, ENABLE);
}

/*******************************************************************************
 * Function Name  	: DebugPutc
 * Return         	: None
 * Parameters 			: Byte du lieu can gui
 * Description			: Gui byte du lieu ra cong Debug
*******************************************************************************/
void DebugPutc(char Byte)
{
	/* Kiem tra trang thai cua bo truyen du lieu (SET: san sang truyen, RESET: chua san sang) */
	while (USART_GetFlagStatus(Debug_UART, USART_FLAG_TC) == RESET) {}
	
	USART_SendData(Debug_UART, (uint16_t)Byte);
}

/*******************************************************************************
 * Function Name  	: DebugPuts
 * Return         	: None
 * Parameters 			: Chuoi du lieu can gui
 * Description			: Gui chuoi du lieu ra cong Debug
*******************************************************************************/
static void DebugPuts(const char* s)
{
	char c;
	while ((c = *s++) != '\0')
	{
		DebugPutc(c);
	}
}

/*******************************************************************************
 * Function Name  	: DebugItoa
 * Return         	: None
 * Parameters 			: Byte du lieu nhan duoc tu cong Debug
 * Description			: Dong goi du lieu nhan duoc tu cong Debug
*******************************************************************************/
static void DebugItoa(long val, int radix, int len)
{
    uint8_t c, r, sgn = 0, pad = ' ';    
    uint8_t s[20], i = 0;    
    uint32_t v;

    if (radix < 0)
    {    
        radix = -radix;    
        if (val < 0) 
        {
            val = -val;    
            sgn = '-';    
        }    
    }   
	
    v = val;    
    r = radix;   
	
    if (len < 0) 
    {    
        len = -len;    
        pad = '0';    
    }  
	
    if (len > 20) return;    
    do 
    {    
        c = (uint8_t)(v % r);    
        if (c >= 10) c += 7;    
        c += '0';    
        s[i++] = c;    
        v /= r;    
    } while (v);  
	
    if (sgn) s[i++] = sgn; 
	
    while (i < len)    
        s[i++] = pad; 
		
    do    
        DebugPutc(s[--i]); 
    while (i);
}

/*******************************************************************************
 * Function Name  	: DebugFtoa
 * Return         	: None
 * Parameters 			: Byte du lieu nhan duoc tu cong Debug
 * Description			: Dong goi du lieu nhan duoc tu cong Debug (Ham mo rong)
*******************************************************************************/
static void DebugFtoa(double value, int precision) 
{	
	int d;
  char buffer[20]; 																							// Dinh nghia bo dem chua ket qua
  snprintf(buffer, sizeof(buffer), "%.*f", precision, value); 	// Chuyen so thap phan thanh chuoi

  char* result = buffer; 										

  while ((d = *result++) != 0) {
		DebugPutc(d); 										
  }
}

/*******************************************************************************
 * Function Name  	: Debug_ReceiveData
 * Return         	: None
 * Parameters 			: Byte du lieu nhan duoc tu cong Debug
 * Description			: Dong goi du lieu nhan duoc tu cong Debug
*******************************************************************************/
void DebugPrint(const char* str, ...)
{
    va_list arp;
    int d, r, w, s, l;
    va_start(arp, str);

    while ((d = *str++) != 0) 
    {
        if (d != '%')
        {    
            DebugPutc(d);
			continue;    
        }
		
        d = *str++; w = r = s = l = 0; 

		if (d == '%')
        {    
            DebugPutc(d); 
			continue;
        }		
		
        if (d == '0') 
        {    
            d = *str++; s = 1;    
        }    
		
        while ((d >= '0')&&(d <= '9')) 
        {    
            w += w * 10 + (d - '0');    
            d = *str++;    
        }    
		
        if (s) w = -w; 
		
        if (d == 'l') 
        {    
            l = 1;    
            d = *str++;    
        }    
		
        if (!d) break;  
		
        if (d == 's') 
        {    
            DebugPuts(va_arg(arp, char*));    
            continue;    
        }    
		
        if (d == 'c') 
        {    
            DebugPutc((char)va_arg(arp, int));    
            continue;    
        }  
		
		if (d == 'f')
		{
			DebugFtoa(va_arg(arp, double), 4);
            continue;
		}
		
        if (d == 'u') r = 10;    
        if (d == 'd') r = -10;    
        if (d == 'X' || d == 'x') r = 16; // 'x' added by mthomas in increase compatibility    
        if (d == 'b') r = 2;    
        if (!r) break;    
        if (l) 
        {    
            DebugItoa((long)va_arg(arp, long), r, w);    
        } 
        else 
        {    
            if (r > 0)        
                DebugItoa((unsigned long)va_arg(arp, int), r, w);        
            else        
                DebugItoa((long)va_arg(arp, int), r, w);
        }    
    }  
    va_end(arp);
}

