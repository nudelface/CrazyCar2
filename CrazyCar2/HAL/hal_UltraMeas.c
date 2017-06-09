/*
 * hal_UltraMeas.c
 *
 *  Created on: 31.05.2017
 *      Author: sbo
 */

#include "hal_UltraMeas.h"
#include "hal_timerA1.h"
#include "hal_gpio.h"
#include "hal_usc.h"
#include <stdint.h>
#include <stdbool.h>
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "inc/hw_types.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"

uint16_t CountUs1;
uint16_t CountUs11;
uint16_t CountUs2;
uint16_t Time1;
float DistUs1;
float DistUs1mem[4];
float DistUs2;
int busy=1;
int i;
int TimeoutBusy;


void initUltraMeas(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2))
    {}

    GPIOPinConfigure(GPIO_PB0_T2CCP0);
    GPIOPinTypeTimer(GPIO_PORTB_BASE, US1_SIGNAL_OUT|US2_SIGNAL_OUT);
    TimerClockSourceSet(TIMER2_BASE, TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_CAP_TIME);
    TimerPrescaleSet(TIMER2_BASE,TIMER_BOTH,20);
    IntMasterEnable();
    IntEnable(INT_TIMER2A);


    TimerControlEvent(TIMER2_BASE, TIMER_A, TIMER_EVENT_POS_EDGE);


    TimerIntRegister(TIMER2_BASE, TIMER_A, TimerInt);
    TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);
    TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);

    TimerLoadSet(TIMER2_BASE, TIMER_A,65535);

    TimerEnable(TIMER2_BASE, TIMER_A | TIMER_B);



}


float MeasDist(void)
{
	if(busy==1)
	{
	busy=0;
	//start PWM
	//TimerLoadSet(TIMER2_BASE, TIMER_A,0);

    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    CountUs11=TimerValueGet(TIMER2_BASE, TIMER_A);
	//STart Timer
   // SysCtlDelay(22000);
    for(i=0;i<=1500;i++)
    {}
    //TimerEnable(TIMER2_BASE, TIMER_A);
    TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);
    TimerIntEnable(TIMER2_BASE, TIMER_CAPA_EVENT);

    //TimerEnable(TIMER2_BASE, TIMER_A);
	//while !busy
    TimeoutBusy=0;
    while(!busy)
    {
    	TimeoutBusy++;
    	if(TimeoutBusy>100000)
    	{
    		busy=1;
    		TimerIntDisable(TIMER2_BASE, TIMER_CAPA_EVENT);

    		//TimerDisable(TIMER2_BASE, TIMER_A | TIMER_B);
    		TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);
    	}
    }

	//Calc Werte
	//Return Werte
	}

	if(TimeoutBusy<100000)
	{
	DistUs1mem[3]=DistUs1mem[2];
	DistUs1mem[2]=DistUs1mem[1];
	DistUs1mem[1]=DistUs1mem[0];
	DistUs1mem[0]=(343*((float)Time1/(2*5000000)))*100; //cm
	DistUs1=(DistUs1mem[1]+DistUs1mem[0]+DistUs1mem[2]+DistUs1mem[3])/4;
	GPIOPinWrite(GPIO_PORTA_BASE, LCD_BL, ~LCD_BL);
	}

	return DistUs1;

}

void TimerInt(void)
{
	CountUs1=TimerValueGet(TIMER2_BASE, TIMER_A);
	TimerIntDisable(TIMER2_BASE, TIMER_CAPA_EVENT);
	GPIOPinWrite(GPIO_PORTA_BASE, LCD_BL, LCD_BL);
	//TimerDisable(TIMER2_BASE, TIMER_A | TIMER_B);
	TimerIntClear(TIMER2_BASE, TIMER_CAPA_EVENT);



	Time1=CountUs11-CountUs1;
//	TimerLoadSet(TIMER2_BASE, TIMER_A,0);
	//TimerDisable(TIMER2_BASE, TIMER_A);
	TimerIntDisable(TIMER2_BASE, TIMER_CAPA_EVENT);
	busy=1;
}



