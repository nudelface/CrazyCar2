/*
 * hal_gpio.h
 *
 *  Created on: 10. Okt. 2016
 *      Author: KlotzSeb
 */

#ifndef HAL_HAL_GPIO_H_
#define HAL_HAL_GPIO_H_


/////Unconnected

void HAL_GPIO_Init(void);


#define OPEN0 BIT0
#define OPEN1 BIT1
#define OPEN2 BIT2
#define OPEN3 BIT3
#define OPEN4 BIT4
#define OPEN5 BIT5
#define OPEN6 BIT6
#define OPEN7 BIT7




///PortA
#define LCD_BL GPIO_PIN_2
#define LCD_DATACMD GPIO_PIN_3
#define LCD_RESET GPIO_PIN_4
#define US2_DRIVER_EN GPIO_PIN_5
#define Steering GPIO_PIN_6
#define Throttle GPIO_PIN_7


////PortB
#define I2C_SCL_MOTION GPIO_PIN_2
#define I2C_SDA_MOTION GPIO_PIN_3
#define US1_SIGNAL_OUT GPIO_PIN_0
#define US2_SIGNAL_OUT GPIO_PIN_1
#define RADAR_SPI_SCLK GPIO_PIN_4
#define RADAR_SPI_SYNC GPIO_PIN_5



///PortC
#define RF_TXD GPIO_PIN_4
#define RF_RXD GPIO_PIN_5

///PortD
#define US1_DRIVER_EN GPIO_PIN_0
#define RADAR_SPI_MOSI GPIO_PIN_1
#define IR3_SENSE_OUT GPIO_PIN_2
#define IR2_SENSE_OUT GPIO_PIN_3
#define REMOTE_CH1 GPIO_PIN_6
#define REMOTE_CH2 GPIO_PIN_7

///PortE
#define VBAT_Measure GPIO_PIN_0
#define IR1_SENSE_OUT GPIO_PIN_1
#define RADAR_IF1 GPIO_PIN_2
#define RADAR_IF2 GPIO_PIN_3
#define US2_SIGNAL_IN GPIO_PIN_4
#define US1_SIGNAL_IN GPIO_PIN_5


////PortF
#define MOTION_INT GPIO_PIN_0
#define LCD_SPI_MOSI GPIO_PIN_1
#define  LCD_SPI_CLK GPIO_PIN_2
#define LCD_SPI_CS GPIO_PIN_3

















/*

///Port2
#define DEBUG_TXD BIT0
#define DEBUG_RXD BIT1
#define AUX_Pin_1 BIT2
#define AUX_Pin_2 BIT3
#define AUX_Pin_3 BIT4
#define AUX_Pin_4 BIT5
#define I2C_SDA_MOTION BIT6
#define I2C_SCL_MOTION BIT7

///Port3
#define Throttle BIT2
#define Steering BIT3
#define SMCLK BIT4
#define Distance_Front_En BIT7

///Port 4
#define Line_Follow_1 BIT4
#define Line_Follow_2 BIT3
#define Line_Follow_3 BIT5
#define Line_Follow_4 BIT6
#define Line_Follow_7 BIT7

//Port 5 not USED

//Port6
#define Distance_Right BIT0
#define Distance_Left BIT1
#define Distance_Front BIT2
#define VBAT_Measure BIT3
#define Distance_Left_EN BIT4

//Port7
#define XT2IN BIT2
#define XT2OUT BIT3


//Port 8
#define LCD_BL           BIT0
#define LCD_SPI_CS       BIT1
#define UART_TXD_AUX     BIT2
#define UART_RXT_AUX     BIT3
#define LCD_SPI_CLK      BIT4
#define LCD_SPI_MOSI     BIT5
#define LCD_SPI_MISO     BIT6
#define LCD_DATACMD      BIT7

//Port 9
#define LCD_RESET           BIT0
#define DISTANCE_RIGHT_EN   BIT7

//Übergabe




///Makros
#define LCD_BL_ON (P8OUT|=LCD_BL)
#define LCD_BL_OFF (P8OUT&= ~LCD_BL)

*/



#endif /* HAL_HAL_GPIO_H_ */
