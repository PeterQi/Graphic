#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_HEIGHT 700
#define WINDOW_WIDTH 500
#include "ordered_edge_table_algorithm.h"


int count = 0;
GLubyte*pPixelData;
void move(GLubyte *pPixelData, int dx, int dy)
{
	int start_y, start_x, end_y, end_x;
	if (dx > 0)
	{
		start_x = dx * 4;
		end_x = WINDOW_HEIGHT
	}
	else
	{
		start_x = 0;
	}
	int start_y = (dy > 0 ? dy : 0);	
	int end_y = (dy > 0 ? WINDOW_HEIGHT : WINDOW_HEIGHT + dy);
	int end_x = (dx > 0 ? WINDOW_WIDTH * 4 : (WINDOW_WIDTH + dx) * 4);
	for (int i = dy; i < WINDOW_HEIGHT + dy; i++)
	{
		for (int j = dx; j < WINDOW_WIDTH * 4 + dx * 4; j++)
		{
			if (i < start_y || j < start_x || i >=end_y || j >= end_x)
				pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = 0;
			else
				pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = pPixelData[i * WINDOW_WIDTH * 4 + j];
		}
	}
}
void myMouse(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (count <= 0)
		{
			count = 0;
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_POLYGON);
			glVertex2i(x, WINDOW_HEIGHT - y);
			count++;
		}
		else if (count > 0)
		{
			glVertex2i(x, WINDOW_HEIGHT - y);
			count++;
		}
		
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (count >= 0)
		{
			glEnd();
			glFlush();
			count = -1;
		}
		else 
		{
			//glClear(GL_COLOR_BUFFER_BIT);
			printf("%d\n", count);
			glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);
			move(pPixelData, -100, -100);
			//glClear(GL_COLOR_BUFFER_BIT);

			glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);

			glutSwapBuffers();
			//glFlush();
		}
	}
}

void display()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	//glBegin(GL_POLYGON);
}
void Drawing()
{
	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(200, 100);
	glVertex2i(200, 300);
	glEnd();

	//glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2i(100, 100);
	glVertex2i(300, 300);
	glVertex2i(100, 300);
	glVertex2i(300, 100);
	glEnd();
	glFlush();
}

void myDisplay(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
	
	display();
	//Drawing();

	
}


void onReshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


int main(int argc, char *argv[])
{
	pPixelData = (GLubyte*)new GLubyte[WINDOW_WIDTH*WINDOW_HEIGHT * 10];
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(700, 200);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("First GLUT Sample");
	
    glutDisplayFunc(&myDisplay);
	//glutDisplayFunc(&renderScene);
	glutMouseFunc(myMouse);
	
	glutReshapeFunc(onReshape);
    glutMainLoop();
    return 0;
}