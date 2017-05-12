/*
 * driver_RF.c
 *
 *  Created on: 26.04.2017
 *      Author: sbo
 */

#include "driver_RF.h"
#include "..\HAL\hal_uart.h"
#include "driver_lcd.h"

#include <stdint.h>
#include <stdbool.h>
#include "driver_aktorik.h"

RFCommand Init;
Test Tester;

extern RFRX RxData;
RFRX SensData;




void RF_Init (void)
{
    Init.Commandbyte=WRITE_COMMAND;
    Init.Command=WRITE_NODE_ADD;
    Init.CommandData=NodeAdress;
    TxData(&Init,3);

    Init.Command=READ_NODE_ADD;
    TxData(&Init,2);
    while(!RxData.RxSucc){}

    if(RxData.NodeAddr==NodeAdress)
    {
        Driver_LCD_WriteString("NodeAdressSucces",16,2,0);
        RxData.RxSucc=0;
    }
    else
    {
        Driver_LCD_WriteString("NodeAddrFail",12,2,0);
    }
    Init.Command=WRITE_RF_CHANNEL;
    Init.CommandData=CHANNEL;

    TxData(&Init,3);

    Init.Command=READ_RF_CHANNEL;
    TxData(&Init,2);
    while(!RxData.RxSucc){};
    if(RxData.NodeAddr==CHANNEL)
    {
        Driver_LCD_WriteString("ChannelSucces",13,3,0);
    }
    else
    {
        Driver_LCD_WriteString("ChannelFail",11,3,0);
    }

   Tester.Commandbyte=WRITE_COMMAND;
   Tester.Command=READ_WRITE_DATA;
   Tester.DestAdress=HostAdress;
   Tester.len=0x02;
   Tester.Data[1]=0x23;
   Tester.Data[0]=0x11;

   TxData(&Tester,Tester.len+4);

   SensData.Commandbyte=WRITE_COMMAND;
   SensData.Command=READ_WRITE_DATA;
   SensData.NodeAddr=HostAdress;
   SensData.len=4;
   SensData.Data[0]=3; ///DATASens1
   SensData.Data[1]=4; // Data2
   SensData.Data[2]=5; //DataSens2
   SensData.Data[3]=0xA; // Data3


}


void RxStuff(void)
{
    if(RxData.len>=2)
    {
    switch(RxData.Data[0])
    {
        case 0:
            if(RxData.Data[1]==1)
            {
                Driver_SetSteering(-RxData.Data[2]);
            }
            else
            {
                Driver_SetSteering(RxData.Data[2]);
            }
        break;
        case 1:
            if(RxData.Data[1]==1)
            {
                Driver_SetBack(RxData.Data[2]);
            }
            else
            {
                Driver_SetThrottle(RxData.Data[2]);
            }
        break;
        case 3:
                SendSensorData();
        break;


    }
    }

}



void SendSensorData(void)
{
    TxData(&SensData,SensData.len+4);
}
