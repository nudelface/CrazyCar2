
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "HAL\hal_general.h"
#include "HAL\hal_gpio.h"
#include "HAL\Interrupts.h"
#include "HAL\hal_usc.h"
#include "HAL\hal_timerB0.h"
#include "DL\driver_general.h"
#include "DL\driver_aktorik.h"
#include "HAL\hal_usciB1.h"
//#include "HAL\hal_adc12.h"
//#include "HAL\hal_dma.h"
//#include "HAL\hal_timerA0.h"
#include "DL\driver_lcd.h"
#include "AL\Sensorcalib.h"
#include "AL\sense_read.h"
#include "AL\Controller.h"
#include "HAL\hal_i2c.h"
#include "DL\driver_gyro.h"
#include "HAL\hal_uart.h"
#include "DL\driver_RF.h"

/*
 * main.c
 */

const float kpSteer=0.5;
const float kpThrottle=0.3;

int dir=0;  //1=links 2=rechts
int icounter=0;
float Excel=40800;
float KPID=0;
float lastKPID=0;


float KpSpeed=1.4;
float KiSpeed=0.3;
float KdSpeed=0.2;




// 22 incremente


//int SteeringCalibC;
extern int SteeringCalibC;
extern ButtonCom Buttons;
extern USCIB1_SPICom SpiCom;
//extern ADC12Com ADC1;
extern int state;
extern int counterz;
extern double PeriodTime;
extern unsigned long PeriodCount;
extern int SpeedReady;
extern int SpeedDir;
extern int Timeout;

int Tryoutcount=0;


int AbstandRechts;
int AbstandLinks;
int AbstandFront;
int LastValueLeft=0;
int LastValueRight=0;
int LastValueFront=0;
float ESpeed=0;
float LastSpeed=0;
float LastESpeed=0;
int pwmOut=0;

float SpeedDes=60;
float LastSpeedDes=0;

float Speedf=0;
float Speed=20; //m/s
float LastiSpeed=0;
float iSpeed=0;

int dFront;
int dLeft;
int dRight;
int didit=0;

int StartupC=0;

int DiskretEn=0;
int HardBraking=0;


int Steer=0;

int drive=1;
int DeltaDist=0;
int dDelta=0;
int line_des=0;
int LastDeltaDist=0;
extern int SpeedSamp;
extern int initfin;


typedef enum {DriveStraight, Hinderniss, Curve} states;
typedef enum {UTurnL,UTurnR,BadRTurn, LTurn, RTurn} turns;


states statecase=DriveStraight;
states laststate=Curve;
turns  Corner=LTurn;


extern SlaveData ACCX;
extern RFRX RxData;

extern RFRX SensData;



void main(void)


  {
			HAL_Init();
			Driver_Init();

			Tryoutcount=0;

	while(1)
	{
         Tryoutcount++;
        if(Tryoutcount>=10)
        {
	    SendSensorData();
        Tryoutcount=0;
        SensData.Data[0]++;

        GetSlaveData(&ACCX);

        if(ACCX.Data>=0)
        {
        Driver_LCD_WriteUInt((int)ACCX.Data,9,5);
        }
        else
        Driver_LCD_WriteString("-",1,9,0);
        Driver_LCD_WriteUInt((int)-ACCX.Data,9,5);
        }


		//////////////////////////////Button Read
		if(Buttons.button==1&&Buttons.active==1)
		{

		//	LCD_BL_OFF;
			Buttons.button=0;
			Buttons.active=0;
			SpeedDes=0;
			drive=0;



		}
		else if (Buttons.button==2&&Buttons.active==1)
		{

		//	LCD_BL_ON;
			Driver_SetSteering(0);
			drive=1;
			statecase=DriveStraight;
			Buttons.button=0;
			Buttons.active=0;

		}

	if(RxData.RxSucc==1 && initfin==1)
		{
		  RxStuff();
		 RxData.RxSucc=0;
		}
		else if (RxData.RxSucc==2)
		{
		    Driver_LCD_WriteString("Rx_Timeout",10,1,0);
		    RxData.RxSucc=0;
		}

		//////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////

	}
  }



