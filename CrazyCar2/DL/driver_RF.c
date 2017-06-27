/*
 * driver_RF.c
 *
 *  Created on: 26.04.2017
 *      Author: sbo
 */

#include "driver_RF.h"
#include "..\HAL\hal_uart.h"
#include "driver_lcd.h"
#include "..\HAL\hal_i2c.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "driver_aktorik.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
int mux=0;

RFCommand Init;
Test Tester;
extern SlaveData ACCX, ACCY, ACCZ,GYRX, GYRY, GYRZ,MagX,MagY,MagZ;
extern RFRX RxData;
RFRX SensData;
int initfin=0;

extern float acc_speed_x;
extern float acc_speed_x_last;
extern float dt;
extern float t_last;
extern float acc_dist_x;
//extern float acc_dist_y;
extern float acc_dist_x_last;
extern int steer_global;
extern int throttle_global;

extern unsigned int Abstand1;
extern unsigned int Abstand2;
extern unsigned int Abstand3;
extern unsigned int Abstand4;

extern double Hx;
extern double Hy;
extern double Hz;

extern float phi;

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

   UARTFIFOLevelSet(UART1_BASE, UART_FIFO_TX7_8,UART_FIFO_RX4_8);
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
   initfin=3;

}


void RxStuff(void)
{
	if(RxData.Command==0xFE)
	{
	    switch(RxData.NodeAddr)
	    {
	        case 1:
	        	Driver_LCD_WriteString("Wrong Format",13,6,0);
	        break;
	        case 2:
	        	Driver_LCD_WriteString("Fail",4,6,0);
	        break;
	        case 3:
	        	Driver_LCD_WriteString("Fail",4,6,0);
	        break;
	        case 6:
	        	Driver_LCD_WriteString("ByteCount and Payload not match",40,6,0);
	        break;
	        default:
	        	Driver_LCD_WriteString("Fail",4,6,0);
	        break;


	    }
	}
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
    UARTIntEnable(UART1_BASE, UART_INT_RX );
}



void SendSensorData(void)
{
	   SensData.Commandbyte=WRITE_COMMAND;
	   SensData.Command=READ_WRITE_DATA;
	   SensData.NodeAddr=HostAdress;
	   SensData.len=4;
	   SensData.Data[0]=mux;

	   switch(mux)
	   {
		   case 0:

			   SensData.Data[1]=(int)ACCX.value*7; // Data2
			   SensData.Data[2]=(int)ACCY.value*7; //DataSens2  //Vx
			   SensData.Data[3]=(int)acc_speed_x; // Data3     //Vy
		   break;

	   	   case 1:

			   SensData.Data[1]=(int)(acc_dist_x/256); //Dist2
			   SensData.Data[2]=(int)(acc_dist_x)&(0xFF00);//(int)acc_dist_y; //Dist3
			   SensData.Data[3]=(int)acc_speed_x; //Dist4
		   break;
	   	   case 2:

			   SensData.Data[1]=steer_global; //Mag
			   SensData.Data[2]=throttle_global; //Gyr
			   SensData.Data[3]=Abstand1; //cm
		   break;
	   	   case 4:
			   SensData.Data[1]=Abstand2; //cm
			   SensData.Data[2]=Abstand3; //
			   SensData.Data[3]=Abstand4; //
	   	   break;

	   	   case 5:
			   SensData.Data[1]=(int)Hx; //nT
			   SensData.Data[2]=(int)Hy; //
			   SensData.Data[3]=(int)Hz; //
		   break;

	   	   case 6:
			   SensData.Data[1]=(int)phi; //Grad
			   SensData.Data[2]=(int)GYRZ.millivalue; //dps
			   SensData.Data[3]=(int)GYRY.millivalue; //
			break;

	   	   case 7:
			   SensData.Data[1]=11; //Grad
			   SensData.Data[2]=11; //dps
			   SensData.Data[3]=11; //
	   	   break;

	   }
    TxData(&SensData,8);
    if(mux<2)
    {
    mux++;
    }
    else
    {mux=0;}
}
