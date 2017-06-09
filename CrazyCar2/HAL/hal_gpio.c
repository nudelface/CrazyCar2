/*
 * hal_gpio.c
 *
 *  Created on: 10. Okt. 2016
 *      Author: KlotzSeb
 */

#include "hal_gpio.h"
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"




void HAL_GPIO_Init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    {
    }

	// PortA

	GPIODirModeSet(GPIO_PORTA_BASE, LCD_BL, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIO_PORTA_BASE, LCD_DATACMD, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIO_PORTA_BASE, US2_DRIVER_EN, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIO_PORTA_BASE, Steering, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTA_BASE, Throttle, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTA_BASE, LCD_RESET, GPIO_DIR_MODE_HW);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_BL);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_DATACMD);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, US2_DRIVER_EN);
	GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, LCD_RESET);
//	GPIOPadConfigSet(GPIO_PORTA_BASE, LCD_BL, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
//	GPIOPadConfigSet(GPIO_PORTA_BASE, LCD_DATACMD, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);
//	GPIOPadConfigSet(GPIO_PORTA_BASE, LCD_RESET, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);

	// POrtB


	GPIODirModeSet(GPIO_PORTB_BASE, I2C_SCL_MOTION, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTB_BASE, I2C_SDA_MOTION, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTB_BASE, US1_SIGNAL_OUT, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTB_BASE, US2_SIGNAL_OUT, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTB_BASE, RADAR_SPI_SCLK, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTB_BASE, RADAR_SPI_SYNC, GPIO_DIR_MODE_HW);


	//POrtC
	GPIODirModeSet(GPIO_PORTC_BASE, RF_TXD, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTC_BASE, RF_RXD, GPIO_DIR_MODE_HW);

	//PortD
	GPIODirModeSet(GPIO_PORTD_BASE, US1_DRIVER_EN, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIO_PORTD_BASE, RADAR_SPI_MOSI, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTD_BASE, IR3_SENSE_OUT, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTD_BASE, IR2_SENSE_OUT, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTD_BASE, REMOTE_CH1, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTD_BASE, REMOTE_CH2, GPIO_DIR_MODE_HW);
	GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, US1_DRIVER_EN);


	//PortE
	GPIODirModeSet(GPIO_PORTE_BASE, VBAT_Measure, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTE_BASE, IR1_SENSE_OUT, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTE_BASE, RADAR_IF1, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTE_BASE, RADAR_IF2, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTE_BASE, US2_SIGNAL_IN, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTE_BASE, US1_SIGNAL_IN, GPIO_DIR_MODE_HW);



	//PortF
	GPIODirModeSet(GPIO_PORTF_BASE, MOTION_INT, GPIO_DIR_MODE_OUT);
	GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_CLK, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_MOSI, GPIO_DIR_MODE_HW);
	GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_CS, GPIO_DIR_MODE_OUT);
		GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_CLK, GPIO_DIR_MODE_HW);
		GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_MOSI, GPIO_DIR_MODE_HW);

		GPIODirModeSet(GPIO_PORTF_BASE, LCD_SPI_CS, GPIO_DIR_MODE_OUT);

		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, MOTION_INT);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,LCD_SPI_CS);

//		GPIOPadConfigSet(GPIO_PORTF_BASE, LCD_SPI_CS, GPIO_STRENGTH_2MA,GPIO_PIN_TYPE_STD_WPD);


		/*
	/////////////Port1

	P1OUT=RPM_Sensor+RPM_Sensor_DIR+START_Button+STOP_Button;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P1REN=RPM_Sensor+RPM_Sensor_DIR+START_Button+STOP_Button;  //0=pull disapled  1=pull enabled
	P1DS=0x0;  // 0=limited 1=full drive strength

	P1IE=START_Button+STOP_Button;
	P1IES=START_Button+STOP_Button;
	P1IFG=0x0;



	/////////////Port2
	P2DIR=0x0;//0=in 1=out
	P2OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P2REN=0x0;  //0=pull disapled  1=pull enabled
	P2DS=0x0;  // 0=limited 1=full drive strength
	P2SEL=0x0;  //0=I/0 Funct  1=Peripheral module function selected


	////////////Port3
	P3DIR=OPEN0+OPEN1+OPEN5+OPEN6+Throttle+Steering+SMCLK+Distance_Front_En;//0=in 1=out
	P3OUT=0x0;  // Variable zuweisen!!! 0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P3REN=0x0;  //0=pull disapled  1=pull enabled
	P3DS=0x0;  // 0=limited 1=full drive strength
	P3SEL|=SMCLK+Steering+Throttle;  //0=I/0 Funct  1=Peripheral module function selected


	////////////Port4
	P4DIR=OPEN0+OPEN1+OPEN2;//0=in 1=out
	P4OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P4REN=0x0;  //0=pull disapled  1=pull enabled
	P4DS=0x0;  // 0=limited 1=full drive strength
	P4SEL=0x0;  //0=I/0 Funct  1=Peripheral module function selected


	////////////Port5
    P5DIR=0xFF;//0=in 1=out
	P5OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P5REN=0x0;  //0=pull disapled  1=pull enabled
	P5DS=0x0;  // 0=limited 1=full drive strength
	P5SEL=0x0;  //0=I/0 Funct  1=Peripheral module function selected


	///////////Port6
    P6DIR=OPEN5+OPEN6+OPEN7+Distance_Left_EN;//0=in 1=out
	P6OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P6REN=0x0;  //0=pull disapled  1=pull enabled
	P6DS=0x0;  // 0=limited 1=full drive strength
	P6SEL=Distance_Right+Distance_Left+Distance_Front+VBAT_Measure;  //0=I/0 Funct  1=Peripheral module function selected



	///////////Port7
    P7DIR|=OPEN0+OPEN1+OPEN4+OPEN5+OPEN6+OPEN7;		//+XT2OUT				//0=in 1=out
	P7OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P7REN|=0x0;  //0=pull disapled  1=pull enabled
	P7DS=0x0;  // 0=limited 1=full drive strength
	P7SEL=XT2IN+XT2OUT; //0=I/0 Funct  1=Peripheral module function selected


	////////Port8
    P8DIR|=LCD_BL+LCD_SPI_CS+UART_TXD_AUX+LCD_SPI_CLK+LCD_SPI_MOSI+LCD_DATACMD;//0=in 1=out
	P8OUT=0x0;//LCD_SPI_CLK;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P8REN=0x0;//LCD_SPI_CLK;  //0=pull disapled  1=pull enabled
	P8DS=0x0;  // 0=limited 1=full drive strength
	P8SEL=LCD_SPI_CLK+LCD_SPI_MOSI+LCD_SPI_MISO;  //0=I/0 Funct  1=Peripheral module function selected


    ///////Port9
    P9DIR=OPEN1+OPEN2+OPEN3+OPEN4+OPEN5+OPEN6+LCD_RESET+DISTANCE_RIGHT_EN;//0=in 1=out
	P9OUT=0x0;  //0=low 1=high oder 0=Pulldown 1=Pullup
	//P1IN=;     //0=low 1=high
	P9REN=0x0;  //0=pull disapled  1=pull enabled
	P9DS=0x0;  // 0=limited 1=full drive strength
	P9SEL=0x0;  //0=I/0 Funct  1=Peripheral module function selected
*/
	//_bis_SR_register(GIE);

}
