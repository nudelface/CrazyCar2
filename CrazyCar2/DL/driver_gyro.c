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
SlaveData WHOAMI;

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

    ACCY.SlAddr=SL_MOTION_ADD;
    ACCY.RAddr=ACCY_H;
    ACCY.lenTX=1;
    ACCY.lenRX=2;
    ACCY.READ=true;
    ACCY.multiplier=0.00012207;

    ACCZ.SlAddr=SL_MOTION_ADD;
    ACCZ.RAddr=ACCZ_H;
    ACCZ.lenTX=1;
    ACCZ.lenRX=2;
    ACCZ.READ=true;
    ACCZ.multiplier=0.00012207;

    GYRX.SlAddr=SL_MOTION_ADD;
    GYRX.RAddr=GYRX_H;
    GYRX.lenTX=1;
    GYRX.lenRX=2;
    GYRX.READ=true;
    GYRX.multiplier=0.01525;

    GYRY.SlAddr=SL_MOTION_ADD;
    GYRY.RAddr=GYRY_H;
    GYRY.lenTX=1;
    GYRY.lenRX=2;
    GYRY.READ=true;
    GYRY.multiplier=0.01525;

    GYRZ.SlAddr=SL_MOTION_ADD;
    GYRZ.RAddr=GYRY_H;
    GYRZ.lenTX=1;
    GYRZ.lenRX=2;
    GYRZ.READ=true;
    GYRZ.multiplier=0.01525;

    WHOAMI.SlAddr=SL_MOTION_ADD;
    WHOAMI.RAddr=0x75;
    WHOAMI.lenTX=1;
    WHOAMI.lenRX=1;

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



   SendCommand(&Reset,1);
   GetSlaveData(&WHOAMI);
   SendCommand(&Conf,4);


}

void GetMagData(void)
{
SendCommand(&Bypass,1);
////Get slavedata

/// Data neuberechnen
SendCommand(&BypassOff,1);

}
