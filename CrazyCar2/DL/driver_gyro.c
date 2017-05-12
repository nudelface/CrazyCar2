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
SlaveData WHOAMI;

Command Conf;
Command Reset;


void DL_Motion_Init(void)
{
    ACCX.SlAddr=SL_MOTION_ADD;
    ACCX.RAddr=ACCX_H;
    ACCX.lenTX=1;
    ACCX.lenRX=2;
    ACCX.READ=true;

    WHOAMI.SlAddr=SL_MOTION_ADD;
    WHOAMI.RAddr=0xB1;
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


   SendCommand(&Reset,1);
   GetSlaveData(&WHOAMI);
   SendCommand(&Conf,4);


}
