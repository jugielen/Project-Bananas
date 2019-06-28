//copyright Gielen Julien
#ifndef __MAP_H__
#define __MAP_H__
#include <stdlib.h>
#include <stdio.h>

#define ITEMS_SIZE 15

//structure for my map
typedef struct my_maps{
    float scrolling; //specified the scrolling, 1 for vertical, 0 for horizontal
    char **map; //actual map
    int difficulty;
}Maps;

Maps *map_ptr; //pointer to my map structure

void init_map(int max_x, int max_y,Maps *my);//initialize an empty map with max_x and max_y items
void load_map(int max_x, int max_y,Maps *my);//load map from txt file with max_x and max_y items
void display_map(int max_x, int max_y,char **map,int score,int lives,float move_up);//display the object from the map

#endif