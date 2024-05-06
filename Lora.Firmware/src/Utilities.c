/*
******************************************************************************
  * @file    	: Utilities.c
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

/*******************************************************************************
 * Function Name  	: Delay_us
 * Return         	: None
 * Parameters 			: None
 * Description			: Delay theo us
*******************************************************************************/
void Delay_us(uint16_t Time)
{
	uint16_t i;
	
	Watchdog_Reset();
	
	for(i = (10*Time); i != 0; i--)
	{}
		
	Watchdog_Reset();
}

/*******************************************************************************
 * Function Name  	: Delay_ms
 * Return         	: None
 * Parameters 			: None
 * Description			: Delay theo ms
*******************************************************************************/
void Delay_ms(uint16_t Time)
{
	xSystem.Delay_ms = Time;
	
	while(xSystem.Delay_ms)
	{
		Watchdog_Reset();
	}
}

/*******************************************************************************
 * Function Name  	: CountTime
 * Return         	: None
 * Parameters 			: None
 * Description			: Dem thoi gian
*******************************************************************************/
void CountTime(void)
{
	DebugPrint("\rXu ly het %d ms", xSystem.Tick1ms);
}

/*******************************************************************************
 * Function Name  	: GetNumberFromString
 * Return         	: None
 * Parameters 			: None
 * Description			: Lay gia tri so tu 1 chuoi
*******************************************************************************/
uint32_t GetNumberFromString(uint16_t BeginIndex, char* Buffer)
{
	uint16_t Count = BeginIndex;
	uint32_t Value = 0;
	
	while(Buffer[Count] && Count < 1024)
	{
		if((Buffer[Count] >= '0') && (Buffer[Count] <= '9'))
		{
			Value *= 10;
			Value += Buffer[Count] - 48;
		}
		else
			break;
		
		Count++;
	}
	
	return Value;
}

/*******************************************************************************
 * Function Name  	: FindIndexOfCharacter
 * Return         	: None
 * Parameters 			: None
 * Description			: Tim vi tri cua ky tu trong 1 chuoi
*******************************************************************************/
int16_t FindIndexOfCharacter(char Character, char* Buffer)
{
	uint16_t Index, Length;
	
	Length = strlen(Buffer);
	
	for(Index = 0; Index < Length; Index++)
	{
		if(Buffer[Index] == Character)
			return Index;
	}
	
	return -1;
}

/*******************************************************************************
 * Function Name  	: SplitString
 * Return         	: None
 * Parameters 			: None
 * Description			: Lay ra 1 phan cua 1 chuoi
*******************************************************************************/
uint8_t SplitString(char* Data, char* Result, char CharBegin, char CharEnd)
{
	int16_t	Begin = FindIndexOfCharacter(CharBegin, Data);
	int16_t	End 	= FindIndexOfCharacter(CharEnd, &Data[Begin+1]);
	int16_t	i;

	if((Begin == -1) || (End == -1))
		return 0;

	for(i = 0; i < End; i++)
	{
		Result[i] = Data[Begin + i + 1];	
	}
		
	return 1;	
}

/*******************************************************************************
 * Function Name  	: GetCheckSum
 * Return         	: None
 * Parameters 			: None
 * Description			: Tinh checksum
*******************************************************************************/
uint32_t GetCheckSum(uint8_t *Buffer, uint32_t Length)
{
	uint32_t i, Checksum = 0;
	
	for(i = 0; i < Length; i++)
		Checksum += Buffer[i];
	
	return Checksum;
}

/*******************************************************************************
 * Function Name  	: GetCRC_16_Modbus
 * Return         	: None
 * Parameters 			: None
 * Description			: Tinh toan CRC-16 modbus
*******************************************************************************/
uint16_t GetCRC_16_Modbus(uint8_t* Buffer, uint16_t Length)
{
	uint16_t i, j, SwapByteValue, CRC16 = 0xFFFF;
	
	for(i = 0; i < Length; i++)
	{
		CRC16 ^= (uint16_t)Buffer[i];
		
		for(j = 0; i < 8; j++)
		{
			if((CRC16 & 0x0001) != 0)
			{
				CRC16 >>= 1;
				CRC16 ^= 0xA001;
			}
			else
				CRC16 >>= 1;
		}
	}
	
//	SwapByteValue = (CRC16 << 8) + (CRC16 >> 8);
	
	return CRC16;
}

/*******************************************************************************
 * Function Name  	: ConvertMinSecToDegree
 * Return         	: None
 * Parameters 			: None
 * Description			: Chuyen phut, guây sang do
*******************************************************************************/
float ConvertMinToDegree(float Min)
{
	return Min/60;
}

