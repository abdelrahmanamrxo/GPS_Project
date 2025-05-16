#include "tm4c123gh6pm.h"
#include "GPIO.h"
#include <stdbool.h>

////////////// The following functions are used to initialize the GPIO ports ////////////// 

/* 
    Port A has A0, A1 for UART0 (RX, TX) enabled for serial communication with PC via debugger
    Port B has B0, B1 for UART1 (RX, TX) enabled for serial communication with the GPS module
    The Rest of port A and port B, as well as the rest of the ports are used for LCD interfacing
    Port F is used for the RGB LED 

*/

void Init_PortA(void){
    SYSCTL_RCGCGPIO_R |= 0x01; // Enable clock for Port A
    while((SYSCTL_PRGPIO_R & 0x01) == 0){}; // Wait for clock to be ready

    SYSCTL_RCGCUART_R |= 0x01; // Enable clock for UART0
    while((SYSCTL_PRUART_R & 0x01) == 0){}; // Wait for clock to be ready

    GPIO_PORTA_LOCK_R = 0x4C4F434B; // Unlock Port A
    GPIO_PORTA_CR_R = 0x07; // Commit changes to PA0-PA1

    GPIO_PORTA_DEN_R = 0x07;  // Enable digital function for PA0-PA1
    GPIO_PORTA_DIR_R &= ~0x03; // Set PA0-PA1 as input/output as required by UART
    GPIO_PORTA_DIR_R |= 0x04; // Set PA2 as output

    GPIO_PORTA_AMSEL_R = 0x00; // Disable analog function
    GPIO_PORTA_PCTL_R = 0x00000011; // Set PCTL for PA0-PA1 as UART (U0RX, U0TX)
    GPIO_PORTA_AFSEL_R |= 0x03; // Enable alternate function for PA0-PA1 (UART)

    UART0_CTL_R = 0; // Disable UART0 for configuration
    UART0_IBRD_R = 104; // Set integer part of baud rate divisor (for 9600 baud rate with 16 MHz clock)
    UART0_FBRD_R = 11; // Set fractional part of baud rate divisor
    UART0_LCRH_R = 0x70; // Set line control register (8 data bits, no parity, 1 stop bit, FIFOs enabled)
    UART0_CTL_R = 0x301; // Enable UART0, TXE, RXE
}

void Init_PortB(void){
    SYSCTL_RCGCGPIO_R |= 0x02; // Enable clock for Port B
    while((SYSCTL_PRGPIO_R&0x02)==0){}; // Wait for clock to be ready

    SYSCTL_RCGCUART_R |= 0x02; // Enable clock for UART1
    while((SYSCTL_PRUART_R&0x02)==0){}; // Wait for clock to be ready
    
    GPIO_PORTB_LOCK_R = 0x4C4F434B; // Unlock Port B
    GPIO_PORTB_CR_R = 0x0B; // Commit changes to Port B 

    GPIO_PORTB_DEN_R = 0x0B;  // Enable digital function for PB0, PB1, and PB3
    GPIO_PORTB_DIR_R = 0x0B;  // Set direction for PB0-PB7 as output (PB0-PB1 for UART, PB3 for LCD)
    
    GPIO_PORTB_AMSEL_R = 0x00; // Disable analog function 
    GPIO_PORTB_PCTL_R = 0x00000011; // Set PCTL for PB0-PB1 as UART (U0RX, U0TX)
    GPIO_PORTB_AFSEL_R = 0x03; // Enable alternate function for PB0-PB1 (UART)

    UART1_CTL_R = 0; // Disable UART0 for configuration
    UART1_IBRD_R = 104; // Set integer part of baud rate divisor (for 9600 baud rate with 16 MHz clock)
    UART1_FBRD_R = 11; // Set fractional part of baud rate divisor
    UART1_LCRH_R = 0x70; // Set line control register (8 data bits, no parity, 1 stop bit, FIFOs enabled)
    UART1_CTL_R = 0x301; // Enable UART0, TXE, RXE

}

