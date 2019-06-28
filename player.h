//copyright Gielen Julien
#ifndef __PLAYER_H__
#define __PLAYER_H__


//structure to define the position of the object
typedef struct Position{
    int x;
    int y;
} coordinates;

//structure to define the player
typedef struct Player{
    coordinates position;
    int lives;
    int score;
} player;

void jump(int x, int y,char **map,player *player_ptr,float *scrolling);//jump with the direction x,y
void collision(int x, char **map,player *player_ptr,float *scrolling);//causes a rejection of the player if collison with an ennemy, x is the direction
void move(int x,int y,char **map,player* player_ptr,float *scrolling); //check the next position and takes the actions necessary. -1<x<1 and -1<y<1.
void gravity(char **map,player *player_ptr,float *scrolling); //check the gravity, on a timer.

#endif