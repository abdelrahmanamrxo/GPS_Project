#ifndef LCD.h
#define LCD.h

#include <stdbool.h>


void printdata(unsigned char data);// Sends a data byte to the LCD module through pins D0-->D7.

void LCD_DATA(unsigned char data);// Sends a data byte to the LCD module.

void LCD_cmd(unsigned char cmd);// Sends a command byte to the LCD module.

void LCD_string(char *str , unsigned char len);// Sends a string to the LCD module.

void LCD_int(void);// Initializes the LCD module.


#endif



