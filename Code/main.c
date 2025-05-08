#include "tm4c123gh6pm.h"
#include "UART.h"
#include "SYSTICK.h"
#include "GPIO.h"
#include "LCD.h"
#include "GPS.h"
#include "Logic.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// Define global variables

float latitude = 0.0, longitude = 0.0; // Latitude and longitude values
extern bool first_read_successful; // Flag to indicate if the first read was successful
unsigned int min_index; // Index of the nearest landmark
float min_distance; // Minimum distance to the nearest landmark

int main(void){

    // Initialize GPIO and SYSTICK
        
    Init_PortA();
    Init_PortB();
    Init_PortC();
    Init_PortD();
    Init_PortF();
    Init_PortE();
    SysTick_Init();
    LCD_int();  

    while(1){
        
        // Read longitude and latitude data from GPS
        
        GPS_READ();
        GPS_format();

        // Find and print the closest location to the LCD

        find_nearest_place_index(longitude, latitude);
        Update_LCD(); // Update the LCD with the nearest place

        // Control LEDs based on distance to the nearest landmark
        
        LED_State();

        // Print latitude and longitude data to PC for debugging
        
        //GPS_data_to_UART0();

    };

}




    
    


