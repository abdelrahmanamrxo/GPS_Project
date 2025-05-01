#ifndef LOGIC_H

#define LOGIC_H  

float to_radians(float degrees);
float calc_distance(float lon1, float lat1, float lon2, float lat2);
unsigned char find_nearest_place_index(float lon, float lat);
void show_nearest_place(float lon, float lat);

#endif

