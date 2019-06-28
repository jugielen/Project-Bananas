//copyright Gielen Julien
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

void jump(int x, int y, char **map,player *player_ptr,float *scrolling){
    move(0,y,map,player_ptr,scrolling);
    move(0,y,map,player_ptr,scrolling);
    move(x,y,map,player_ptr,scrolling);
    move(x,y,map,player_ptr,scrolling);
    move(x,y,map,player_ptr,scrolling);
}

void collision(int x,char **map,player *player_ptr,float *scrolling){
    player_ptr->lives-=1;
    if (x==0){
        x=1; //give a default direction
    }
    move(-x,-1,map,player_ptr,scrolling);
    move(-x,0,map,player_ptr,scrolling);
    move(-x,-1,map,player_ptr,scrolling);
    move(-x,0,map,player_ptr,scrolling);
    move(-x,0,map,player_ptr,scrolling);
}

void move(int x,int y, char **map,player *player_ptr,float *scrolling){ //move toward x,y and check for collision with another object
    if ((player_ptr->position.x+x>=0)&&(player_ptr->position.y+y>=0)){ //check if next position is in map
        switch (map[player_ptr->position.y+y][player_ptr->position.x+x]){ //check if object is in the next position
            case ' '://update map and position if next position is empty
                map[player_ptr->position.y][player_ptr->position.x]=' ';
                player_ptr->position.x+=x;
                player_ptr->position.y+=y;
                map[player_ptr->position.y][player_ptr->position.x]='p';
            break;
            case '*': //update map, score and position if next position is a banana
                player_ptr->score+=10;
                map[player_ptr->position.y][player_ptr->position.x]=' ';
                player_ptr->position.x+=x;
                player_ptr->position.y+=y;
                map[player_ptr->position.y][player_ptr->position.x]='p'; 
            break;
            case 's'://launch the fct collision is next position is a ennemy
                collision(x,map,player_ptr,scrolling); 
            break;
        }
        if(player_ptr->position.y>10&&player_ptr->position.y<50){
            *scrolling=player_ptr->position.y-9;
        }
        else if(player_ptr->position.y<=10){
            *scrolling=0;
        }
        
    
    }
    glutPostRedisplay();
}

void gravity(char **map, player *player_ptr,float *scrolling){ //check if player is in the air, move toward the ground if so.    
    if (map[player_ptr->position.y+1][player_ptr->position.x]!='w'){
        move(0,1,map,player_ptr,scrolling);
    }
}