#include "stm32f103xb.h"
#include "SysTick.h"
#include <stdint.h>
#include "adc.h"
#include "pwm_servo.h"

#define SERVO_COUNT 5   
#define DEADZONE 5

uint16_t adc_values[SERVO_COUNT] = {0}; // Array to hold ADC values for each servo
uint16_t last_adc_values[SERVO_COUNT] = {0}; // Array to hold last ADC values for deadzone comparison

int main(void)
{
    PWM_Servo_Init(); // Initialize PWM for servo control
    for(uint8_t i=0; i<SERVO_COUNT; i++) {
        PWM_Servo_SetPulse(i, 1500); // Set all servos to neutral position (1500 microseconds)
    }
    for(volatile uint32_t i=0; i<200000; i++); // Simple delay to allow servos to reach position

    ADC_init(); // Initialize ADC
    SysTick_Init(); // Initialize SysTick timer
    
    uint16_t last_update = 0;

    while(1){
        if((SysTick_Get() - last_update) >= 20) { // Update every 20ms
            last_update = SysTick_Get();
            for(uint8_t i=0; i<SERVO_COUNT; i++){
                adc_values[i] = ADC_READ(i); // Read ADC value for each channel
                if((adc_values[i] > last_adc_values[i] + DEADZONE) || 
                   (adc_values[i] < last_adc_values[i] - DEADZONE)) {
                    last_adc_values[i] = adc_values[i]; // Update last ADC value
                    uint16_t pulse_width = ADC_MapToServo(adc_values[i]); // Map ADC value to servo pulse width
                    PWM_Servo_SetPulse(i, pulse_width); // Set servo pulse width based on ADC value
                }
            }
        }
    }
}