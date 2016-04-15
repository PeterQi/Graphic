#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <ctime>
#include "config.h"
#include "ordered_edge_table_algorithm.h"
#include "geometric_transform.h"
#include "L_system.h"
#include "Cohen-Sutherland.h"
segments seg[SEGMENT_NUM];
int Ly_line[SEGMENT_NUM], Hy_line[SEGMENT_NUM];
int first_x, first_y, Last_x, Last_y;
NET *nets[WINDOW_HEIGHT];
NET *aet;
Point pts[30];
int num = 0;
int count1 = 0;
GLubyte * pPixelData;
GLubyte * pNewData;
int algo_num = 0;
Segment segs[SEGMENT_NUM];
bool is_seg = true;
bool cutting = false;
Point2 recP[2];
int rec_num = 0;
void myMouse(int button, int state, int x, int y)
{
	if (algo_num == 0)
	{
		fill(button, state, x, y, seg, Ly_line, Hy_line, num, first_x, first_y, Last_x, Last_y, nets, aet);
	}
	else if(algo_num == 1)
	{
		transform(button, state, x, y, count1, num, pts);
	}
	else if (algo_num == 4)
	{
		Cohen_mouse(button, state, x, y, num, segs, is_seg, cutting, recP, rec_num);
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
		char tmpP[20];
		LS Koch;
		double angel = PI * 90 / 180;
		LS_state st(WINDOW_WIDTH/3, WINDOW_HEIGHT/2, 0);
		strcpy_s(tmpP, "F+F-F-FF+F+F-F");
		Koch.init_LS(angel, WINDOW_WIDTH/4, 4, "F-F-F-F", st, tmpP);
		while (Koch.n < 3)
		{
			Koch.ProcessP();
		}
		Koch.ProcessPaint();
	} 
	else if (algo_num == 3)
	{
		char tmpP[20];
		LS Koch;
		double angel = PI * 60 / 180;
		LS_state st(1,1,0);
		strcpy_s(tmpP, "F-F++F-F");
		Koch.init_LS(angel, WINDOW_WIDTH, 3, "F", st, tmpP);
		while (Koch.n < 5)
		{
			Koch.ProcessP();
		}
		Koch.ProcessPaint();
	}
	

}

void myDisplay(void)
{
	//glClear(GL_COLOR_BUFFER_BIT);
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
	std::cout << "***********************************" << endl
		<< "*1.ÓÐÐò±ß±íËã·¨                   *" << endl
		<< "*2.Í¼ÐÎ±ä»»                       *" << endl
		<< "*3.Kochµº(n=3)                    *" << endl
		<< "*4.KochÇúÏß(n=5)                  *" << endl
		<< "*5.Ïß¶Î²Ã¼ô                       *" << endl
		<< "***********************************" << endl
		<< "ÇëÊäÈëËã·¨ºÅ£º";
	std::cin >> algo_num;
	algo_num -= 1;
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