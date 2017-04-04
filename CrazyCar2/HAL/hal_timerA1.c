/*
 * hal_timerA1.c
 *
 *  Created on: 31. Okt. 2016
 *      Author: KlotzSeb
 */

//#include <msp430.h>
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
extern int initcounter;

#include "driverlib/sysctl.h"
extern void PWM1IntHandler(void);

uint32_t Period, dCThrottle, dCSteering;




void HAL_TimerA1_Init()
{


	//GPIOPinConfigure(GPIO_PA6_T1CCP0);  //Pin A6 (Steering auf CCP1 des Timer1)
	//GPIOPinConfigure(GPIO_PA7_T1CCP1);  //PinA7 (throttle auf CCP2 des Timers1)
	//GPIOPinTypeTimer(GPIO_PORTA_BASE, Steering);
	//GPIOPinTypeTimer(GPIO_PORTA_BASE, Throttle);

	//Period=SysCtlClockGet()/PWM_freq;  //60Hz
	dCThrottle = 0;
	dCSteering = Period/2;
	IntMasterEnable();
	SysCtlPWMClockSet(SYSCTL_PWMDIV_8);  //Enable pwm Clock
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);


	GPIOPinConfigure(GPIO_PA6_M1PWM2);
	GPIOPinConfigure(GPIO_PA7_M1PWM3);
	GPIOPinTypePWM(GPIO_PORTA_BASE, Steering);
	GPIOPinTypePWM(GPIO_PORTA_BASE, Throttle);





	PWMGenConfigure(PWM1_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure(PWM1_BASE,PWM_GEN_1, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, Fr_divider_A);
	PWMGenPeriodSet(PWM1_BASE, PWM_GEN_1, Fr_divider_A);

	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_2, 3590);
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_3, 2500);

	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT, true);
	PWMOutputState(PWM1_BASE, PWM_OUT_3_BIT, true);

	PWMGenEnable(PWM1_BASE, PWM_GEN_1);
	PWMGenEnable(PWM1_BASE, PWM_GEN_1);

	PWMOutputState(PWM1_BASE, PWM_OUT_2_BIT | PWM_OUT_3_BIT, true);

	PWMGenIntTrigEnable(PWM1_BASE, PWM_GEN_1, PWM_INT_CNT_ZERO);
	PWMGenIntRegister(PWM1_BASE, PWM_GEN_1, PWM1IntHandler);

	PWMIntEnable(PWM1_BASE, PWM_INT_GEN_1);


	IntEnable(INT_PWM1_1);
	IntEnable(INT_PWM1_3);
	IntPrioritySet(INT_PWM1_1, 0x00);



	//SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
	//SysCtlDelay(3);
	//TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM);
	//TimerLoadSet(TIMER1_BASE, TIMER_B, Period-1);
	//TimerMatchSet(TIMER1_BASE, TIMER_B, dCThrottle);


  /*
	TA1CTL |= TBSSEL__SMCLK+ID_0+MC__STOP;  	//SEL_SMCLKK=Clock ist SMCLOCK    MC_STOP=Mode ist Stop
	TA1CCTL0 |= CM_0+CCIS_0+SCS+OUTMOD_0+CCIE;		//CM=Capture mode:No Capture     CCIS=Capt/compare Inpt select ist   SCS=Syncron Capture  OUTMOD_0=Out BIT-Value   CCIE=Interrupt enable
	TA1CCTL1 |= CM_0+CCIS_0+SCS+OUTMOD_7;      //Throttle 7  Outmod: Reset/Set  für PWM
	TA1CCTL2 |= CM_0+CCIS_0+SCS+OUTMOD_7;      //Steering   Outmod: Reset/Set  für PWM

	TA1R = 0x0;   //Init Register Zähler
	TA1CCR0 = Fr_divider_A; //0x3D09;  //-1 weil der 0te wert dazugehört   Divider siehe h-file
	TA1CCR1= 2500;  //CC Regeister Throttle
	TA1CCR2= 3590;  //CC Register Steering

	TA1CTL |=TACLR;//clear
	TA1CTL |= MC__UP;  //Mode Hochzählen
   */
}
