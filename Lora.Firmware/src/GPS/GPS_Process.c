/*
******************************************************************************
  * @file    	: GPS_Process.c
  * @version 	: V1.0.0
  * @date    	: 23/04/20224
  * @brief   	: Dinh nghia cac ham dung trong module
******************************************************************************
*/

/* Includes */
#include "Debug.h"
#include "stdlib.h"
#include "string.h"
#include "Utilities.h"
#include "GPS_Process.h"

/* Khai bao cac bien dung trong module */
GPSDataStructure				GPSData;

/*******************************************************************************
 * Function Name  	: GPS_ProcessData
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly cac ban tin GPS
*******************************************************************************/
void GPS_ProcessData(char* Data)
{
	uint16_t Begin, End;
	char Buffer[100];
	
	if(strstr(Data, "$GPRMC"))
	{
		SplitString(Data, Buffer, '$', 0x0D);
		GPS_RMCMessageProcess(Buffer);
	}
}

/*******************************************************************************
 * Function Name  	: GPS_RMCMessageProcess
 * Return         	: None
 * Parameters 			: None
 * Description			: Xu ly ban tin RMC
*******************************************************************************/
void GPS_RMCMessageProcess(char* Message)
{
	uint16_t Index;
	uint32_t tmpValue;
	char tmpBuffer[50];
	
	/* Time */
	Index = FindIndexOfCharacter(',', Message);
	tmpValue = GetNumberFromString(++Index, Message);
	
	GPSData.UTCTime.Hour 	= tmpValue / 10000;
	GPSData.UTCTime.Min		= (tmpValue % 10000) / 100;
	GPSData.UTCTime.Sec		= tmpValue % 100;
	
	/* Valid */
	Index += FindIndexOfCharacter(',', &Message[Index]);
	if(Message[++Index] == 'A')
		GPSData.Valid = 1;
	else 
		GPSData.Valid = 0;
	
	if(GPSData.Valid == 0)
	{
		DebugPrint("\rGPS: Invalid.");
		return;
	}
	
	/* Latitude */
	Index += FindIndexOfCharacter(',', &Message[Index]);
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	if(SplitString(&Message[Index], tmpBuffer, ',', ','))
		GPSData.Lat = atof(tmpBuffer);
	
	/* N/S */
	Index++;
	Index += FindIndexOfCharacter(',', &Message[Index]);
	if(Message[++Index] == 'N')
		GPSData.NorS = 1;
	else 
		GPSData.NorS = 0;
	
	/* Longitude */
	Index += FindIndexOfCharacter(',', &Message[Index]);
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	if(SplitString(&Message[Index], tmpBuffer, ',', ','))
		GPSData.Long = atof(tmpBuffer);
	
	/* E/W */
	Index++;
	Index += FindIndexOfCharacter(',', &Message[Index]);
	if(Message[++Index] == 'E')
		GPSData.EorW = 1;
	else 
		GPSData.EorW = 0;
	
	/* Speed */
	Index += FindIndexOfCharacter(',', &Message[Index]);
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	if(SplitString(&Message[Index], tmpBuffer, ',', ','))
		GPSData.Speed = atof(tmpBuffer);
	
	/* COG */
	Index++;
	Index += FindIndexOfCharacter(',', &Message[Index]);
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	if(SplitString(&Message[Index], tmpBuffer, ',', ','))
		GPSData.COG = atof(tmpBuffer);
	
	/* Date */
	Index++;
	Index += FindIndexOfCharacter(',', &Message[Index]);
	tmpValue = GetNumberFromString(++Index, Message);
	
	GPSData.UTCTime.Date 	= tmpValue / 10000;
	GPSData.UTCTime.Month	= (tmpValue % 10000) / 100;
	GPSData.UTCTime.Year	= tmpValue % 100;
	
	DebugPrint("\rValid: %d. UTC Time: %02d.%02d.%02d, %02d:%02d:%02d. ", GPSData.Valid, GPSData.UTCTime.Date, GPSData.UTCTime.Month, GPSData.UTCTime.Year, GPSData.UTCTime.Hour, GPSData.UTCTime.Min, GPSData.UTCTime.Sec);
	DebugPrint("North: %d. Latitude: %f. East: %d. Longitude: %f. Speed: %f. COG: %f.", GPSData.NorS, GPSData.Lat, GPSData.EorW, GPSData.Long, GPSData.Speed, GPSData.COG);
}

