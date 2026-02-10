#include "stm32f103xb.h"
#include "SysTick.h"
#include <stdint.h>

int main(void)
{
  SysTick_Init(); // Initialize SysTick timer

  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // Enable GPIOC clock
  GPIOC->CRH &= ~(0xF << 20); // Clear MODE13 bits
  GPIOC->CRH |= (0x2 << 20); // Set PC13 to output mode (2MHz)




    while(1){
        uint32_t ms = SysTick_Get(); // Get current ms_tick value
        static uint32_t last_toggle_time = 0; // Static variable to store last toggle time
      if(ms - last_toggle_time >= 500) { // Toggle every 100 ms (1 second)
          GPIOC->ODR ^= (1 << 13); // Toggle PC13
          last_toggle_time = ms; // Update last toggle time
      }
    }

}