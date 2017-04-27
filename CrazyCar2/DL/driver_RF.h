/*
 * driver_RF.h
 *
 *  Created on: 26.04.2017
 *      Author: sbo
 */

#ifndef DL_DRIVER_RF_H_
#define DL_DRIVER_RF_H_

// comad data

//Kmmandobytes

#define NodeAdress 0x45
#define HostAdress 0x44
#define CHANNEL 0x6

#define WRITE_NODE_ADD  0x10        // zwischen 0x01 - 0xFE
#define READ_NODE_ADD   0x11
#define READ_FIRMWARE   0x12
#define READ_RF_CHANNEL  0x13
#define WRITE_RF_CHANNEL 0x14

#define WRITE_COMMAND   0x02        //<STX>
#define READ_WRITE_DATA 0x20
void RF_Init (void);
// ERRORcodes

/*
WRONG_MASSAGE_FORMAT                        0x01
Network address is missing                  0x02
Unknown command                             0x03
Wrong RF message format                     0x04
Destination address not valid               0x05
Byte Count and payload bytes not matching   0x06  /payload ungleich anzahl Bytes
Channel Number is missing                   0x07
Channel Number not in the right range       0x08

Schreiben
<STX><0x20><DESTINATION_ADDRESS(1Byte)><NUMBER_OF_BYTES(1Byte)><n Bytes>

Lesen
<STX> <0x20> <SOURCE_ADDRESS (1 Byte)> <NUMBER_OF_BYTES (1 Byte)> <n Bytes>
*/


typedef struct Test{
    unsigned char Commandbyte;
    unsigned char Command;
    unsigned char DestAdress;
    unsigned char len;
    unsigned char Data[2];


}Test;

void RxStuff(void);

#endif /* DL_DRIVER_RF_H_ */
