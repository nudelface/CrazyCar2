/*
 * Interrupts.c
 *
 *  Created on: 17.10.2016
 *      Author: Sebastian
 */
#include "Interrupts.h"
#include <stdint.h>
#include <stdbool.h>

#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "hal_timerB0.h"
#include "hal_usc.h"
#include "driverlib/interrupt.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

//#include "hal_gpio.h"
//#include "hal_general.h"
//#include "..\DL\driver_general.h"
//#include "..\DL\driver_aktorik.h"
#include "hal_usciB1.h"
#include "hal_adc12.h"
//#include "..\DL\driver_lcd.h"


ButtonCom Buttons;

int initcounter=0;
//extern USCIB1_SPICom SpiCom;
extern ADC12Com ADC1;
int counterz=0;
//extern int DiskretEn;
int SpeedReady=0;
int SpeedDir=0;
int Timeout=0;
//extern int drive;

double PeriodTime=0;
long PeriodSample=0;
long DirSample=0;
unsigned long PeriodCount=0;
unsigned int lastCount=2000;
unsigned int Count=0;
unsigned long Globalmillis=0;
unsigned long Globaltenmillis=0;
unsigned long Globalsecond=0;
int tenmillisready=0;
int millisready=0;
int secondready=0;

int SpeedSamp=4;

int SampleCounter=0;



int state=0;


void
Timer0BIntHandler(void)
{
TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
Globalmillis++;
PeriodCount++;
if((PeriodCount>=1000/120)&&(ADC1.Status.B.ADCrdy==0))  //120Hz
{
	ADCProcessorTrigger(ADC0_BASE, 0);
	PeriodCount=0;
}
if(Globalmillis>Globaltenmillis*10+10)
{
	Globaltenmillis++;
	tenmillisready=1;
}
if(Globalmillis>Globalsecond*1000+1000)
{
	Globalsecond++;
}

}

/*
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void)
{
	Buttons.active=1;
	if (START_flag>=1)
			{Buttons.button=1;}
	else if (STOP_flag>=1)
			{Buttons.button=2;}


}





#pragma vector=TIMER0_B0_VECTOR
__interrupt void TIMERB_ISR (void)
{

	counterz++;

	//ADC1.Status.B.ADCrdy=0;

	TBCTL |= TBCLR;
	TBEX0 |= TBIDEX__5;										// divide/5
	TBCTL |= MC__UP;

	P1IFG&=~START_Button;
	P1IFG&=~STOP_Button;
}





#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMERA_ISR (void)
{
	if(initcounter<=1000)
	{

	initcounter+=1;
	}

}


#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerA0_ISR (void)
{
	Count=TA0CCR2;
	if(SampleCounter<4)
	{
		PeriodSample=PeriodSample+( Count-lastCount); //Count-lastCount ist Periodendauer in Zählerzahl
		lastCount=Count;
		SampleCounter++;
	}
	else
	{
		DirSample=DIR;

		//if (drive==1)
		//{

		PeriodCount=PeriodSample>>2;
		SpeedReady=1;
		SpeedDir= DirSample;
		Timeout=0;
		PeriodSample=0;
		SampleCounter=0;
				//TA0R=0x0;
		//}
	}
	TA0CCTL2&=~CCIFG; //not suere
	TA0CCTL2&=~COV; //not sure
	TA0CTL |= MC__CONTINUOUS;  //Mode Hochzählen
}





#pragma vector=USCI_B1_VECTOR
__interrupt void USCB_ISR (void)
{

if((UCB1IFG&UCRXIFG)==1)
{
	SpiCom.RXData.Data[SpiCom.TxData.cnt]=UCB1RXBUF;

	SpiCom.TxData.cnt=SpiCom.TxData.cnt+1;

	if(SpiCom.TxData.cnt <= SpiCom.TxData.len-1)
	{

		UCB1TXBUF=SpiCom.TxData.Data[SpiCom.TxData.cnt];
		SpiCom.TxData.Data[SpiCom.TxData.cnt] = 0x0;
		SpiCom.RXData.len=SpiCom.TxData.cnt;
	}
	else
	{
		SpiCom.Status.B.TXSuc=1;
		SpiCom.TxData.cnt=0;
	}
}




}



#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void)
{

	if(DMAIV==0x02)
	{
	DMA0CTL|=DMAEN;
	ADC12CTL0 |= ADC12ENC;
	ADC1.Status.B.ADCrdy=1;
	}
}

*/
