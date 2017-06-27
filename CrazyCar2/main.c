
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
#include "HAL\hal_UltraMeas.h"
#include "DL\driver_general.h"
#include "DL\driver_aktorik.h"
#include "HAL\hal_usciB1.h"
#include "driverlib/uart.h"
#include "HAL\hal_adc12.h"
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
#include "driverlib/pwm.h"


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
extern ADC12Com ADC1;
extern int state;
extern int counterz;
extern double PeriodTime;
extern unsigned long PeriodCount;
extern int SpeedReady;
extern int SpeedDir;
extern int Timeout;

int Tryoutcount=0;


int Abstand1;
int Abstand2;
int Abstand3;
long b_Abstand1;
long b_Abstand2;
long b_Abstand3;
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


extern SlaveData ACCX, ACCY, ACCZ,GYRX, GYRY, GYRZ,MagX,MagY,MagZ;
extern RFRX RxData;
extern double Hy,Hx,Hz,Hy_f,Hx_f,Hz_f;
extern float phi;

extern RFRX SensData;

float TESTI;
extern unsigned long Globalmillis;
extern unsigned long Globaltenmillis;
extern unsigned long Globalsecond;
extern int tenmillisready;
extern int millisready;
extern int secondready;

float acc_speed_x=0;
float acc_speed_x_last=0;
float dt=0;
float t_last=0;
float acc_dist_x=0;
float acc_dist_x_last=0;
int firststart=1;

