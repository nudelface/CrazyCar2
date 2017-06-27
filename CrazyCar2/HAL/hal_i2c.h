/*
 * hal_i2c.h
 *
 *  Created on: 28.03.2017
 *      Author: Sebo
 */

#ifndef HAL_HAL_I2C_H_
#define HAL_HAL_I2C_H_



void HAL_I2C_Init(void);



typedef struct SlaveData{
    unsigned char SlAddr;
    unsigned char RAddr;
    unsigned char Datab1;
    unsigned char Datab2;
    unsigned char lenRX;
    unsigned char lenTX;
    signed short Data;
    unsigned char RxData[10];
    int READ;
    float multiplier;
    float value;
    int millivalue;
    unsigned int LSB;
    float offset;
}SlaveData;

typedef struct Command{
    unsigned char SlAddr;
    unsigned char RAdd[10];
    unsigned char RData[10];
}Command;

void GetSlaveData(SlaveData *data);
void SendCommand(Command *data, int numCmd);

enum {WriteRegAd,Byte1, Byte2,SingleByte};

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
