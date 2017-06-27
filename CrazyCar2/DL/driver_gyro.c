/*
 * driver_gyro.c
 *
 *  Created on: 06.04.2017
 *      Author: sbo
 */

#include "driver_gyro.h"
#include "..\HAL\hal_i2c.h"
#include "math.h"

#include <stdint.h>
#include <stdbool.h>
SlaveData ACCX;
SlaveData ACCY;
SlaveData ACCZ;
SlaveData GYRX;
SlaveData GYRY, GYRZ;
SlaveData WHOAMI,WHOIAM,ResetMag,GetMode;
SlaveData MagX,ASAX;
SlaveData MagY,ASAY;
SlaveData MagZ,ASAZ;

Command Conf;
Command Reset;
Command Bypass,BypassOff,SetMode;
int init1=0;

double Hx,Hx_f,Hx_last=0;
double Hy,Hy_f,Hy_last=0;
double Hz,Hz_f,Hz_last=0;
float phi;



void DL_Motion_Init(void)
{
    ACCX.SlAddr=SL_MOTION_ADD;
    ACCX.RAddr=ACCX_H;
    ACCX.lenTX=1;
    ACCX.lenRX=2;
    ACCX.READ=true;
    ACCX.multiplier=-0.00012207*9.81;
    ACCX.LSB=2;
    ACCX.offset=0;

    ACCY.SlAddr=SL_MOTION_ADD;
    ACCY.RAddr=ACCY_H;
    ACCY.lenTX=1;
    ACCY.lenRX=2;
    ACCY.READ=true;
    ACCY.multiplier=0.00012207*9.81;
    ACCY.LSB=2;
    ACCY.offset=0;

    ACCZ.SlAddr=SL_MOTION_ADD;
    ACCZ.RAddr=ACCZ_H;
    ACCZ.lenTX=1;
    ACCZ.lenRX=2;
    ACCZ.READ=true;
    ACCZ.multiplier=0.00012207*9.81;
    ACCZ.LSB=2;
    ACCZ.offset=0;

    GYRX.SlAddr=SL_MOTION_ADD;
    GYRX.RAddr=GYRX_H;
    GYRX.lenTX=1;
    GYRX.lenRX=2;
    GYRX.READ=true;
    GYRX.multiplier=0.01525;
    GYRX.LSB=2;

    GYRY.SlAddr=SL_MOTION_ADD;
    GYRY.RAddr=GYRY_H;
    GYRY.lenTX=1;
    GYRY.lenRX=2;
    GYRY.READ=true;
    GYRY.multiplier=0.01525;
    GYRY.LSB=2;

    GYRZ.SlAddr=SL_MOTION_ADD;
    GYRZ.RAddr=GYRZ_H;
    GYRZ.lenTX=1;
    GYRZ.lenRX=2;
    GYRZ.READ=true;
    GYRZ.multiplier=0.01525;
    GYRZ.LSB=2;

    WHOAMI.SlAddr=SL_MOTION_ADD;
    WHOAMI.RAddr=0x75;
    WHOAMI.lenTX=1;
    WHOAMI.lenRX=1;
    WHOAMI.LSB=2;

    WHOIAM.SlAddr=SL_MAG_ADD;
    WHOIAM.RAddr= 00;
    WHOIAM.lenRX=1;
    WHOIAM.LSB=2;
    GetMode.SlAddr=SL_MAG_ADD;
    GetMode.RAddr=0x0A;
    GetMode.lenRX=1;
    GetMode.LSB=2;

    SetMode.SlAddr=SL_MAG_ADD;
    SetMode.RAdd[0]=0x0A;
    SetMode.RData[0]=2;



   Reset.SlAddr=SL_MOTION_ADD;
   Reset.RAdd[0]=0x6B; //PowerManag
   Reset.RData[0]=0x80; //Reset

   Conf.SlAddr=SL_MOTION_ADD;
   Conf.RAdd[0]=0x1D;  //acc Bandwith
   Conf.RData[0]=6;
   Conf.RAdd[1]=0x1C; //ACC sensitivity
   Conf.RData[1]=0x8;
   Conf.RAdd[2]=0x1A; //gyro BW
   Conf.RData[2]=6;
   Conf.RAdd[3]=0x1B;  //Gyyro Sensitivity
   Conf.RData[3]=16;

   Bypass.SlAddr=SL_MOTION_ADD;
   Bypass.RAdd[0]=55;
   Bypass.RData[0]=2;
   BypassOff.SlAddr=SL_MOTION_ADD;
   BypassOff.RAdd[0]=55;
   BypassOff.RData[0]=0;

   MagX.SlAddr=SL_MAG_ADD;
   MagX.RAddr=MagX_L;
   MagX.lenRX=2;
   MagX.multiplier=0.146;
   MagX.LSB=1;

   MagY.SlAddr=SL_MAG_ADD;
   MagY.RAddr=MagY_L;
   MagY.lenRX=2;
   MagY.multiplier=0.146;
   MagY.LSB=1;

  MagZ.SlAddr=SL_MAG_ADD;
  MagZ.RAddr=MagZ_L;
  MagZ.lenRX=2;
  MagZ.multiplier=0.146;
  MagZ.LSB=1;

  ASAX.SlAddr=SL_MAG_ADD;
  ASAX.RAddr=AsaX;
  ASAX.lenRX=1;

  ASAY.SlAddr=SL_MAG_ADD;
  ASAY.RAddr=AsaY;
  ASAY.lenRX=1;

  ASAZ.SlAddr=SL_MAG_ADD;
  ASAZ.RAddr=AsaY;
  ASAZ.lenRX=1;

  ResetMag.SlAddr=SL_MAG_ADD;
  ResetMag.RAddr=ST2;
  ResetMag.lenRX=1;





   SendCommand(&Reset,1);
   GetSlaveData(&WHOAMI);
   SendCommand(&Conf,4);

   GetSlaveData(&ACCX);
   GetSlaveData(&ACCY);
   GetSlaveData(&ACCZ);





}

