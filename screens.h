//copyright Gielen Julien
#ifndef SCREENS_H__
#define SCREENS_H__
#include <stdbool.h>
#define MAX_CH 350

void first_screen(int width, int height,int difficulty);
void show_controls(int width, int height);
void show_rules(int width, int height);
void game_over(int width, int height, int score);
void player_win(int width, int height, int score);

#endif