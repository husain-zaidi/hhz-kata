#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
using namespace std;

bool movingUp = false; // Whether or not we are moving up or down  
float yLocation = 0.0f;

void renderRectangle(void){
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f, 0.0f); // The bottom left corner  
        glVertex3f(-1.0f, 1.0f, 0.0f); // The top left corner  
        glVertex3f(1.0f, 1.0f, 0.0f); // The top right corner  
        
        glVertex3f(1.0f, -1.0f, 0.0f); // The bottom right corner  
    glEnd();
}

void display(void){
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glTranslatef(0.0f, yLocation, 0.0f);
    glRotatef(62.0f, 0.0f, 1.0f, 0.0f);
    renderRectangle();
    glFlush();

    if(movingUp)
        yLocation -= 0.005f;
    else
        yLocation += 0.005f;

    if(yLocation < -3.0f)
        movingUp = false;
    else if(yLocation > 3.0f)
        movingUp = true;
}

void reshape(int width, int height){
    glViewport(0,0,(GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (GLfloat)width/(GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("CO-315 Assignment");
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
