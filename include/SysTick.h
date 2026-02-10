#ifndef SYSTICK_H
#define SYSTICK_H

#include "stm32f1xx.h"
#include <stdint.h>

extern volatile uint32_t ms_tick; // Global variable 
void SysTick_Init(void); // Initializes the SysTick timer
void SysTick_Delay(uint32_t delay_ms); // Delays non blocking in ms
uint32_t SysTick_Get(void); // Retrieves the current value of ms_tick (if needed)

#endif