#ifndef UART_H
#define UART_H

#include <stdbool.h>

// Check data on Receiver

bool UART0_isCharAvailable(void);
bool UART1_isCharAvailable(void);

// Check if Transmitter is ready to send data

bool UART0_isTxReady(void);
bool UART1_isTxReady(void);

// Receive and Send data

char UART0_getChar(void);
char UART1_getChar(void);
void UART0_sendChar(char data);
void UART1_sendChar(char data);
void UART0_sendString(char *str);
void UART1_sendString(char *str);

// Special functions for debugging 

void GPS_data_to_UART0(void);
void UART0_printFloat(float value);

#endif
