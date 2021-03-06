/*
 * hal_general.c
 *
 *  Created on: 10. Okt. 2016
 *      Author: KlotzSeb
 */
//#include "hal_wdt.h"
//#include "hal_pmm.h"
#include "hal_general.h"
#include "interrupts.h"
#include "hal_usc.h"
#include "hal_timerB0.h"
#include "hal_timerA1.h"
#include "hal_gpio.h"
#include "hal_usciB1.h"
#include "hal_i2c.h"
//#include "hal_adc12.h"
//#include "hal_dma.h"
#include "hal_usc.h"
#include "hal_uart.h"
//#include "hal_timerA0.h"
#include "hal_ultrasdrive.h"

USCIB1_SPICom SpiCom;
i2cCom Motion;




void HAL_Init(void)
{


	HAL_GPIO_Init();
	//HAL_PMM_Init ();
	HAL_I2C_Init();
	HAL_UCS_Init();
	HAL_TimerB0_Init();
    HAL_TimerA1_Init();
    HAL_USCIB1_Init();
    HAL_USCIB1_Transmit();
    UltrasonicDriverInit();
	hal_uart_init();
	initUltraMeas();
	HAL_Adc_init();

	//HAL_Wdt_Init();
	//HAL_Adc_init();
   // HAL_DMA_Init();
    //HAL_TimerA0_Init();*/

}

