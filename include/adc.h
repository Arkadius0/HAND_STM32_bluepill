#ifndef ADC_H
#define ADC_H
#include "stm32f103xb.h"
#include <stdint.h>

void ADC_init(void); // Initializes the ADC peripheral
uint16_t ADC_READ(uint8_t channel); // Reads the ADC value from the specified channel (0-4)

#endif