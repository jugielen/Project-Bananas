//copyright Gielen Julien
#ifdef __APPLE_CC__
#include <OpenGL/OpenGL.h>
#include <GLUT/freeglut.h>
#else
#include <GL/freeglut.h>
#endif
#include "bananas.h"
#include <stdio.h>
#include <stdlib.h>

void handleResize(int width,int heigth){
	glViewport(0, 0, width, heigth);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, heigth, 0);
}


int main(int argc, char *argv[]){
    int width, height;
    init_game(&width,&height); //initialize the game before entering the glut loop.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA); 
    glutInitWindowSize(width,height);  
    glutCreateWindow("Jumping Bananas");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(start_game);
    glutKeyboardFunc(key_down);
    glutKeyboardUpFunc(key_up);
    glutSpecialFunc(spec_key_down);
    glutSpecialUpFunc(spec_key_up);
    glutTimerFunc(50,on_timer,0);
    glutReshapeFunc(handleResize);
    glutMainLoop();
return 0;

}