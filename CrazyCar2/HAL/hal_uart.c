/*
 * hal_uart.c
 *
 *  Created on: 26.04.2017
 *      Author: sbo
 */
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_usc.h"

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_i2c.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/uart.h"

extern int initcounter;
int initfin=0;

RFRX RxData;

void hal_uart_init(void)
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART1))
    {
    }

    GPIOPinConfigure(GPIO_PC4_U1RX);
    GPIOPinConfigure(GPIO_PC5_U1TX);

    GPIOPinTypeUART(GPIO_PORTC_BASE, (GPIO_PIN_4 | GPIO_PIN_5));

    UARTConfigSetExpClk(UART1_BASE, SysCtlClockGet(),Baud, (UART_CONFIG_WLEN_8| UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));

    UARTIntRegister(UART1_BASE, UARTIntHandler);
    UARTEnable(UART1_BASE);
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);



}
void TxData(unsigned char *Tx_data,unsigned char len)
{
    int x=1;
    while(UARTBusy(UART1_BASE)){}
    while(x<=len)
    {
        UARTCharPut(UART1_BASE, *Tx_data);
        while(UARTBusy(UART1_BASE)){}
        x++;
        Tx_data++;
    }
    while(UARTBusy(UART1_BASE)){}
    SysCtlDelay(2000000);

}


void UARTIntHandler(void)
{
    int i=0;
    unsigned long ulStatus;
    unsigned char *Rx = &RxData;
    ulStatus=UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ulStatus);
    if(ulStatus && UART_INT_RX)
    {
        while(UARTCharsAvail(UART1_BASE))
        {
            *Rx=UARTCharGet(UART1_BASE);
            Driver_LCD_WriteUInt((unsigned int)*Rx,5,i++*14);
             Rx++;
        }
        RxData.RxSucc=1;
    }
    else if(ulStatus && UART_INT_RT)
    {

        RxData.RxSucc=2;
    }

    initfin=1;

}

