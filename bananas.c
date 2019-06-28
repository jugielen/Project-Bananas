//copyright Gielen Julien
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include "maps.h"
#include "bananas.h"
#include "player.h"
#include "ennemies.h"
#include "screens.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void screens(void){
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	switch(menu_action){
        case 0:
            first_screen(items_x*ITEMS_SIZE,items_y*ITEMS_SIZE,map_ptr->difficulty);
        break;
        case 1:
            show_controls(items_x*ITEMS_SIZE,items_y*ITEMS_SIZE);
        break;
        case 2:
            show_rules(items_x*ITEMS_SIZE,items_y*ITEMS_SIZE);
        break;
        case 3:
            if (!game_started){
                load_map(items_x,items_y,map_ptr);
                map_ptr->map[player_ptr->position.y][player_ptr->position.x]='p';
                create_ennemies(map_ptr->map,items_x,items_y);
                game_started=true;
            }
            display_map(items_x,items_y,map_ptr->map,player_ptr->score,player_ptr->lives,map_ptr->scrolling);//display object based of the map[][]         
        break;
        case 4:
            game_over(items_x*ITEMS_SIZE,items_y*ITEMS_SIZE,player_ptr->score);
        break;
        case 5:
            player_win(items_x*ITEMS_SIZE,items_y*ITEMS_SIZE,player_ptr->score);
        break;
        case 6:
            if (map_ptr->difficulty==2){
                map_ptr->difficulty=0;
            }
            else{
                map_ptr->difficulty++;
            }
            menu_action=0;
        break;
    }
    glFlush();
    glutPostRedisplay();
}



void start_game(void){     
    glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    screens();
}

void create_player(){
    player_ptr=malloc(sizeof(player));
    player_ptr->position.x=36;
    player_ptr->position.y=0;
    player_ptr->lives=3;
    player_ptr->score=0;
}

void init_game(int *width, int *height){
    items_x=ITEMS, items_y=ITEMS*2;
    key_ptr=malloc(4*sizeof(bool));
    int i;
    for (i=0;i<4;i++){
        key_ptr[i]=false;
    } 
    map_ptr=malloc(sizeof(Maps));
    map_ptr->difficulty=0;
    map_ptr->scrolling=0;
    create_player(); 
    ennemies_ptr=NULL;
    lasers_ptr=NULL; 
    menu_action=0;
    game_started=false;
    init_map(items_x,items_y,map_ptr);
    *width=ITEMS*ITEMS_SIZE;
    *height=ITEMS*ITEMS_SIZE;
}

void controls(bool *key_ptr){ //bool is true if a key is pressed
    int x=0,y=0;
    if(key_ptr[0]){ //left arrow 
        x=-1;
    }
    if(key_ptr[1]){ //right arrow
        x=1;
    }
    if (key_ptr[2]&&map_ptr->map[player_ptr->position.y+1][player_ptr->position.x]=='w'){ //space bar
        y=-1;
        jump(x,y,map_ptr->map,player_ptr,&(map_ptr->scrolling));
    }
        move(x,0,map_ptr->map,player_ptr,&(map_ptr->scrolling));
    if (key_ptr[3]){ // 'e' - shootlaser
        int direction=1;
        if(key_ptr[0]){  //specified the direction of the laser depending on the arrow pressed.
            direction=-1;
        }
        add_laser(player_ptr->position.x+direction,player_ptr->position.y,direction); //add a laser to the list
        map_ptr->map[player_ptr->position.y][player_ptr->position.x+direction]='l'; //add laser on the map
    }
    glutPostRedisplay();
}



    
void on_timer(int n){
    if (game_started){//check which key is pressed
        controls(key_ptr);
        gravity(map_ptr->map,player_ptr,&(map_ptr->scrolling));//check for gravity
        if (player_ptr->lives<=0){
            menu_action=4;
        }
        if (ennemies_ptr==NULL){
            menu_action=5;
        }
    }
    if (ennemies_ptr!=NULL){ //move the ennemies if there are any
        bool player_hit=move_ennemy(map_ptr->map,&(player_ptr->score));
        if (player_hit){ //launch the collision function if the player is hit by an ennemy
         collision(0,map_ptr->map,player_ptr,&(map_ptr->scrolling));
        }
    }
    if (lasers_ptr!=NULL){
    move_laser(map_ptr->map,&(player_ptr->score),items_x); //move the lasers if there are any
    }

    glutTimerFunc(75,on_timer,0);
}


void key_down(unsigned char key, int mouse0, int mouse1){
    switch(key){
        case ' ':
            key_ptr[2]=true;
        break;
        case 27: //escape - close program
            if (menu_action!=3){
                exit(0);
                free(map_ptr);
                free(player_ptr);
            }
            else{
                menu_action=4;
            }
        break;
        case 'e':
            key_ptr[3]=true;
        break;
        case 'c':
            if (menu_action!=3){
                menu_action=1;
            }
        break;
        case 'r':
            if (menu_action!=3){
                menu_action=2;
            }
        break;
        case 13: //enter - start game
            if (menu_action<3){
                menu_action=3;
            }
        break;
        case 'd':
            if (menu_action==0){
                menu_action=6;
            }
    }
}


void key_up(unsigned char key, int mouse0, int mouse1){
    switch(key){
        case ' ':
            key_ptr[2]=false;
        break;
        case 'e':
            key_ptr[3]=false;
        break;
    }
}

void spec_key_down(int spec_key, int mouse0, int mouse1){
     switch(spec_key){
        case GLUT_KEY_LEFT:
            key_ptr[0]=true;
        break;
        case GLUT_KEY_RIGHT:
            key_ptr[1]=true;
        break;
    }
}

void spec_key_up(int spec_key, int mouse0, int mouse1){
     switch(spec_key){
        case GLUT_KEY_LEFT:
            key_ptr[0]=false;
        break;
        case GLUT_KEY_RIGHT:
            key_ptr[1]=false;
        break;
    }
}
