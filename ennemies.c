//copyright Gielen Julien
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ennemies.h"
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif

int ennemy_progress(void){ //define the move based on the current position
    int move_y;
    int progress;
    switch (ennemy_jump){
        case 0:
            move_y=-1;
            progress=1;
        break;
        case 1:
            move_y=-1;
            progress=2;
        break;
        case 2:
            move_y=1;
            progress=3;
        break;
        case 3:
            move_y=1;
            progress=0;
        break;

    }
    ennemy_jump=progress;
return move_y;
}

bool move_ennemy(char **map, int *score){ //update the map with ennemies' moves
    int move_y=ennemy_progress();
    bool hit=false;
    ennemy *temp_ptr=ennemies_ptr;
    do{
        switch (map[temp_ptr->position_y+move_y][temp_ptr->position_x]){
            case ' ':
                map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                map[temp_ptr->position_y+move_y][temp_ptr->position_x]='s';
                temp_ptr->position_y+=move_y;
            break;
            case 'l':
                map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                map[temp_ptr->position_y+move_y][temp_ptr->position_x]=' ';
                laser *laser_hit_ptr=look_for_laser(temp_ptr->position_x,temp_ptr->position_y+move_y);//look for the laser who was hit
                remove_laser(laser_hit_ptr);//remove laser from the list
                temp_ptr=temp_ptr->previous_ptr;        //update the temp pointer
                remove_ennemy(temp_ptr->next_ptr); //remove the killed ennemy from the list
                *score+=25; //update the score
            break;
            case 'p':
                map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                map[temp_ptr->position_y+move_y][temp_ptr->position_x]='s';
                temp_ptr->position_y+=move_y;
                hit=true; //bool true if ennemy hit the player
            break;
        }
        if (ennemies_ptr==NULL){ //upadte the temp pointer if no more ennmies in the list
            temp_ptr=NULL;
        }
        else{
            temp_ptr=temp_ptr->next_ptr; //update the pointer to the next one from the list
        }
    } while (temp_ptr!=ennemies_ptr); //loop until we have gone full circle
    glutPostRedisplay();
    return hit;
}

ennemy *look_for_ennemy(int x, int y){
    ennemy *temp_ptr=ennemies_ptr;
    while (temp_ptr->position_x!=x && temp_ptr->position_y!=y){ //look for the ennemy with the specified coordinates
        temp_ptr=temp_ptr->next_ptr;
    }
    return temp_ptr; //return the pointer to the ennemy
}


void remove_ennemy(ennemy *ennemy_killed){
    ennemy_killed->previous_ptr->next_ptr=ennemy_killed->next_ptr; //update the previous ptr
    ennemy_killed->next_ptr->previous_ptr=ennemy_killed->previous_ptr; //update the next ptr
    if (ennemy_killed==ennemies_ptr){
        ennemies_ptr=ennemy_killed->next_ptr;//update the external pointeur if we remove the first element
    }
    if (ennemy_killed->next_ptr==ennemy_killed){//if all ennemies are killed
        ennemies_ptr=NULL;
    }
    free(ennemy_killed); //free the memory
}


void add_ennemy(int x,int y){
    if (ennemies_ptr==NULL){ //if we add the first element
        ennemies_ptr=malloc(sizeof(ennemy));
        ennemies_ptr->previous_ptr=ennemies_ptr;
        ennemies_ptr->next_ptr=ennemies_ptr;
        ennemies_ptr->position_x=x;
        ennemies_ptr->position_y=y;
    }
    else{
        ennemy *temp_ptr;
        temp_ptr=ennemies_ptr->previous_ptr;
        ennemies_ptr->previous_ptr=malloc(sizeof(ennemy));
        ennemies_ptr->previous_ptr->next_ptr=ennemies_ptr;
        ennemies_ptr->previous_ptr->previous_ptr=temp_ptr;
        ennemies_ptr->previous_ptr->position_x=x;
        ennemies_ptr->previous_ptr->position_y=y;
        ennemies_ptr->previous_ptr->previous_ptr->next_ptr=ennemies_ptr->previous_ptr;
    }
    

}

void create_ennemies(char **map, int max_x, int max_y){ //create the ennemy list based on the map
    ennemies_ptr=NULL;
    ennemy_jump=0;
    int i,j;
    for(i=0;i<max_y;i++){
        for(j=0;j<max_x;j++){
            if (map[i][j]=='s'){
                add_ennemy(j,i); //add ennemy to the list with the position i,j
            }
        }
    }
}

