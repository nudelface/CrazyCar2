/*
 * hal_uart.h
 *
 *  Created on: 26.04.2017
 *      Author: sbo
 */

#ifndef HAL_HAL_UART_H_
#define HAL_HAL_UART_H_

void hal_uart_init(void);
void UARTIntHandler(void);
void TxData(unsigned char *Tx_data,unsigned char len);

#define Baud 115200


typedef struct RFCommand{
    unsigned char Commandbyte;
    unsigned char Command;
    unsigned char CommandData;
}RFCommand;

typedef struct RFRX{
    unsigned char Commandbyte;
    unsigned char Command;
    unsigned char NodeAddr;
    unsigned char len;
    unsigned char Data[10];


    unsigned char RxSucc;
}RFRX;



#endif /* HAL_HAL_UART_H_ */