void main(void)


  {
			HAL_Init();
			Driver_Init();

			Tryoutcount=0;
			Driver_LCD_Clear();
			SysCtlDelay(10000);
	while(1)
	{
        GPIOPinWrite(GPIO_PORTA_BASE, US2_DRIVER_EN, US2_DRIVER_EN);
        GPIOPinWrite(GPIO_PORTD_BASE, US1_DRIVER_EN, US1_DRIVER_EN);
         Tryoutcount+=1;
        // GPIOPinWrite(GPIO_PORTA_BASE, US2_DRIVER_EN, ~US2_DRIVER_EN);
        // GPIOPinWrite(GPIO_PORTD_BASE, US1_DRIVER_EN, ~US1_DRIVER_EN);
         if(ADC1.Status.B.ADCrdy==1)
         {
        	 b_Abstand1=ADC1.Bit[2];
        	 b_Abstand2=ADC1.Bit[4];
        	 b_Abstand3=ADC1.Bit[5];
        	 Abstand1=Dist(b_Abstand1);
        	 Abstand2=Dist(b_Abstand2);
        	 Abstand3=Dist(b_Abstand3);
        /*	 Driver_LCD_WriteString("1",1,3,0);
        	 Driver_LCD_WriteString("2",1,4,0);
        	 Driver_LCD_WriteString("3",1,5,0);
        	 Driver_LCD_WriteUInt((unsigned int)Abstand1,3,14);
        	 Driver_LCD_WriteUInt((unsigned int)Abstand2,4,14);
        	 Driver_LCD_WriteUInt((unsigned int)Abstand3,5,14);
        	 */
        	 ADC1.Status.B.ADCrdy=0;

         }

        if(Tryoutcount>100000)
        {
        	SensData.Data[0]=(int)ACCX.value;
        	//SendSensorData();
        if(Tryoutcount<100001)
        {
        	TESTI=MeasDist();

        }
        else
        {
        	Tryoutcount=0;

        }

        if(tenmillisready==1)  //Every ten milliseconds
        {
        	dt=((float)Globalmillis/1000)-t_last;
        	t_last=(float)Globalmillis/1000;
        	acc_speed_x=ACCX.value*dt+acc_speed_x_last; // in m/s/s * s
        	acc_speed_x_last=acc_speed_x;

        	acc_dist_x=((ACCX.value/2)*(dt*dt))+acc_dist_x_last;
        	acc_dist_x_last=acc_dist_x;

        	tenmillisready=0;
        }
        if(secondready==1)
        {
        	acc_speed_x_last=ACCX.value*dt; //noramlisieren
        	secondready=0;
        }

      //  SensData.Data[0]++;

        GetSlaveData(&ACCX);
        GetSlaveData(&ACCY);
        GetSlaveData(&ACCZ);
        GetSlaveData(&GYRX);
        GetSlaveData(&GYRY);
        GetSlaveData(&GYRZ);
        GetMagData();

        if(firststart==1)
        {
        ACCX.offset=ACCX.value;
        ACCY.offset=ACCY.value;
        ACCZ.offset=ACCZ.value;
        firststart=0;
        }


       if((ACCX.millivalue)>=0)
         {
             Driver_LCD_WriteString("+",1,2,5);
             Driver_LCD_WriteUInt((unsigned int)(ACCX.millivalue),2,14);
         }
         else
         {
         Driver_LCD_WriteString("-",1,2,5);
         Driver_LCD_WriteUInt((unsigned int)-(ACCX.millivalue),2,14);
         }
       if((acc_speed_x)>=0)
         {
             Driver_LCD_WriteString("+",1,3,5);
             Driver_LCD_WriteUInt((unsigned int)(acc_speed_x),3,14);
         }
         else
         {
         Driver_LCD_WriteString("-",1,3,5);
         Driver_LCD_WriteUInt((unsigned int)-(acc_speed_x),3,14);
         }

       /*        if((ACCY.millivalue)>=0)
         {
             Driver_LCD_WriteString("+",1,2,5);
             Driver_LCD_WriteUInt((unsigned int)(ACCY.millivalue),2,14);
         }
         else
         {
         Driver_LCD_WriteString("-",1,2,5);
         Driver_LCD_WriteUInt((unsigned int)-(ACCY.millivalue),2,14);
         }
         */
        /*
       // Driver_LCD_WriteString("X",1,1,0);
       // Driver_LCD_WriteUInt((unsigned int)TESTI,1,14);
       if((Hx*1000)>=0)
        {
            Driver_LCD_WriteString("+",1,1,5);
            Driver_LCD_WriteUInt((unsigned int)(Hx_f*1000),1,14);
        }
        else
        {
        Driver_LCD_WriteString("-",1,1,5);
        Driver_LCD_WriteUInt((unsigned int)-(Hx_f*1000),1,14);
        }
        Driver_LCD_WriteString("nT",2,1,45);

        Driver_LCD_WriteString("Y",1,2,0);

        if((Hy*1000)>=0)
        {
            Driver_LCD_WriteString("+",1,2,5);
            Driver_LCD_WriteUInt((unsigned int)(Hy_f*1000),2,14);
        }
        else
        {
        Driver_LCD_WriteString("-",1,2,5);
        Driver_LCD_WriteUInt((unsigned int)-(Hy_f*1000),2,14);
        }
        Driver_LCD_WriteString("nT",2,2,45);


        Driver_LCD_WriteString("Z",1,3,0);

        if((Hz*1000)>=0)
        {
            Driver_LCD_WriteString("+",1,3,5);
            Driver_LCD_WriteUInt((unsigned int)(Hz_f*1000),3,14);
        }
        else
        {
        Driver_LCD_WriteString("-",1,3,5);
        Driver_LCD_WriteUInt((unsigned int)-(Hz_f*1000),3,14);
        }
        Driver_LCD_WriteString("nT",2,3,45);



        Driver_LCD_WriteString("Winkel",4,4,10);

        Driver_LCD_WriteString("phi",3,5,0);
        if(phi>=0)
        {
            Driver_LCD_WriteString("+",1,5,22);
            Driver_LCD_WriteUInt((unsigned int)phi,5,28);
        }
        else
        {
        Driver_LCD_WriteString("-",1,5,22);
        Driver_LCD_WriteUInt((unsigned int)-phi,5,28);
        }
        Driver_LCD_WriteString("Grad",4,6,55);

        Driver_LCD_WriteString("Y",1,6,0);
        if(GYRY.Data>=0)
        {
            Driver_LCD_WriteString("+",1,6,5);
            Driver_LCD_WriteUInt((GYRY.millivalue),6,14);
        }
        else
        {
        Driver_LCD_WriteString("-",1,6,5);
        Driver_LCD_WriteUInt((unsigned int)-GYRY.millivalue,6,14);
        }
        Driver_LCD_WriteString("dps",3,6,45);


        Driver_LCD_WriteString("Z",1,7,0);
        if(GYRZ.Data>=0)
        {
            Driver_LCD_WriteString("+",1,7,5);
            Driver_LCD_WriteUInt((GYRZ.millivalue),7,14);
        }
        else
        {
        Driver_LCD_WriteString("-",1,7,5);
        Driver_LCD_WriteUInt((unsigned int)-GYRZ.millivalue,7,14);
        }
        Driver_LCD_WriteString("dps",3,7,45);


        */


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
		    UARTIntEnable(UART1_BASE, UART_INT_RX );
		}
		else if(RxData.RxSucc==1 && initfin==0)
		{
			UARTIntEnable(UART1_BASE, UART_INT_RX );
		}
		//////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////

	}
        else
        {

        }
  }
  }


