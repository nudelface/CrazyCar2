/*
 * hal_timerB0.h
 *
 *  Created on: 25. Okt. 2016
 *      Author: Niki
 */

#ifndef HAL_HAL_TIMERB0_H_
#define HAL_HAL_TIMERB0_H_



void HAL_TimerB0_Init(void);

#define Timerval SysCtlClockGet()/1000

//#define Fr_divider_B  ((SMCLK_FREQU / 8 / 5)  +1)     // Hardware dividiert SMCLK Durch 8, dann durch 5..Das ist die Timer Clock. Timer Click durch zielfrequenz ergibt z�hlwert //fr ergibt 4hz,bl umschalten dividiert durch 2 zu 2hz
//#define Fr_divider_B1  Fr_divider_B / 60


#endif /* HAL_HAL_TIMERB0_H_ */
