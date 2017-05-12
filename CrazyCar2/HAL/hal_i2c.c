/*
 * hal_i2c.c
 *
 *  Created on: 28.03.2017
 *      Author: Sebo
 */
#include "..\DL\driver_gyro.h"
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

SlaveData *act_data;
int currentstate;
int nextstate;


void HAL_I2C_Init(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C0));

//SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

GPIOPinConfigure(GPIO_PB2_I2C0SCL);
GPIOPinConfigure(GPIO_PB3_I2C0SDA);

GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, I2C_SCL_MOTION);
GPIOPinTypeI2C(GPIO_PORTB_BASE, I2C_SDA_MOTION);

//SysCtlPeripheralDisable(SYSCTL_PERIPH_I2C0);
//
//SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);



I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(),false);

I2CMasterIntEnableEx(I2C0_BASE,I2C_MASTER_INT_DATA);

IntEnable(INT_I2C0);


}



void GetSlaveData(SlaveData *data)
{
    IntEnable(INT_I2C0);
    act_data=data;
	I2CMasterSlaveAddrSet(I2C0_BASE, data->SlAddr, false); //start writing Reg Addr
	I2CMasterDataPut(I2C0_BASE, data->RAddr);

	if(act_data->lenTX==1 && act_data->READ==false)
	{
	    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
	}
	else
	{
	I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
	}
	if(act_data->lenRX>1)
	{
	    nextstate=WriteRegAd;
	}
	else
	{
	    nextstate=SingleByte;
	}
	I2CMasterIntEnableEx(I2C0_BASE,I2C_MASTER_INT_DATA);
	while(I2CMasterBusy(I2C0_BASE));

}

void SendCommand(Command *data, int numCmd)
{
    IntDisable(INT_I2C0);
    I2CMasterIntDisableEx(I2C0_BASE,I2C_MASTER_INT_DATA);
    int x;
    I2CMasterSlaveAddrSet(I2C0_BASE, data->SlAddr, false); //start writing Reg Addr

    for(x=0;x<=numCmd-1;x++)
    {
        I2CMasterDataPut(I2C0_BASE, data->RAdd[x]);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
        I2CMasterDataPut(I2C0_BASE, data->RData[x]);
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
        while(I2CMasterBusy(I2C0_BASE));

    }
    I2CMasterIntEnableEx(I2C0_BASE,I2C_MASTER_INT_DATA);
}




// Motion InterruptHandler
void
I2CMasterTXHandler(void)
{

	Motion.TxData.TxIntFlag = 1;
}


void
I2CMasterIntHandler(void)
{
    currentstate=nextstate;
    unsigned int MasterIntStatus;
    MasterIntStatus=I2CMasterIntStatusEx(I2C0_BASE, true);
    I2CMasterIntClearEx(I2C0_BASE, MasterIntStatus);

    switch(currentstate){

    case WriteRegAd:
        I2CMasterSlaveAddrSet(I2C0_BASE,act_data->SlAddr,true);
        I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_RECEIVE_START);
        nextstate=Byte1;
    break;
    case Byte1:
        act_data->Datab1=I2CMasterDataGet(I2C0_BASE);
        I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        nextstate=Byte2;
    break;
    case Byte2:
        act_data->Datab2=I2CMasterDataGet(I2C0_BASE);
        act_data->Data=act_data->Datab1<<8 + act_data->Datab2;
    break;

    case SingleByte:
        I2CMasterControl(I2C0_BASE,I2C_MASTER_CMD_SINGLE_RECEIVE);
        act_data->Datab1=I2CMasterDataGet(I2C0_BASE);
    break;

    };

}
