#include "adc.h"

void ADC_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
// Configure PA0 - PA4 to analog input mode
    GPIOA->CRL &= ~(0xFFFFF); // Clear all bits
    
    ADC1->CR2 |= ADC_CR2_ADON; // Turn on ADC

    ADC1->CR2 |= ADC_CR2_CONT; // Enable continuous conversion mode
    while (ADC1->CR2 & ADC_CR2_RSTCAL); // Wait for calibration to complete
    ADC1->CR2 |= ADC_CR2_CAL; // Start calibration
    while (ADC1->CR2 & ADC_CR2_CAL); // Wait for calibration to
  
}