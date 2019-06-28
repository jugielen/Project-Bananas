//copyright Gielen Julien
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif
#include "maps.h"


void init_map(int max_x, int max_y,Maps *my){
    int i=0,j=0;
    my->map=malloc(max_y*sizeof(int *)); 
    for(i=0;i<max_y;i++){
            my->map[i]=malloc(max_x*sizeof(char)); 
                for(j=0;j<max_x;j++){
                    my->map[i][j]=' '; //each element of the map is empty (caracter ' ' )
                }
    }
}



void load_map(int max_x, int max_y,Maps *my){
    init_map(max_x,max_y,my);
	char c;
    int i=0,j=0;
	FILE *fichier = NULL;
    switch(my->difficulty){
        case 0:
            fichier = fopen("map0.txt", "r");
        break;
        case 1:
            fichier = fopen("map1.txt", "r");
        break;
        case 2:
            fichier = fopen("map2.txt", "r");
        break;
    }
	if(fichier ==NULL)
	{
		printf ("file empty");
	}
	
    c=fgetc(fichier);
	while (i<max_y){
		 if(c=='\n'||j==max_x){
				 i++;
 				j = 0;
 		}
			 
		else{ 
			my->map[i][j]=c;
			j++;
		}
        c=fgetc(fichier);
	}
    fclose(fichier);

}

void display_score_lives(int score,int lives){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3ub(0,255,120);
    const unsigned char string[20]="Your score : ";
    const unsigned char string_score[20];
    const unsigned char string2[20]="Your lives : ";
    const unsigned char string_lives[20];
    sprintf((char *)string_score,"%d",score);
    glRasterPos2f(10.0,20.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string_score);
    sprintf((char *)string_lives,"%d",lives);
    glRasterPos2f(150.0,20.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string2);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string_lives);
}


void display_map(int max_x, int max_y,char **map,int score,int lives,float move_up){
    int i,j;
    for(i=0;i<max_y;i++){
        for(j=0;j<max_x;j++){
            switch(map[i][j]){ //check each element of the map
                case 'w': //draw a wall/platform
                    glColor3ub(120,250,0);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glTranslatef(j*ITEMS_SIZE,(i-move_up)*ITEMS_SIZE,0.0f);
                    glBegin(GL_QUADS);
                    glVertex3f(0.0f, 0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE, 0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE/2, 0.0f);
                    glVertex3f(0.0f,ITEMS_SIZE/2, 0.0f);
                    glEnd();
                    glColor3ub(165,42,42);
                    glBegin(GL_QUADS);
                    glVertex3f(0.0f, ITEMS_SIZE/2, 0.0f);
                    glVertex3f(ITEMS_SIZE, ITEMS_SIZE/2, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE, 0.0f);
                    glVertex3f(0.0f,ITEMS_SIZE, 0.0f);
                    glEnd();
                break;
    
                case '*': //draw a banana
                    glColor3ub(255,255,51);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glTranslatef(j*ITEMS_SIZE,(i-move_up)*ITEMS_SIZE,0.0f);
                    glBegin(GL_QUADS);
                    glVertex3f(ITEMS_SIZE/4, 0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE/2, 0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE/2,ITEMS_SIZE, 0.0f);
                    glVertex3f(ITEMS_SIZE/4,ITEMS_SIZE, 0.0f);
                    glEnd();
                break;

                case 's': //draw a snake
                    glColor3ub(0,250,125);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glTranslatef(j*ITEMS_SIZE,(i-move_up)*ITEMS_SIZE,0.0f);
                    glBegin(GL_TRIANGLES);
                    glVertex3f(0.0f, ITEMS_SIZE/2 , 0.0f);
                    glVertex3f(ITEMS_SIZE, ITEMS_SIZE/2, 0.0f);
                    glVertex3f(ITEMS_SIZE/2,ITEMS_SIZE, 0.0f);
                    glEnd();
                    glBegin(GL_TRIANGLES);
                    glVertex3f(0.0f, ITEMS_SIZE/2, 0.0f);
                    glVertex3f(ITEMS_SIZE/2,0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE/2, 0.0f);
                    glEnd();
                break;

                case 'p': //draw a player
                    glColor3ub(210,180,140);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glTranslatef(j*ITEMS_SIZE,(i-move_up)*ITEMS_SIZE,0.0f);
                    glBegin(GL_TRIANGLES);
                    glVertex3f(0.0f, ITEMS_SIZE, 0.0f);
                    glVertex3f(ITEMS_SIZE/2,0.0f, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE, 0.0f);
                    glEnd();
                break;
                case 'l': //draw a laser
                    glColor3ub(0,0,250);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glTranslatef(j*ITEMS_SIZE,(i-move_up)*ITEMS_SIZE,0.0f);
                    glBegin(GL_QUADS);
                    glVertex3f(0.0f,ITEMS_SIZE/2, 0.0f);
                    glVertex3f(0.0f,ITEMS_SIZE/4, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE/2, 0.0f);
                    glVertex3f(ITEMS_SIZE,ITEMS_SIZE/4, 0.0f);
                    glEnd();
                break;
            }
        }
    }
    display_score_lives(score,lives);
}

