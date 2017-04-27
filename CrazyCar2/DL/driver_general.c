/*
 * driver_general.c
 *
 *  Created on: 31. Okt. 2016
 *      Author: KlotzSeb
 */

#include "..\HAL\hal_timerA1.h"
#include "..\HAL\hal_usc.h"
#include "driver_aktorik.h"
#include "driver_lcd.h"
#include "driver_gyro.h"
#include "driver_RF.h"




void Driver_Init(void)
{
	Driver_LCD_Init();      //LCD Initialisieren
	Driver_SetSteering(0);  //Steering initialisieren
    Driver_ESCInit();       // ESC Initialisieren
    DL_Motion_Init();
    RF_Init();
}
