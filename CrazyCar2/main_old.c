/*
 * main.c
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "HAL/hal_gpio.h"
#include "HAL/hal_usc.h"
#include "HAL/Interrupts.h"
#include "HAL/hal_timerB0.h"


void calc_freq();

int main(void) {
	HAL_UCS_Init();
	HAL_GPIO_Init();
	HAL_TimerB0_Init();


	while(1)
	{
		volatile uint32_t ui32Loop;
        for(ui32Loop = 0; ui32Loop < 10000; ui32Loop++)
        {
        }

		if(GPIOPinRead(GPIO_PORTA_BASE, LCD_BL)==LCD_BL)
		{

			GPIOPinWrite(GPIO_PORTA_BASE, LCD_BL, 0x0);
		}
		else
		{

		GPIOPinWrite(GPIO_PORTA_BASE, LCD_BL, LCD_BL);
		}

		//calc_freq();

	}

}

/*
void calc_freq()
{
	unsigned long count;
	char r[8];
	float time = 0.1;
	float freq;

    count = (10000 - timer) * 100;	// *100 converts kHz to Hz for easy displaying
    freq = time * count;			// Time is the time period the first timer is measuring, in this case it is 100mS

    RIT128x96x4StringDraw(itoa(freq,r,10), 44, 60, 15);
    RIT128x96x4StringDraw("Hz", 76, 60, 15);
}
*/