void Init_PortC(void){
    SYSCTL_RCGCGPIO_R |= 0x04; // Enable clock for Port C
    while((SYSCTL_PRGPIO_R&0x04)==0){}; // Wait for clock to be ready
    
    GPIO_PORTC_LOCK_R = 0x4C4F434B; // Unlock Port C
    GPIO_PORTC_CR_R = 0xF0; // Commit changes to Port C 
    
    GPIO_PORTC_AMSEL_R = 0x00; // Disable analog function 
    GPIO_PORTC_PCTL_R = 0x00000000; // Clear PCTL register 
    GPIO_PORTC_AFSEL_R = 0x00; // Disable alternate function 
    
    GPIO_PORTC_DEN_R = 0xFF;  // Enable digital function for PC0-PC7
    GPIO_PORTC_DIR_R = 0xFF;  // Set direction for PC0-PC7 as output
}

void Init_PortD(void){
    SYSCTL_RCGCGPIO_R |= 0x08; // Enable clock for Port D
    while((SYSCTL_PRGPIO_R&0x08)==0){}; // Wait for clock to be ready
    
    GPIO_PORTD_LOCK_R = 0x4C4F434B; // Unlock Port D
    GPIO_PORTD_CR_R = 0xCC; // Commit changes to Port D 
    
    GPIO_PORTD_AMSEL_R = 0x00; // Disable analog function 
    GPIO_PORTD_PCTL_R = 0x00000000; // Clear PCTL register 
    GPIO_PORTD_AFSEL_R = 0x00; // Disable alternate function 
    
    GPIO_PORTD_DEN_R = 0xCC;  // Enable digital function for PD0-PD7
    GPIO_PORTD_DIR_R = 0xCC;  // Set direction for PD0-PD7 as output
}

void Init_PortF(void){
    SYSCTL_RCGCGPIO_R |= 0x20; // Enable clock for Port F
    while((SYSCTL_PRGPIO_R&0x20)==0){}; // Wait for clock to be ready
    
    GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock Port F
    GPIO_PORTF_CR_R = 0x1F; // Commit changes to Port F 
    
    GPIO_PORTF_AMSEL_R = 0x00; // Disable analog function 
    GPIO_PORTF_PCTL_R = 0x00000000; // Clear PCTL register 
    GPIO_PORTF_AFSEL_R = 0x00; // Disable alternate function 
    
    GPIO_PORTF_DEN_R = 0x1F;  // Enable digital function for PF0-PF4
    GPIO_PORTF_DIR_R = 0x1F; // Set direction for PF0-PF4 as output
}

void Init_PortE(void){
    SYSCTL_RCGCGPIO_R |= 0x10; // Enable clock for Port E
    while((SYSCTL_PRGPIO_R & 0x10) == 0){}; // Wait for clock to be ready
    
    GPIO_PORTE_LOCK_R = 0x4C4F434B; // Unlock Port E
    GPIO_PORTE_CR_R = 0x02; // Commit changes to PE0-PE5
    
    GPIO_PORTE_AMSEL_R = 0x00; // Disable analog function
    GPIO_PORTE_PCTL_R = 0x00000000; // Clear PCTL register
    GPIO_PORTE_AFSEL_R = 0x00; // Disable alternate function
    
    GPIO_PORTE_DEN_R = 0x02; // Enable digital function for PE0-PE5
    GPIO_PORTE_DIR_R = 0x02; // Set direction for PE0-PE5 as output
}


////////////// The following functions are to be used to test the RGB LED on Port F //////////////

void red_led(bool state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x02; // turn on red LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x02; // turn off red LED
    }
}

void green_led(bool state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x08; // turn on green LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x08; // turn off green LED
    }
}

void blue_led(bool state) {
    if (state) {
        GPIO_PORTF_DATA_R |= 0x04; // turn on blue LED
    } else {
        GPIO_PORTF_DATA_R &= ~0x04; // turn off blue LED
    }
}

void buzzer(bool state) {
    if (state) {
        GPIO_PORTA_DATA_R |= 0x04; // turn on buzzer (PA2)
    } else {
        GPIO_PORTA_DATA_R &= ~0x04; // turn off buzzer (PA2)
    }
}

