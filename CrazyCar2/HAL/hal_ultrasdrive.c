/*
 * hal_ultrasdrive.c
 *
 *  Created on: 31.05.2017
 *      Author: sbo
 */

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
#include "hal_ultrasdrive.h"
#include "driverlib/interrupt.h"


#include "driverlib/sysctl.h"
int pwmcounter=0;


void UltrasonicDriverInit(void)
{
    IntMasterEnable();
    SysCtlPWMClockSet(SYSCTL_PWMDIV_8);  //Enable pwm Clock
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    GPIOPinConfigure(GPIO_PE4_M0PWM4);
    GPIOPinConfigure(GPIO_PE5_M0PWM5);
    GPIOPinTypePWM(GPIO_PORTE_BASE, US2_SIGNAL_IN);
    GPIOPinTypePWM(GPIO_PORTE_BASE, US1_SIGNAL_IN);  //Setze Frequenzausgänge

    PWMGenConfigure(PWM0_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
   // PWMGenConfigure(PWM0_BASE,PWM_GEN_2, PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, Fr_divider_B);
    //PWMGenPeriodSet(PWM0_BASE, PWM_GEN_2, Fr_divider_B);

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_4, Fr_divider_B/2);
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_5, Fr_divider_B/2);

    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);

    PWMGenEnable(PWM0_BASE, PWM_GEN_2);
    PWMGenEnable(PWM0_BASE, PWM_GEN_2);

    PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT | PWM_OUT_5_BIT, true);

    PWMIntEnable(PWM0_BASE, PWM_INT_GEN_2);
    PWMGenIntTrigEnable(PWM0_BASE, PWM_GEN_2, PWM_INT_CNT_ZERO);

	PWMGenIntRegister(PWM0_BASE, PWM_GEN_2, PWM_INT_HANDLER);

	PWMIntEnable(PWM0_BASE, PWM_INT_GEN_2);


	IntEnable(INT_PWM0_2);

	//IntPrioritySet(INT_PWM1_1, 0x00);
    GPIOPinWrite(GPIO_PORTA_BASE, US2_DRIVER_EN, US2_DRIVER_EN);
    GPIOPinWrite(GPIO_PORTD_BASE, US1_DRIVER_EN, US1_DRIVER_EN);



}

void PWM_INT_HANDLER(void)
{

	PWMGenIntClear(PWM0_BASE, PWM_GEN_2, PWM_INT_CNT_ZERO);
	pwmcounter++;
	if(pwmcounter>=10)
	{

		   PWMGenDisable(PWM0_BASE, PWM_GEN_2);
		    PWMGenDisable(PWM0_BASE, PWM_GEN_2);
		    pwmcounter=0;
	}
}
