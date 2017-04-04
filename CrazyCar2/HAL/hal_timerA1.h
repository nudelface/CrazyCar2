/*
 * hal_timerA1.h
 *
 *  Created on: 31. Okt. 2016
 *      Author: KlotzSeb
 */

#ifndef HAL_HAL_TIMERA1_H_
#define HAL_HAL_TIMERA1_H_

void HAL_TimerA1_Init(void);

#define Fr_divider_A (SMCLK_FREQU/60)  //60 Hz
#define PWM_freq 60
#define Max_Left 3030
#define Max_Right 4150
#define Middle 3590

#define PwmSteer PWM_OUT_2
#define PwmThrot PWM_OUT_3
//void PWM1IntHandler(void);



#endif /* HAL_HAL_TIMERA1_H_ */
