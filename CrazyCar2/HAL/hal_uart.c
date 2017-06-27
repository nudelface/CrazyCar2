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
extern int initfin;

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
    UARTFIFOEnable(UART1_BASE);
    UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX7_8,UART_FIFO_RX1_8);
    UARTIntRegister(UART1_BASE, UARTIntHandler);
    UARTEnable(UART1_BASE);
    UARTIntEnable(UART1_BASE, UART_INT_RX );



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
    unsigned char trash=0;
    ulStatus=UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, UART_INT_RX | UART_INT_RT);
    //UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT );  ///Edit		1
    if(initfin<2)
    {

    }
    if(((ulStatus == UART_INT_RX)||(ulStatus == (UART_INT_RX+UART_INT_RT)))&&(RxData.RxSucc==0))
    {

        while(UARTCharsAvail(UART1_BASE))
        {
            *Rx=UARTCharGet(UART1_BASE);
            if(initfin<2)
            {
            	Driver_LCD_WriteUInt((unsigned int)*Rx,5,i++*14);
            }
            else
            {
            	//UARTIntDisable(UART1_BASE, UART_INT_RX | UART_INT_RT );
            }
            //Driver_LCD_WriteUInt((unsigned int)*Rx,5,i++*14);
             Rx++;
        }
        RxData.RxSucc=1;
    }
    else if(ulStatus == UART_INT_RT)
    {

        RxData.RxSucc=2;
       // UARTDisable(UART1_BASE);
        //UARTEnable(UART1_BASE);
        UARTIntEnable(UART1_BASE, UART_INT_RX );
        while(UARTCharsAvail(UART1_BASE))
        {
        	trash=UARTCharGet(UART1_BASE);


        }
    }

    //UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT );


}

