/*
 * driver_gyro.c
 *
 *  Created on: 06.04.2017
 *      Author: sbo
 */

#include "driver_gyro.h"
#include "..\HAL\hal_i2c.h"

#include <stdint.h>
#include <stdbool.h>
SlaveData ACCX;
SlaveData ACCY;
SlaveData ACCZ;
SlaveData GYRX;
SlaveData GYRY, GYRZ;
SlaveData WHOAMI,WHOIAM;
SlaveData MagX;
SlaveData MagY;
SlaveData MagZ;

Command Conf;
Command Reset;
Command Bypass,BypassOff;


void DL_Motion_Init(void)
{
    ACCX.SlAddr=SL_MOTION_ADD;
    ACCX.RAddr=ACCX_H;
    ACCX.lenTX=1;
    ACCX.lenRX=2;
    ACCX.READ=true;
    ACCX.multiplier=0.00012207;
    ACCX.LSB=2;

    ACCY.SlAddr=SL_MOTION_ADD;
    ACCY.RAddr=ACCY_H;
    ACCY.lenTX=1;
    ACCY.lenRX=2;
    ACCY.READ=true;
    ACCY.multiplier=0.00012207;
    ACCY.LSB=2;

    ACCZ.SlAddr=SL_MOTION_ADD;
    ACCZ.RAddr=ACCZ_H;
    ACCZ.lenTX=1;
    ACCZ.lenRX=2;
    ACCZ.READ=true;
    ACCZ.multiplier=0.00012207;
    ACCZ.LSB=2;

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

  /* MagX.SlAddr=SL_MAG_ADD;
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
  MagZ.LSB=1;*/





   SendCommand(&Reset,1);
   GetSlaveData(&WHOAMI);
   SendCommand(&Conf,4);


}

void GetMagData(void)
{
SendCommand(&Bypass,1);
//SysCtlDelay(1000);
////Get slavedata
GetSlaveData(&WHOIAM);
GetSlaveData(&MagX);
GetSlaveData(&MagY);
GetSlaveData(&MagZ);
/// Data neuberechnen
SendCommand(&BypassOff,1);
//SysCtlDelay(10000);

}
