//copyright Gielen Julien
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "screens.h"


void first_screen(int width, int height,int difficulty){ 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   
    const unsigned char title[MAX_CH]="Jumping Bananas!";
    glColor3ub(255,255,0);//color of the text in RGB, to be used before glrasterpos
    glRasterPos2f(width/3.0,100);//set the positon of the text
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,title);//dispaly text in string
    glColor3ub(0,255,120);
    const unsigned char string[MAX_CH]="To see the controls, press c.\nTo see the rules, press r.\nTo change difficulty, press d.\nTo start playing, press Enter.\nTo quit, press Escape.";
    glRasterPos2f(width/4.0,250.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
    const unsigned char diff[MAX_CH]="Difficulty : ";
    glRasterPos2f(width/4.0,400.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,diff);
    if (difficulty==0){
            const unsigned char easy[MAX_CH]="Easy";
            glutBitmapString(GLUT_BITMAP_HELVETICA_18,easy);
    }
    else if(difficulty==1){
            const unsigned char normal[MAX_CH]="Normal";
            glutBitmapString(GLUT_BITMAP_HELVETICA_18,normal);
    }
    else{
            const unsigned char difficult[MAX_CH]="Difficult";
            glutBitmapString(GLUT_BITMAP_HELVETICA_18,difficult);
    }
}

void show_controls(int width, int height){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const unsigned char title[MAX_CH]="Jumping Bananas! - Controls";
    glColor3ub(255,255,0);//color of the text in RGB, to be used before glrasterpos
    glRasterPos2f(width/4.0,100);//set the positon of the text
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,title);//dispaly text in string
    glColor3ub(0,255,120);
    const unsigned char string[MAX_CH]="- Left/right arrow: move left/right\n- Space bar : jump\n- E : shoot laser\n\nTo see the rules, press r.\nTo start playing, press Enter.\nTo quit, press Escape.";
    glRasterPos2f(width/4.0,250.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
}

void show_rules(int width, int height){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const unsigned char title[MAX_CH]="Jumping Bananas! - Rules";
    glColor3ub(255,255,0);//color of the text in RGB, to be used before glrasterpos
    glRasterPos2f(width/4.0,100);//set the positon of the text
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,title);//dispaly text in string
    glColor3ub(0,255,120);
    const unsigned char string[MAX_CH]="Catch the bananas and kill all the ennemies!\nYou get 10 points per bananas and \n25 points if you kill an ennemy.\n\nTo see the controls, press c.\nTo start playing, press Enter.\nTo quit, press Escape.";
    glRasterPos2f(width/4.0,250.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
}

void game_over(int width, int height, int score){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const unsigned char title[MAX_CH]="Jumping Bananas! - Game Over";
    glColor3ub(255,255,0);//color of the text in RGB, to be used before glrasterpos
    glRasterPos2f(width/4.0,100);//set the positon of the text
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,title);//dispaly text in string
    glColor3ub(0,255,120);
    const unsigned char string[MAX_CH]="Your score : ";
    const unsigned char string_score[MAX_CH];
    sprintf((char *)string_score,"%d",score);
    glRasterPos2f(width/3.0,250.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string_score);
}

void player_win (int width, int height, int score){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    const unsigned char title[MAX_CH]="Jumping Bananas! - Victory !";
    glColor3ub(255,255,0);//color of the text in RGB, to be used before glrasterpos
    glRasterPos2f(width/4.0,100);//set the positon of the text
    glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,title);//dispaly text in string
    glColor3ub(0,255,120);
    const unsigned char string[MAX_CH]="Your score : ";
    const unsigned char string_score[MAX_CH];
    sprintf((char *)string_score,"%d",score);
    glRasterPos2f(width/3.0,250.0);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,string_score);
}
