//copyright Gielen Julien
#ifndef BANANAS_H__
#define BANANAS_H__
#include <stdbool.h>
#include "player.h"
#include "maps.h"

#define ITEMS 40


bool *key_ptr; //pointer to our controls

int menu_action;

int items_x, items_y; //specify the number of items in the map
player *player_ptr; //pointer to our player structure

bool game_started; 
void screens(void);
void start_game(void);

//create the player
void create_player();

//initialze the game
void init_game(int *width, int *height);


//define the action to do depending on what key is down
void controls(bool *key_ptr);

//launch functions on a timer
void on_timer(int n);

//launch the game over screen at the end of the game
void game_over();

void key_screen(unsigned char key, int mouse0, int mouse1);
void spec_key_down(int spec_key, int mouse0, int mouse2); //check if a key is down and update the bool associated with it.
void spec_key_up(int spec_key, int mouse0, int mouse2);//check if a key is up update the bool associated with it.
void key_down(unsigned char key, int mouse0, int mouse1);//check if a special key is down update the bool associated with it.
void key_up(unsigned char key, int mouse0, int mouse1);//check if a special key is up update the bool associated with it.


#endif