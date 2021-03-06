/*
 * hal_adc12.h
 *
 *  Created on: 29.11.2016
 *      Author: Sebo
 */

#ifndef HAL_HAL_ADC12_H_
#define HAL_HAL_ADC12_H_


void HAL_Adc_init(void);
void IntADC (void);

typedef struct {
	union {
		unsigned char R;
		struct {
			unsigned char ADCrdy:1;
			unsigned char dummy:7;
		}B;
	}Status;
	uint32_t Bit[8];
	unsigned int Bit2;
	unsigned int Bit3;
	unsigned int vBat;

}ADC12Com;

#define Res 3,739 / 4095   //3,739 V geteilt durch die Aufl�sung des ADC 12-Bit


#endif /* HAL_HAL_ADC12_H_ */
