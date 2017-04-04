/*
 * hal_i2c.c
 *
 *  Created on: 28.03.2017
 *      Author: Sebo
 */

#include "hal_i2c.h"

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
#include "hal_gpio.h"

extern i2cCom Motion;



void HAL_I2C_Init(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

GPIOPinConfigure(GPIO_PB2_I2C0SCL);
GPIOPinConfigure(GPIO_PB3_I2C0SDA);

GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, I2C_SCL_MOTION);
GPIOPinTypeI2C(GPIO_PORTB_BASE, I2C_SDA_MOTION);

IntEnable(INT_I2C0);

I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(),true);


}

void HAL_Motion_Init(void)
{
	Motion.Addr=SL_MOTION_ADD;
	Motion.RXData.RxIntFlag=0;
	Motion.TxData.TxIntFlag=0;
}

void GetSlaveData(unsigned char SlaveAdress, unsigned char len, unsigned char *data)
{
	Motion.TxData.TxIntFlag = 0;
	Motion.TxData.Data[0]=59;
	I2CMasterSlaveAddrSet(I2C0_BASE, SlaveAdress+0, true);
	I2CMasterDataPut(I2C0_BASE, Motion.TxData.Data[0]);
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	while(I2CMasterBusy(I2C0_BASE))
	{}




}




// Motion InterruptHandler
void
I2CMasterTXHandler(void)
{
	I2CMasterIntClear(I2C0_BASE);
	Motion.TxData.TxIntFlag = 1;
}


void
I2CMasterIntHandler(void)
{
	I2CMasterIntClear(I2C0_BASE);

	Motion.RXData.Data[0] = I2CMasterDataGet(I2C0_BASE);

	Motion.RXData.RxIntFlag = 1;

}
