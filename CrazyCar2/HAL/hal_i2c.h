/*
 * hal_i2c.h
 *
 *  Created on: 28.03.2017
 *      Author: Sebo
 */

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_



void HAL_I2C_Init(void);
void HAL_Motion_Init(void);
void GetSlaveData(unsigned char SlaveAdress, unsigned char len, unsigned char *data);

#define SL_MOTION_ADD 0x68

typedef struct {
	unsigned char Addr;
	union{
			unsigned char R;
			struct {
					unsigned char TXSuc:1;  //Bit=1 wenn Daten  übertragen wurden
					unsigned char dummy:7;
			  }B;
		  }Status;
   struct{
			  unsigned char len;  //Länge der Daten in Bytes die übertragen werden
			  unsigned char cnt;  //Index auf Momentan übertragene Daten
			  unsigned char Data[256]; //TX Daten Array
			  unsigned char TxIntFlag;
		  }TxData;
   struct{
			  unsigned char len;   //Länge der empfangenen Daten
			  unsigned char cnt;  //Index auf Momentan empfangene Daten
			  unsigned char Data[256];  //Rx Daten Array
			  unsigned char RxIntFlag;
		  }RXData;
}i2cCom;



#endif /* HAL_HAL_I2C_H_ */
