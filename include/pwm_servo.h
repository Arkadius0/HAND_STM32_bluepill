#ifndef PWM_SERVO_H
#define PWM_SERVO_H 

#include "stm32f103xb.h"
#include <stdint.h>

void PWM_Servo_Init(void); // Initializes the PWM for servo control
void PWM_Servo_SetAngle(uint16_t servo_id, uint16_t angle); // Sets the servo angle (70-90 degrees)

#endif