#ifndef __ADC
#define __ADC

#include "stm8.h"

void adc_init(){
	ADC_CR2 |= (1 << 3); // Right Aligned DATA
	ADC_CR1 |= (1 << 0); // ADC ON

	ADC_CR1 &= ~(1 << 1); // CONT bit to off
	ADC_CR2 &= ~(1 << 1); // SCAN bit is off
}

unsigned int adc_read(unsigned int channel){
	
	unsigned int output = 0;

	ADC_CSR &= 0b01111111;

	// if(channel == 5){
	// 	ADC_CSR &= (0b11110000);
	// 	ADC_CSR |= (0b00000101);
	// } else {
	// 	ADC_CSR &= (0b11110000);
	// 	ADC_CSR |= (0b00000100);
	// }

	ADC_CSR &= (0b11110000);
	ADC_CSR |= ((0x0F) & channel); // Select Channel
	// ADC_CR2 |= (1 << 3); // Right Aligned DATA
	// ADC_CR1 |= (1 << 0); // ADC ON
	ADC_CR1 |= (1 << 0); // ADC Start Conversion

	// Wait until EOC bit is set by hardware
	while((ADC_CSR) & 0b10000000 == 0){
		nop();
	}

	// copy data from data registers into value
	output |= (unsigned int) ADC_DRL;
	output |= (unsigned int) ADC_DRH << 8;

	// stop ADC conversion
	// ADC_CR1 &= ~(1 << 0);
	// ADC_CSR &= 0b01110000;

	output &= 0x3FF;
	return output;

}

#endif // __ADC