#include"tm4c123gh6pm.h"
#include"UART.h"
#include<stdbool.h>


int main (void){

    // Initialize the GPIO ports for the LCD
    Init_PortB(); // Initialize Port B for LCD data pins
    Init_PortC(); // Initialize Port C for LCD data pins
    Init_PortD(); // Initialize Port D for LCD control pins
    Init_PortF(); // Initialize Port F for additional control pins (if needed)

    // Initialize the LCD
    LCD_int(); // Call the LCD initialization function

    // Example usage: Display a string on the LCD
    char message[] = "a";
    LCD_string(message, sizeof(message) - 1); // Send the string to the LCD
    
    while(1) {
        // Main loop can be used for other tasks or to update the display
    }

   
}
