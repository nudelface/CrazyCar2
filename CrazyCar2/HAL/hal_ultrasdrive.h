/*
 * hal_ultrasdrive.h
 *
 *  Created on: 31.05.2017
 *      Author: sbo
 */

#ifndef HAL_HAL_ULTRASDRIVE_H_
#define HAL_HAL_ULTRASDRIVE_H_

#define Fr_divider_B (SMCLK_FREQU/40000)  //60 Hz
void UltrasonicDriverInit(void);
void PWM_INT_HANDLER(void);

#endif /* HAL_HAL_ULTRASDRIVE_H_ */
