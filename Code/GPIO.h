#ifndef GPIO_H
#define GPIO_H

void Init_PortA(void); // For Serial Communicaiction with PC via Debugger

// Enable GPIO Ports for LED & LCD Interface

void Init_PortB(void); // GPIO for LCD + UART
void Init_PortC(void); // GPIO for LCD
void Init_PortD(void); // GPIO for LCD
void Init_PortF(void); // GPIO for LCD + LEDs 

// LED Control Functions for Port F

void red_led(char state);
void green_led(char state);
void blue_led(char state);


#endif
