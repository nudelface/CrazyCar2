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


void DL_Motion_Init(void)
{
    ACCX.SlAddr=SL_MOTION_ADD;
    ACCX.RAddr=ACCX_H;
}
