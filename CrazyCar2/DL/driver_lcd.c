/*
 * driver_lcd.c
 *
 *  Created on: 14.11.2016
 *      Author: Sebo
 */

#include "driver_lcd.h"

#include <stdint.h>
#include <stdbool.h>
#include "..\HAL\hal_gpio.h"
#include "..\HAL\hal_usciB1.h"
#include "drl_lcd_fonts.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"


extern USCIB1_SPICom SpiCom;
extern unsigned char cmdArr[];

unsigned char InitArr[10] = {LCD_RESET_c, ADC_SEL_NORMAL, LCD_BIAS, COMMON_REVERSE,DISPLAY_line_start, POWER_CONT, RES_RATIO, ELEC_VOL_MODE, ELEC_VOL_VALUE, DISPLAY_ON};
unsigned char Init2Arr[9]={ LCD_RESET, LCD_BIAS, ADC_SEL_NORMAL, COMMON_REVERSE, RES_RATIO, ELEC_VOL_MODE, ELEC_VOL_VALUE, POWER_CONT, DISPLAY_ON };

void Driver_LCD_WriteCommand(unsigned char *data, unsigned char len)          //Write Commands übermitteln
{
	CS_L;
	unsigned int i = 0;
	command;
	SpiCom.TxData.Data[0] = 0;
	for(i = 0; i < len; i++)
	{
		SpiCom.TxData.Data[i+1] = *data;
		data++;
	}

	SpiCom.TxData.len = len+1;
	if(SpiCom.Status.B.TXSuc==1)
	{
		HAL_USCIB1_Transmit();

	}
	CS_H;
	LCD_data;
}

void Driver_LCD_Init(void)               //LCD Initialisieren
{
	LCD_RESET_L;
	__delay_cycles(100000);
	LCD_RESET_H;
	Driver_LCD_WriteCommand(&Init2Arr[0], 9);

	__delay_cycles(100000);

	Driver_LCD_Clear();

}

void Driver_LCD_Clear(void)  //LCD Clearen
{

	LCD_data;
	int c_p=0;
	unsigned char column = 0;
	unsigned char clearArr[5] = {DISPLAY_line_start,DISPLAY_Page,DISPLAY_col_msb,DISPLAY_col_lsb};

	Driver_LCD_WriteCommand(&clearArr[0],4);
	LCD_data;
	CS_L;
	SpiCom.TxData.len=0x83;
	HAL_USCIB1_Transmit();
	CS_H;
	while (c_p <= 7)
	{
			if(SpiCom.Status.B.TXSuc==1)
			{
				c_p++;
				clearArr[1]=DISPLAY_Page+c_p;
				Driver_LCD_WriteCommand(&clearArr[1],3);
				CS_L;
				LCD_data;
				//SpiCom.TxData.Data[2]=0xFF;
				SpiCom.TxData.len=0x83;
				HAL_USCIB1_Transmit();
				CS_H;
			}

	}

	Driver_LCD_WriteCommand(&clearArr[4],1);
	CS_H;
}



void Driver_LCD_Clearpage(unsigned char page)  //Page Clearen
{

	LCD_data;
	unsigned char clearArr[5] = {DISPLAY_line_start,DISPLAY_Page,DISPLAY_col_msb,DISPLAY_col_lsb};
	clearArr[1]=DISPLAY_Page | page;
	Driver_LCD_WriteCommand(&clearArr[0],4);
	LCD_data;
	CS_L;
	SpiCom.TxData.len=0x83;
	if(SpiCom.Status.B.TXSuc==1)
	{

	HAL_USCIB1_Transmit();
	CS_H;
	}
}


void Driver_LCD_Clearspace(unsigned char page, unsigned char col, unsigned char length)  //Space Clearen
{

	unsigned char i,j;

	Driver_LCD_SetPosition(page, col);
	LCD_data;

	SpiCom.TxData.len=length;

	for(i= 0; i< length; i++)
	{

			SpiCom.TxData.Data[i] = 0x0;
	}

	CS_L;
	if(SpiCom.Status.B.TXSuc==1)
	{

	CS_L;
	HAL_USCIB1_Transmit();
	CS_H;
	}

}



void Driver_LCD_SetPosition(unsigned char page, unsigned char col)   //Set Position
{
	unsigned char set[3];
  set[0] = DISPLAY_Page + page;
  set[1]= DISPLAY_col_msb + ((col & 0xF0)>>4);
  set[2] = DISPLAY_col_lsb + (col & 0x0F);


  Driver_LCD_WriteCommand(&set[0], 3);
	LCD_data;
	CS_H;

}

void Driver_LCD_WriteString(unsigned char *str, unsigned char len, unsigned char page, unsigned char col)  //Write String
{
	unsigned char i,j;
Driver_LCD_Clearspace(page,col,len*CHAR_WIDTH);
Driver_LCD_SetPosition(page, col);
LCD_data;


SpiCom.TxData.len=len*CHAR_WIDTH;

for(i= 0; i< len; i++)
{
	for(j=0;j<CHAR_WIDTH; j++)
	{
		SpiCom.TxData.Data[i*CHAR_WIDTH+j] = font [*str-32][j];
	}
	str++;
}

if(SpiCom.Status.B.TXSuc==1)
{

	CS_L;
HAL_USCIB1_Transmit();
     CS_H;
}


}

void Driver_LCD_WriteUInt(int num, unsigned char page, unsigned char col)   //Write Unsigned Integer
{
		unsigned char i=0,j,len=0;
		char out[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


		SpiCom.TxData.len = 0;
		itoa(num,out,10);
		while(out[i] != '\0')
		{
			len++;
			i++;
		}
	//	Driver_LCD_Clearspace(page,col,len*CHAR_WIDTH);
		Driver_LCD_SetPosition(page, col);
		LCD_data;
		CS_L;
		SpiCom.TxData.len = 5*CHAR_WIDTH;
		for(i = 0; i < len; i++)
		{
			for(j = 0; j< CHAR_WIDTH; j++)
			{
				SpiCom.TxData.Data[i*6+j] = font[out[i]-32][j];
			}
		}


		if(SpiCom.Status.B.TXSuc==1)
		{

			CS_L;
		HAL_USCIB1_Transmit();
		CS_H;

		}
}


void itoa(unsigned int value, char* result, unsigned char base)    //Standard-fkt
{
  // check that the base if valid
  if (base < 2 || base > 36) { *result = '\0';}

  char* ptr = result, *ptr1 = result, tmp_char;
  int tmp_value;

  do {
	tmp_value = value;
	value /= base;
	*ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) *ptr++ = '-';
  *ptr-- = '\0';
  while(ptr1 < ptr) {
	tmp_char = *ptr;
	*ptr--= *ptr1;
	*ptr1++ = tmp_char;
  }

}
