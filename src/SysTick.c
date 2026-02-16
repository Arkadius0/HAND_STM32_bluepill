#include "SysTick.h"
#include "stm32f103xb.h"

volatile uint32_t ms_tick = 0;
uint32_t last_toggle_time = 0;

void SysTick_Handler(void){
    ms_tick++;
}

void SysTick_Init(void) {
    SysTick->LOAD = 72000 - 1; // Set reload value for 1ms (assuming 72MHz clock)
    SysTick->VAL = 0; // Clear current value
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                      SysTick_CTRL_TICKINT_Msk |
                      SysTick_CTRL_ENABLE_Msk; // Enable SysTick timer with interrupt
}

uint32_t SysTick_Get(void) {
    // This function can be used to retrieve the current value of ms if needed
    return ms_tick;
}
void SysTick_Delay(uint32_t delay_ms) {
    uint32_t start_time = ms_tick;
    while (ms_tick - start_time < delay_ms);
}
