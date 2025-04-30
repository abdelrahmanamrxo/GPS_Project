#include"tm4c123gh6pm.h"
#include<stdbool.h>

///////////////pin layout
//RS-->PD0
//RW-->PD1
//EN-->PD2

//D0-->PB3
//D1-->PC4
//D2-->PC5
//D3-->PC6
//D4-->PC7
//D5-->PD6
//D6-->PD7
//D7-->PF4







void printdata(unsigned char data){               // Sends byte to the LCD module through pins D0-->D7.

    if( (data & 0x01) == 0x01 ) GPIO_PORTB_DATA_R |= (1<<3); // Set PB3 if bit 0 of data is 1 (D0)
    else GPIO_PORTB_DATA_R &=(~ (1<<3) );                  // Clear PB3 if bit 0 of data is 0

    if( (data & 0x02) == 0x02 ) GPIO_PORTC_DATA_R |= (1<<4); // Set PC4 if bit 1 of data is 1 (D1)
    else GPIO_PORTC_DATA_R &=(~ (1<<4) );                  // Clear PC4 if bit 1 of data is 0

    if( (data & 0x04) == 0x04 ) GPIO_PORTC_DATA_R |= (1<<5); // Set PC5 if bit 2 of data is 1 (D2)
    else GPIO_PORTC_DATA_R &=(~ (1<<5) );                  // Clear PC5 if bit 2 of data is 0

    if( (data & 0x08) == 0x08 ) GPIO_PORTC_DATA_R |= (1<<6); // Set PC6 if bit 3 of data is 1 (D3)
    else GPIO_PORTC_DATA_R &=(~ (1<<6) );                  // Clear PC6 if bit 3 of data is 0

    if( (data & 0x10) == 0x10 ) GPIO_PORTC_DATA_R |= (1<<7); // Set PC7 if bit 4 of data is 1 (D4)
    else GPIO_PORTC_DATA_R &=(~ (1<<7) );                  // Clear PC7 if bit 4 of data is 0

    if( (data & 0x20) == 0x20 ) GPIO_PORTD_DATA_R |= (1<<6); // Set PD6 if bit 5 of data is 1 (D5)
    else GPIO_PORTD_DATA_R &=(~ (1<<6) );                  // Clear PD6 if bit 5 of data is 0

    if( (data & 0x40) == 0x40 ) GPIO_PORTD_DATA_R |= (1<<7); // Set PD7 if bit 6 of data is 1 (D6)
    else GPIO_PORTD_DATA_R &=(~ (1<<7) );                  // Clear PD7 if bit 6 of data is 0

    if( (data & 0x80) == 0x80 ) GPIO_PORTF_DATA_R |= (1<<4); // Set PF4 if bit 7 of data is 1 (D7)
    else GPIO_PORTF_DATA_R &=(~ (1<<4) );                  // Clear PF4 if bit 7 of data is 0



}

void LCD_DATA(unsigned char data){                //Sends a data byte to the LCD module.

    GPIO_PORTD_DATA_R |= (1<<2);  //EN=1
    GPIO_PORTD_DATA_R |= (1<<0);  //RS=1
    GPIO_PORTD_DATA_R &= ~(1<<1); //RW=0
    printdata(data);                         //send an 8-bit data value to the LCD for display
    for(int i=0;i<1000;i++);      //Delay/////////////////////////////////////////////////////////////////////////////////////////////change
    GPIO_PORTD_DATA_R &= ~(1<<2); //EN=0



    /* Control Signals:
    * - RS (Register Select): Set to 1 to indicate data register.
    * - RW (Read/Write): Set to 0 to indicate a write operation.
    * - EN (Enable): A high-to-low pulse to latch the data into the LCD.
    */

    }


void LCD_cmd(unsigned char cmd){                  //Sends a command byte to the LCD module.

    GPIO_PORTD_DATA_R |= (1<<2);  //EN=1
    GPIO_PORTD_DATA_R &= ~(1<<0); //RS=0
    GPIO_PORTD_DATA_R &= ~(1<<1); //RW=0
    printdata(cmd);                     //send an 8-bit command value to the LCD for execution
    for(int i=0;i<1000;i++);      //Delay/////////////////////////////////////////////////////////////////////////////////////////////change
    GPIO_PORTD_DATA_R &= ~(1<<2); //EN=0


    /** Control Signals:
    * - RS (Register Select): Set to 0 to indicate a command is being sent.
    * - RW (Read/Write): Set to 0 to indicate a write operation.
    * - EN (Enable): Pulsed high to latch the command into the LCD.
    *
    */
}





void LCD_string(char *str , unsigned char len){   // Sends a string to the LCD module as data byte.

    char i;
    for( i = 0 ; i < len ; i++ ) LCD_DATA(str[i]); // Send each character to the LCD


    /*
    * @param str Pointer to the string to be displayed on the LCD.
    * @param len Length of the string (number of characters).
    */

}


void LCD_int(void){                              // Initialize the LCD module

    // Send initialization commands to the LCD

    LCD_cmd(0x38); // Function set: 8-bit mode, 2 lines, 5x7 dots
    LCD_cmd(0x06); // Entry mode set: increment cursor, no shift
    LCD_cmd(0x0C); // Display on, cursor off, blink off
    LCD_cmd(0x01); // Clear display
    LCD_cmd(0x80); // Set cursor position to first line, first column

}
