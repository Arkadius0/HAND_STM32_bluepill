#include "pwm_servo.h"

// safe angle range
#define ANGLE_MIN 10     // Minimum 10°
#define ANGLE_MAX 170    // Maximum 170°

void PWM_Servo_Init(void) {
    //timers
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN; // Enable GPIOA and GPIOB clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN; // Enable TIM2 and TIM3 clock
    // TIM2 for PA0 PA1 PA2 PA3
    GPIOA->CRL &= ~(0xFFFF); // Clear all bits for PA0-PA3
    GPIOA->CRL |= (0xBBBB); // Set PA0-PA3 to alternate function push-pull (2MHz)
    // TIM2 configuration
    TIM2->PSC = 72 - 1; // Prescaler for 1MHz
    TIM2->ARR = 20000 - 1; // Auto-reload for 20ms (50Hz)

    TIM2->CCMR1 = 0x6868; // PWM mode 1 for channels 1 and 2
    TIM2->CCMR2 = 0x6868; // PWM mode 1 for channels 3 and 4

    TIM2->CCER = TIM_CCER_CC1E | 
                 TIM_CCER_CC2E | 
                 TIM_CCER_CC3E | 
                 TIM_CCER_CC4E; // Enable output for all channels

    TIM2->CR1 |= TIM_CR1_CEN; // Start TIM2

    GPIOB->CRL &= ~(0xF); // Clear MODE12 bits
    GPIOB->CRL |= (0xB); // Set AF PP

    TIM3->PSC = 72 - 1; // Prescaler for 1MHz
    TIM3->ARR = 20000 - 1; // Auto-reload for 20ms (50Hz)

    TIM3->CCMR1 = 0x6868; // PWM mode 1 for channels 1 and 2
    TIM3->CCER = TIM_CCER_CC1E; // Enable output for channel 1


    TIM3->CR1 |= TIM_CR1_CEN; // Start TIM3

    // Set all servos to neutral position (1500 microseconds)
    TIM2->CCR1 = 1500; // Neutral position for servo 1
    TIM2->CCR2 = 1500; // Neutral position for servo 2
    TIM2->CCR3 = 1500; // Neutral position for servo 3
    TIM2->CCR4 = 1500; // Neutral position for servo 4
    TIM3->CCR1 = 1500; // Neutral position for servo 5
}

void PWM_Servo_SetAngle(uint16_t servo_id, uint16_t angle) {
  
    if(angle < ANGLE_MIN) angle = ANGLE_MIN;
    if(angle > ANGLE_MAX) angle = ANGLE_MAX;
    uint16_t pulse_us = 50 + (angle * 200) / 180; // Map 70-90° to 1000-2000 microseconds


    switch (servo_id) {
        case 0:
            TIM2->CCR1 = pulse_us; // Set pulse width for servo 1
            break;
        case 1:
            TIM2->CCR2 = pulse_us; // Set pulse width for servo 2
            break;
        case 2:
            TIM2->CCR3 = pulse_us; // Set pulse width for servo 3
            break;
        case 3:
            TIM2->CCR4 = pulse_us; // Set pulse width for servo 4
            break;
        case 4:
            TIM3->CCR1 = pulse_us; // Set pulse width for servo 5
            break;
        default:
            // Invalid servo_id, do nothing or handle error
            break;
    }
}
