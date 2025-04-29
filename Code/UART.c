#include"tm4c123gh6pm.h"
#include"UART.h"
#include<stdbool.h>

////////////// Checking Functions //////////////

// These functions check if the UART is ready to send or receive data, they return 1 if ready, 0 if not.

bool UART0_isCharAvailable(void){
    return (UART0_FR_R & 0x10) == 0; // Check if RXFE is 0 (data available)
}

bool UART1_isCharAvailable(void){
    return (UART1_FR_R & 0x10) == 0; // Check if RXFE is 0 (data available)
}

bool UART0_isTxReady(void){
    return (UART0_FR_R & 0x20) == 0; // Check if TXFF is 0 (transmit FIFO not full)
}

bool UART1_isTxReady(void){
    return (UART1_FR_R & 0x20) == 0; // Check if TXFF is 0 (transmit FIFO not full)
}


////////////// Recieving & Sending Functions //////////////

// The getString functions can take a normal string as an argument or an array of characters, both work fine as long as the string is null terminated.

char UART0_getChar(void){
    while(UART0_isCharAvailable() == 0); // Wait for character to be available
    return (char)(UART0_DR_R & 0xFF); // Read character from UART0 data register
}

char UART1_getChar(void){
    while(UART1_isCharAvailable() == 0); // Wait for character to be available
    return (char)(UART1_DR_R & 0xFF); // Read character from UART1 data register
}

void UART0_sendChar(char data){
    while(UART0_isTxReady() == 0); // Wait for transmit FIFO to be not full
    UART0_DR_R = data; // Send character to UART0 data register
}

void UART1_sendChar(char data){
    while(UART1_isTxReady() == 0); // Wait for transmit FIFO to be not full
    UART1_DR_R = data; // Send character to UART1 data register
}

void UART0_sendString(char *str){
    while(*str != '\0'){ // Loop until null terminator is reached
        UART0_sendChar(*str); // Send each character
        str++; // Move to the next character
    }
}

void UART1_sendString(char *str){
    while(*str != '\0'){ // Loop until null terminator is reached
        UART1_sendChar(*str); // Send each character
        str++; // Move to the next character
    }
}
