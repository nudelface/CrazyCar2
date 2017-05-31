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


void initUltraMeas(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2))
    {}


    TimerClockSourceSet(TIMER0_BASE, TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_B_PERIODIC);

    //TimerLoadSet(TIMER0_BASE, TIMER_B,Timerval);


    IntMasterEnable();
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntEnable(INT_TIMER0A);
    TimerEnable(TIMER0_BASE, TIMER_A);
}

