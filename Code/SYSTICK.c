#include "SYSTICK.h"
#include "tm4c123gh6pm.h"

#define ms_ticks 16000 // Assuming 16 MHz clock, 1 ms = 16000 ticks

// Initializes the SysTick timer, using the system clock of 16 MHz

void SysTick_Init(void) {
    NVIC_ST_CTRL_R = 0; // Disable SysTick during setup
    NVIC_ST_RELOAD_R = 0x00FFFFFF; // Set reload value to max
    NVIC_ST_CURRENT_R = 0; // Clear current value
    NVIC_ST_CTRL_R = 0x00000005; // Enable SysTick with core clock
}

// Delays for a millisecond using SysTick timer, is used in the delay function because
// the counter itself cannot fit larger values than 24 bits, so we need to use a loop to count the milliseconds
// and call the function for each millisecond. 

void SYSTICK_wait_1ms(void) {
    NVIC_ST_CTRL_R = 0; // Disable SysTick during setup
    NVIC_ST_RELOAD_R = ms_ticks - 1; // Set reload value for 1 ms
    NVIC_ST_CURRENT_R = 0; // Clear current value
    NVIC_ST_CTRL_R |= 0x00000005; // Enable SysTick timer

    while ((NVIC_ST_CTRL_R & 0x00010000) == 0); // Wait for COUNT flag
    NVIC_ST_CTRL_R = 0; // Disable SysTick after delay
}


// Delays for a specified number of milliseconds using SysTick timer


void delay(unsigned int delay) {
    
    for(int i = 0; i < delay; i++) {
        SYSTICK_wait_1ms(); // Call the 1 ms wait function
    }

}
