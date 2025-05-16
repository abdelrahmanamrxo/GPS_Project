#ifndef LOGIC_H
#define LOGIC_H
#include <stdbool.h>  

// from radians to degrees
float to_radians(float degrees);

// calculate the distance between two points on the earth
float calc_distance(float lon1, float lat1, float lon2, float lat2);

// find the nearest landmark and the index of it
void find_nearest_place_index(float lon, float lat);

//  Function to control LEDS based on distance    
void LED_State(void);

//  Function to update the LCD with the nearest place
void Update_LCD(void);

// Find absolute of float value

float absolute(float value);

// Activate the buzzer
void activate_buzzer(void);

// Converts to standard degrees
float convert_to_degrees(float angle);

#endif
