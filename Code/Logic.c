#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "LCD.h"
#include <math.h>
#include "GPIO.h"
#define EARTH_RADIUS_KM 6378.0f
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

//  Constant places configurations (change with actual values)
const float place_longitudes[5] = {3116.675537, 3116.707031,
     3116.827148, 3116.811523, 3116.708984};
const float place_latitudes[5]  = {3003.875732, 3003.819336,
     3003.829102, 3003.906250, 3003.933350};

//decleration of global values
extern unsigned int min_index;
extern float min_distance;
exern bool start; 


//  Landmarks names (subject to change)
//  The names are stored in a 2D array, where each row represents a place name. (auto sized)
  char* place_names[5] = {
    "CONCRETE",
    "CREDIT",
    "HALL D",
    "LIBRARY",
    "PALESTINE"
    // Add more places as needed
};
// Landmarks names lengths (adjust as per the names above)
const unsigned int place_name_lengths[5] = {8, 6, 6, 7, 9};


// Function to convert the GPS module coordinates to degrees
float convert_to_degrees(float angle) {  
    int degrees = (int)angle/100;  // Get the integer part of the coordinate
    float minutes = angle- (float)degrees*100;  // Get the decimal part and convert to minutes
    return degrees + (minutes / 60.0f);  // Convert to degrees
}

//  Function to convert degrees to radians
float to_radians(float degrees) {         
    return degrees * (3.14159265f / 180.0f);
}



//  Haversine formula to calculate the distance between two points on the earth
float calc_distance(float lon1, float lat1, float lon2, float lat2) {  
    float dlat = to_radians(abs(convert_to_degrees(lat2) - convert_to_degrees(lat1)));  // Absolute Difference in Latitudes
    float dlon = to_radians(abs(convert_to_degrees(lon2) - convert_to_degrees(lon1)));  // Absolute Difference in Longitudes

    float a = sinf(dlat / 2.0f) * sinf(dlat / 2.0f) +              //sin^2(dlat/2)
              cosf(to_radians(lat1)) * cosf(to_radians(lat2)) *    //cos(lat1)*cos(lat2)
              sinf(dlon / 2.0f) * sinf(dlon / 2.0f);               //sin^2(dlon/2)
                 
    float c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));
    return EARTH_RADIUS_KM * c *1000.0f;  // Distance in meters
}



//  Find Nearest Landmark and the Index of it
void find_nearest_place_index(float lon, float lat) {
    float d;
	  unsigned int i;
    // loop through all Landmarks to find the nearest one
    for(i = 0; i < ARRAY_SIZE(place_longitudes); i++){  
        d = calc_distance(lon, lat, place_longitudes[i], place_latitudes[i]);
        if (d < min_distance) {
            min_distance = d;
            min_index = i;
        }
    }
}

//  Function to control LEDS based on distance
void LED_State(float min_distance) {
    float upp_threshold = 50.0f; // Upper threshold for distance
    float low_threshold = 10.0f;  // Lower threshold for distance

    // If the distance is less than 10m turn on the green LED
    if (min_distance<=low_threshold) 
    {
        red_led(0); 
        blue_led(0);
        green_led(1); 
    }
    // If the distance is between 10m AND 50m turn of the blue LED
    else if (min_distance<upp_threshold && min_distance > low_threshold) 
    {
        red_led(0); 
        blue_led(1);
        green_led(0); 
    }
    // If the distance is greater than 50m turn on the red LED (worst case)
    else 
    {
        red_led(1); 
        blue_led(0);
        green_led(0);
    }
    min_distance = 100000000.0f; // Reset the minimum distance for the next calculation
}

//  Display on LCD 
void Update_LCD(unsigned int min_index) {
    if (start == true) { // Starting
        LCD_string("Waiting", 7); // calls LCD_string function to display
        
    }
    // add else if for lon and lat global variables to check 
    // start = false; // Set start to false after the first display
	else {
        LCD_string(place_names[min_index],(unsigned char)((place_name_lengths[min_index])-1)); // calls LCD_string function to display
    }
}