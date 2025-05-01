#include <stdint.h>
#include "LCD.h"
#include <math.h>
#include "GPIO.h"
#define EARTH_RADIUS_KM 6371.0

//  Constant Place Data 
const float place_longitudes[5] = {30.0, 30.1, 30.2, 30.3, 30.4};
const float place_latitudes[5]  = {31.0, 31.1, 31.2, 31.3, 31.4};

 unsigned char place_names[5][8] = {
    "HALL 1",
    "HALL A",
    "MOSQUE",
    "LIBRARY",
    "CONCRETE"
};

const unsigned char place_name_lengths[5] = {5, 5, 6, 7, 8};

//  Distance Calculation 

float to_radians(float degrees) {
    return degrees * (3.14159265f / 180.0f);
}

double calc_distance(float lon1, float lat1, float lon2, float lat2) {
    float dlat = to_radians(lat2 - lat1);
    float dlon = to_radians(lon2 - lon1);

    float a = sinf(dlat / 2.0f) * sinf(dlat / 2.0f) +
              cosf(to_radians(lat1)) * cosf(to_radians(lat2)) *
              sinf(dlon / 2.0f) * sinf(dlon / 2.0f);

    double c = 2.0f * atanf(sqrtf(a) / sqrtf(1.0f - a));
    return EARTH_RADIUS_KM * c;
}






//  Find Nearest Place Index 
unsigned char find_nearest_place_index(float lon, float lat) {
    unsigned char min_index = 0;
    double min_distance =calc_distance(lon, lat, place_longitudes[0], place_latitudes[0]);
		unsigned char i;
    for (i = 1; i < 5; i++) {
        double d = calc_distance(lon, lat, place_longitudes[i], place_latitudes[i]);
        if (d < min_distance) {
            min_distance = d;
            min_index = i;
        }
    }
    if (min_distance<5.0f)
    {
        red_led(0);
        blue_led(0);
        green_led(1); 
    
    }
    else if (min_distance< 20.0f)
    {
        green_led(0); 
        red_led(0);
        blue_led(1);
    
    }
    else{
        green_led(0); 
        blue_led(0);
        red_led(1);
    
    }

    return min_index;
}

//  Display on LCD 
void show_nearest_place(float lon, float lat) {
    unsigned char index = find_nearest_place_index(lon, lat);
  
	LCD_string(place_names[index], place_name_lengths[index]);
}

