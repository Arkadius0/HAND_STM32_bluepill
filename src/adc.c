#include "adc.h"

void ADC_init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; // Enable ADC1 clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Enable GPIOA clock
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; // Enable GPIOB clock
// Configure PA0 - PA4 to analog input mode
    GPIOA->CRL &= ~(0xFFF0000); // Clear all bits
    GPIOA->CRL |= 0x4440000; // Set PA0-PA4 to analog input mode (CNF=00, MODE=00)

    GPIOB->CRL &= ~(0xF00); // Clear all bits for PB1
    GPIOB->CRL |= 0x400; // Set PB1 to analog input mode (CNF=00, MODE=00)

    ADC1->CR2 |= ADC_CR2_ADON; // Turn on ADC

    ADC1->CR2 |= ADC_CR2_RSTCAL; // Reset calibration
    while (ADC1->CR2 & ADC_CR2_RSTCAL); // Wait for calibration to complete
    ADC1->CR2 |= ADC_CR2_CAL; // Start calibration
    while (ADC1->CR2 & ADC_CR2_CAL); // Wait for calibration to

   ADC1->SMPR2 = (ADC1->SMPR2 & ~0x3FFFFFFF) | 0x2AAAAAA8; // 239.5 cykli
}

uint16_t ADC_READ(uint8_t channel) {
    
    if (channel != 4 && channel != 5 && channel != 6 && channel != 7 && channel != 9) return 0;// Invalid channel, return 0
    
    ADC1->SQR3 = channel; // Select the channel to convert
    ADC1->CR2 |= ADC_CR2_ADON; // Start conversion

    while (!(ADC1->SR & ADC_SR_EOC)); // Wait for conversion to complete
    return ADC1->DR; // Return the converted value
}

// uint16_t ADC_MapToServo(uint16_t adc_value) {
//     // Map the ADC value (0-4095) to a servo control value (0-180 degrees)
//     return (adc_value * 1000) / 4095 + 1000; // Map to 1000-2000 microseconds for servo control
// }
