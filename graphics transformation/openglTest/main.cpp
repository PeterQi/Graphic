#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <ctime>
#include "config.h"
#include "ordered_edge_table_algorithm.h"
#include "geometric_transform.h"

segments seg[SEGMENT_NUM];
int Ly_line[SEGMENT_NUM], Hy_line[SEGMENT_NUM];
int first_x, first_y, Last_x, Last_y;
NET *nets[WINDOW_HEIGHT];
NET *aet;
Point pts[30];
int num = 0;
int count = 0;
GLubyte * pPixelData;
GLubyte * pNewData;
int algo_num = 0;
void myMouse(int button, int state, int x, int y)
{
	if (algo_num == 0)
	{
		fill(button, state, x, y, seg, Ly_line, Hy_line, num, first_x, first_y, Last_x, Last_y, nets, aet);
	}
	else if (algo_num == 1)
	{
		transform(button, state, x, y, count, num, pts);
	}
}

void display()
{
	if (algo_num == 0)
	{
		glBegin(GL_LINE_LOOP);
	}
	else if (algo_num == 2)
	{
		glRectf(-0.5, -0.5, 0.5, 0.5);
		glFlush();
	}

}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	display();
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
	init_fill(Ly_line, Hy_line);
	srand(unsigned(time(0)));
	random(0, 3);
	//std::cin >> algo_num;
	algo_num = 2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(700, 200);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("First GLUT Sample");
	
    glutDisplayFunc(&myDisplay);
	glutMouseFunc(myMouse);
	
	glutReshapeFunc(onReshape);
    glutMainLoop();
    return 0;
}