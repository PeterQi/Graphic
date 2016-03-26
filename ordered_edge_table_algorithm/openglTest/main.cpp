#include <GL/glut.h>
#include <stdio.h>
#define WINDOW_HEIGHT 500
#define SEGMENT_NUM 20

segments seg[SEGMENT_NUM];
int Ly_line[SEGMENT_NUM];
int Hy_line[SEGMENT_NUM];
int num = 0;
int Last_x, Last_y;

void renderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glBegin(GL_TRIANGLES);
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	glEnd();
	glutSwapBuffers();
}

class segments
{
public:
	double A, B, C;
	int Ly, Hy;
	segments(int x1, int x2, int y1, int y2)
	{
		A = y2 - y1;
		B = x1 - x2;
		C = x2*y1 - x1*y2;
		Ly = (y1 < y2) ? y1 : y2;
		Hy = (y1 > y2) ? y1 : y2;
	}
	int intersection(int y)
	{
		if (y > Hy || y < Ly)
		{
			return -1;
		}
		else if (Ly == Hy)
		{
			return -2;
		}
		else
		{
			double x = (-B*y - C) / A;
			return (int)x;
		}
	}
private:

};

void QuickSortLy(int start, int end)
{
	int i = start;
	int j = end;
	int key = seg[Ly_line[start]].Ly;
	while (i < j)
	{
		while (seg[Ly_line[j]].Ly>key && i < j)j--;
		Ly_line[i] = Ly_line[j];
		while (seg[Ly_line[i]].Ly < key && i < j)i++;
		Ly_line[j] = Ly_line[i];

	}

}
void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		glVertex2i(x, WINDOW_HEIGHT - y);
		if (num > 0)
		{
			seg[num](Last_x, Last_y, x, WINDOW_HEIGHT - y);
		}

		Last_x = x;
		Last_y = WINDOW_HEIGHT - y;
		num++;
		printf("%d,%d\n", x, y);
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		glEnd();
		glFlush();

		num = 0;

		for (int i = 0; i < SEGMENT_NUM; i++)
		{
			Ly_line[i] = i;
			Hy_line[i] = i;
		}

	}
}

void display()
{
	//glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_LOOP);
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
	for (int i = 0; i < SEGMENT_NUM; i++)
	{
		Ly_line[i] = i;
		Hy_line[i] = i;
	}
    glutInit(&argc, argv);;
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(500, 200);
    glutInitWindowSize(500, WINDOW_HEIGHT);
    glutCreateWindow("First GLUT Sample");
    glutDisplayFunc(&myDisplay);
	//glutDisplayFunc(&renderScene);
	glutMouseFunc(myMouse);
	
	glutReshapeFunc(onReshape);
    glutMainLoop();
    return 0;
}