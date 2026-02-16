#include "stm32f103xb.h"
#include "adc.h"
#include "SysTick.h"
#include "pwm_servo.h"
#include <stdint.h>


#define SERVO_COUNT 5   

const uint8_t servo_to_adc[SERVO_COUNT] = {4, 5, 6, 7, 9}; // ADC channels for each servo

uint16_t last_adc[SERVO_COUNT] = {2048, 2048, 2048, 2048, 2048}; // Initialize last ADC values to middle value (2048)

// safe angle range
#define ANGLE_MIN 10     // Minimum 10°
#define ANGLE_MAX 170    // Maximum 170°
#define DEADZONE 15     // Deadzone for ADC changes 

#define ANGLE_RANGE (ANGLE_MAX - ANGLE_MIN)  // 160°

uint8_t ADC_to_Angle(uint16_t adc) {
    // Mapuj CAŁY zakres ADC (0-4095) na bezpieczny zakres kąta
    uint32_t angle = ANGLE_MIN + ((uint32_t)adc * ANGLE_RANGE) / 4095;
    return (uint8_t)angle;
}

int main(void) {
    PWM_Servo_Init();
       for(uint8_t i=0; i<SERVO_COUNT; i++) {
        PWM_Servo_SetAngle(i, 90); // Set all servos to neutral position (1500 microseconds)
    }
    for(volatile uint32_t i=0; i<200000; i++); // Simple delay to allow servos to reach position
    ADC_init();
    SysTick_Init();
    
    uint32_t last_update = 0;
    
    while(1) {
        if (SysTick_Get() -last_update >= 20){ // Update every 20ms (50Hz)
            last_update = SysTick_Get();
            for(uint8_t i=0; i<SERVO_COUNT; i++){
                uint8_t adc_channel = servo_to_adc[i];
                uint16_t adc_value = ADC_READ(adc_channel);
                if (adc_value > last_adc[i] + DEADZONE || adc_value < last_adc[i] - DEADZONE) { // Only update if ADC value has changed significantly
                    last_adc[i] = adc_value;
                    uint8_t angle = ADC_to_Angle(adc_value);
                    PWM_Servo_SetAngle(i, angle);
                }
            }
        }
    }
}