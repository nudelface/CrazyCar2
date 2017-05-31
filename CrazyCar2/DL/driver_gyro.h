/*
 * driver_gyro.h
 *
 *  Created on: 06.04.2017
 *      Author: sbo
 */

#ifndef DL_DRIVER_GYRO_H_
#define DL_DRIVER_GYRO_H_

void DL_Motion_Init(void);

void GetMagData(void);


#define SL_MOTION_ADD 0x68
#define SL_MAG_ADD 0x0C
#define ACCX_H 59
#define ACCX_L 60
#define ACCY_H 61
#define ACCY_L 62
#define ACCZ_H 63
#define ACCZ_L 64


#define TOut_H 65
#define TOut_L 66

#define GYRX_H 67
#define GYRX_L 68
#define GYRY_H 69
#define GYRY_L 70
#define GYRZ_H 71
#define GYRZ_L 72

#define MagX_L 0x03
#define MagY_L 0x05
#define MagZ_L 0x07
#define ST2 0x09

#define AsaX 0x10
#define AsaY 0x11
#define AsaZ 0x12


#endif /* DL_DRIVER_GYRO_H_ */