void add_laser(int x,int y, int direction){
    if (lasers_ptr==NULL){ //if we add the first element
        lasers_ptr=malloc(sizeof(laser));
        lasers_ptr->previous_ptr=lasers_ptr;
    }
    else{
        laser *temp_ptr;
        temp_ptr=lasers_ptr->previous_ptr;
        lasers_ptr->previous_ptr=malloc(sizeof(laser));
        lasers_ptr->previous_ptr->previous_ptr=temp_ptr; //update the addedd laser with pointer to the previous laser
        lasers_ptr->previous_ptr->previous_ptr->next_ptr=lasers_ptr->previous_ptr; //update the previous laser from the added laser
    }
    lasers_ptr->previous_ptr->next_ptr=lasers_ptr; //update the added laser
    lasers_ptr->previous_ptr->position_x=x; //pos x from the added laser
    lasers_ptr->previous_ptr->position_y=y; // pos y from the added laser
    lasers_ptr->previous_ptr->duration=10; // duration from the added laser
    lasers_ptr->previous_ptr->direction=direction; // direction of the added laser

}

void remove_laser(laser *laser_terminated){
    laser_terminated->previous_ptr->next_ptr=laser_terminated->next_ptr; //update the previous ptr
    laser_terminated->next_ptr->previous_ptr=laser_terminated->previous_ptr; //update the next ptr
    if (laser_terminated==lasers_ptr){
        lasers_ptr=laser_terminated->next_ptr;//update the external pointeur if we remove the first element
    }
    if (laser_terminated->next_ptr==laser_terminated){//if all lasers are terminated
        lasers_ptr=NULL;
    }
    free(laser_terminated);
}

laser *look_for_laser(int x, int y){
    laser *temp_ptr=lasers_ptr;
    while (temp_ptr->position_x!=x && temp_ptr->position_y!=y){ //look for the ennemy with the specified coordinates
        temp_ptr=temp_ptr->next_ptr;
    }
    return temp_ptr;
}

void move_laser(char **map, int *score, int max_x){
    laser *temp_ptr=lasers_ptr;
    do{
        if(temp_ptr->position_x+temp_ptr->direction>=0&&temp_ptr->position_x+temp_ptr->direction<max_x){
            switch (map[temp_ptr->position_y][temp_ptr->position_x+temp_ptr->direction]){
                case ' ':
                    map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                    map[temp_ptr->position_y][temp_ptr->position_x+temp_ptr->direction]='l';
                    temp_ptr->position_x+=temp_ptr->direction;
                break;
                case 's':
                    map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                    map[temp_ptr->position_y][temp_ptr->position_x+temp_ptr->direction]=' ';
                    ennemy *ennemy_hit=look_for_ennemy(temp_ptr->position_x+temp_ptr->direction,temp_ptr->position_y);
                    remove_ennemy(ennemy_hit);                
                    temp_ptr=temp_ptr->previous_ptr;
                    remove_laser(temp_ptr->next_ptr);
                    *score+=25;
                break;
                case '*':
                    if(map[temp_ptr->position_y][temp_ptr->position_x]=='l'){
                        map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                    }
                    temp_ptr->position_x+=temp_ptr->direction;
                break;
                case 'w':
                    map[temp_ptr->position_y][temp_ptr->position_x]=' ';
                    temp_ptr=temp_ptr->previous_ptr;
                    remove_laser(temp_ptr->next_ptr);
                break;
            }
        temp_ptr->duration-=1; //decrease the remaining duration of the laser
        }
        else{
            temp_ptr->duration=0; //if laser outside of the map, duration is zero
        }
        if (temp_ptr->duration==0){ //if duration is zero, terminate the laser
            map[temp_ptr->position_y][temp_ptr->position_x]=' ';
            temp_ptr=temp_ptr->previous_ptr;
            remove_laser(temp_ptr->next_ptr);
        }
        if (lasers_ptr==NULL){ //if no more laser in the list, update the temp pointer
            temp_ptr=NULL;
        }
        else{
            temp_ptr=temp_ptr->next_ptr;
        }
    } while (temp_ptr!=lasers_ptr);
    glutPostRedisplay();
}