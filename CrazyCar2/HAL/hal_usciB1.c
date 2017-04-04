/*
 * hal_usciB1.c
 *
 *  Created on: 07.11.2016
 *      Author: Sebo
 */


#include "hal_usciB1.h"
#include "hal_gpio.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/ssi.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
extern USCIB1_SPICom SpiCom;



void HAL_USCIB1_Init(void)
{


	//GPIOPinConfigure(GPIO_P)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI1);

	GPIOPinConfigure(GPIO_PF2_SSI1CLK);
	GPIOPinConfigure(GPIO_PF1_SSI1TX);

	GPIOPinTypeSSI(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2);
	SSIConfigSetExpClk(SSI1_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_2,SSI_MODE_MASTER,200000,8);
	SSIEnable(SSI1_BASE);
	/*
	UCB1CTL1|=UCSWRST;          //Enabled USCI Logic held in reset state
	UCB1CTL0|=UCCKPL+UCMSB+UCMST+UCSYNC+UCMODE0;  //UCCKPL=Clock Polarity:inactive state is high   UCMSB=MSB Firtst  UCMST=Master Mode   UCSYNC=Synchronous Mode enabled  UCMODE 0 = 3-Pin SPI
	UCB1CTL1|=UCSSEL__SMCLK;    //Clock select:  Source ist SMCLK
	UCB1STAT|=UCLISTEN;      // Loop-Back enable  Transmitted obejct werden Intern an den Receive-Register geschrieben
	UCB1BR0=SCLK_diver;   // Divider = 25
	UCB1IE|=0x1;              //Interrpt Enable
	UCB1CTL1 &= UCSSEL__SMCLK+UCSWRST*0;  //SMCLOCK selected und Wurst auf 0 gesetzt = SPI geht in Operation...also angeschalten
	UCB1IE|=0x1;
	*/

}


void HAL_USCIB1_Transmit(void)
{

	for(SpiCom.TxData.cnt=0; SpiCom.TxData.cnt<=SpiCom.TxData.len-1;SpiCom.TxData.cnt++)
	{

		SSIDataPut(SSI1_BASE, SpiCom.TxData.Data[SpiCom.TxData.cnt]);
		SpiCom.TxData.Data[SpiCom.TxData.cnt] = 0x0;
		SpiCom.RXData.len=SpiCom.TxData.cnt;
	}
    while(SSIBusy(SSI1_BASE))
    {
    }
	SpiCom.Status.B.TXSuc=1;
	SpiCom.TxData.cnt=0;


	/*
	UCB1CTL1 &= ~UCSWRST;  //UsCI aktiv
	UCB1IE |= UCRXIE;     //Interrupt enable
	SpiCom.TxData.cnt=0;   //Init counter of Bytes
	SpiCom.Status.B.TXSuc=0;  //Setzen auf "in sendemodus"
	UCB1TXBUF=SpiCom.TxData.Data[0];  //Transmit starten
	while(SpiCom.Status.B.TXSuc==0); //Bleibt hier stehen bis datenversendet sind

	*/
}
