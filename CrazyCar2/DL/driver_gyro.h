/*
 * driver_gyro.h
 *
 *  Created on: 06.04.2017
 *      Author: sbo
 */

#ifndef DL_DRIVER_GYRO_H_
#define DL_DRIVER_GYRO_H_

void DL_Motion_Init(void);




#define SL_MOTION_ADD 0x68

#define ACCX_H 0x59
#define ACCX_L 0x60
#define ACCY_H 0x61
#define ACCY_L 0x62
#define ACCZ_H 0x63
#define ACCZ_L 0x64

#define TOut_H 0x65
#define TOut_L 0x66

#define GYRX_H 0x67
#define GYRX_L 0x68
#define GYRY_H 0x69
#define GYRY_L 0x70
#define GYRZ_H 0x71
#define GYRZ_L 0x72


#endif /* DL_DRIVER_GYRO_H_ */
