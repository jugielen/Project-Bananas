//copyright Gielen Julien
#ifndef __ENNEMIES_H__
#define __ENNEMIES_H__
#include <stdbool.h>

// defintion of my ennemy structure for a double chained circular list.
typedef struct Ennemies{
    int position_x;
    int position_y;
    struct Ennemies *previous_ptr;
    struct Ennemies *next_ptr;
} ennemy;

ennemy *ennemies_ptr; //external pointer to my ennemies list
int ennemy_jump;

// defintion of my laser structure for a double chained circular list.
typedef struct Lasers{
    int position_x;
    int position_y;
    int duration;
    int direction;
    struct Lasers *previous_ptr;
    struct Lasers *next_ptr;
} laser;

laser *lasers_ptr; //external pointer to my lasers list

int ennemy_progress(void); //return the move that ennemies need to make
bool move_ennemy(char **map, int *score); //move the ennmies on the map
ennemy *look_for_ennemy(int x, int y);// look for an ennemy with the specified position and return the pointer to that ennemy;
void remove_ennemy(ennemy *ennemy_killed); //remove the pointed ennemy from the list
void add_ennemy(int x,int y); //add an ennemy to the list
void create_ennemies(char **map, int max_x, int max_y); //create the ennemy list
void add_laser(int x,int y, int direction); //add laser to the list
void remove_laser(laser *laser_terminated); //remove laser from the list
laser *look_for_laser(int x, int y); //look for a laser with the specified position
void move_laser(char **map, int *score,int max_x); //move the laser on the map
#endif