void GetMagData(void)
{
SendCommand(&Bypass,1);
SysCtlDelay(10000);
////Get slavedata
GetSlaveData(&WHOIAM);
SendCommand(&SetMode,1);
SysCtlDelay(10000);
GetSlaveData(&GetMode);
GetSlaveData(&MagX);
GetSlaveData(&MagY);
GetSlaveData(&MagZ);
GetSlaveData(&ASAX);
GetSlaveData(&ASAY);
GetSlaveData(&ASAZ);
GetSlaveData(&ResetMag);
/// Data neuberechnen
SendCommand(&BypassOff,1);
//SysCtlDelay(10000);

Hx=(double)MagX.Data*(((((double)ASAX.RxData[0]-128)*0.5)/128)+1);
Hy=(double)MagY.Data*(((((double)ASAY.RxData[0]-128)*0.5)/128)+1);
Hz=(double)MagZ.Data*(((((double)ASAZ.RxData[0]-128)*0.5)/128)+1);
if((Hy>(Hy_last+Hy_last*0.1))&&init1>=5)
{
    Hy_f=Hy_last+Hy_last*0.1;
    Hy_last=Hy_f;
   }
else if((Hy<(Hy_last-Hy_last*0.1))&&init1>=5)
{
    Hy_f=Hy_last-Hy_last*0.1;
    Hy_last=Hy_f;
    }
else
{
Hy_f=Hy;
Hy_last=Hy_f;
if(init1>10)
{init1++;}
}

if((Hx>(Hx_last+Hx_last*0.1))&&init1>=5)
{
    Hx_f=Hx_last+Hx_last*0.1;
    Hx_last=Hx_f;
   }
else if((Hx<(Hx_last-Hx_last*0.1))&&init1>=5)
{
    Hx_f=Hx_last-Hx_last*0.1;
    Hx_last=Hx_f;
    }
else
{
Hx_f=Hx;
Hx_last=Hx_f;

}

if((Hz>(Hz_last+Hz_last*0.1))&&init1>=5)
{
    Hz_f=Hz_last+Hz_last*0.1;
    Hz_last=Hz_f;
   }
else if((Hz<(Hz_last-Hz_last*0.1))&&init1>=5)
{
    Hz_f=Hz_last-Hz_last*0.1;
    Hz_last=Hz_f;
    }
else
{
Hz_f=Hz;
Hz_last=Hz_f;

}




phi=((-atan2((float)Hx,(float)Hy))/(6.2831))*360;


}
