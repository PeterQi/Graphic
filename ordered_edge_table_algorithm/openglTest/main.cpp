#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_HEIGHT 500
#define SEGMENT_NUM 20

class NET
{
public:
	double inter_x;
	double dx;
	int ymax;
	NET* next;
	NET()
	{
		next = NULL;
	}
};
NET *nets[WINDOW_HEIGHT];
NET *aet;
class segments
{
public:
	double A, B, C;
	int Ly, Hy;
	segments()
	{
		return;
	}
	void setSegments(int x1, int x2, int y1, int y2)
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
}//²âÊÔ´úÂë


/*void QuickSortLy(int start, int end)
{
	if (start >= end)
	{
		return; 
	}
	int i = start;
	int j = end;
	int start_index = Ly_line[start];
	int key = seg[Ly_line[start]].Ly;
	while (i < j)
	{
		while (seg[Ly_line[j]].Ly >= key && i < j)j--;
		Ly_line[i] = Ly_line[j];
		while (seg[Ly_line[i]].Ly <= key && i < j)i++;
		Ly_line[j] = Ly_line[i];

	}
	Ly_line[i] = start_index;
	QuickSortLy(start, i-1);
	QuickSortLy(i + 1, end);
}

void QuickSortHy(int start, int end)
{
	if (start >= end)
	{
		return;
	}
	int i = start;
	int j = end;
	int start_index = Hy_line[start];
	int key = seg[Hy_line[start]].Hy;
	while (i < j)
	{
		while (seg[Hy_line[j]].Hy >= key && i < j)j--;
		Hy_line[i] = Hy_line[j];
		while (seg[Hy_line[i]].Hy <= key && i < j)i++;
		Hy_line[j] = Hy_line[i];

	}
	Hy_line[i] = start_index;
	QuickSortHy(start, i-1);
	QuickSortHy(i + 1, end);
}*/
int first_x, first_y;
void myMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		glVertex2i(x, WINDOW_HEIGHT - y);
		if (num > 0)
		{
			seg[num-1].setSegments(Last_x, x, Last_y, WINDOW_HEIGHT - y);
		}
		else
		{
			first_x = x;
			first_y = WINDOW_HEIGHT - y;
		}

		Last_x = x;
		Last_y = WINDOW_HEIGHT - y;
		num++;
		//printf("%d,%d\n", x, y);
	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		glEnd();
		glFlush();
		for (int i = 0; i < WINDOW_HEIGHT; i++)
			nets[i] = NULL;
		seg[num - 1].setSegments(Last_x, first_x, Last_y, first_y);
		//QuickSortLy(0, num - 1);
		//QuickSortHy(0, num - 1);
		int lowest_y = WINDOW_HEIGHT;
		int highest_y = 0;
		for (int i = 0; i < num; i++)
		{
			if (seg[i].Ly == seg[i].Hy)continue;
			if (seg[i].Ly < lowest_y) lowest_y = seg[i].Ly;
			if (seg[i].Hy > highest_y) highest_y = seg[i].Hy;
			NET *tmp = nets[seg[i].Ly];
			if (nets[seg[i].Ly] == NULL)
			{
				nets[seg[i].Ly] = new NET();
				nets[seg[i].Ly]->inter_x = seg[i].intersection(seg[i].Ly);
				nets[seg[i].Ly]->dx = -seg[i].B / seg[i].A;
				nets[seg[i].Ly]->ymax = seg[i].Hy;
			}
			else
			{
				while (nets[seg[i].Ly]->next != NULL) nets[seg[i].Ly] = nets[seg[i].Ly]->next;
				nets[seg[i].Ly]->next = new NET();
				nets[seg[i].Ly]->next->inter_x = seg[i].intersection(seg[i].Ly);
				nets[seg[i].Ly]->next->dx = -seg[i].B / seg[i].A;
				nets[seg[i].Ly]->next->ymax = seg[i].Hy;
				nets[seg[i].Ly] = tmp;
			}
		}
		aet = nets[lowest_y];
		for (int i = lowest_y; i < highest_y; i++)
		{
			NET *start = aet;

			int xx[SEGMENT_NUM];
			int tmp_num = 0;
			if (aet != NULL)
			while (aet->next != NULL)
			{
				if (i >= aet->next->ymax)
				{
					aet->next = aet->next->next;
				}
				else
				{
					aet->next->inter_x += aet->next->dx;
				}
				aet = aet->next;
				if (aet == NULL) break;
			}
			aet = start;
			
			if (i >= aet->ymax)
			{
				aet = aet->next;
			}
			else
			{
				aet->inter_x += aet->dx;
			}
			start = aet;
			if (i > lowest_y)
			{
				if (aet != NULL)
				{
					while (aet->next != NULL) aet = aet->next;
					aet->next = nets[i];
				}
				else
				{
					aet = nets[i];
				}
			}
			aet = start;
			NET *tmp = aet;
			while (tmp != NULL)
			{
				xx[tmp_num] = tmp->inter_x;
				tmp_num++;
				tmp = tmp->next;
			}
			for (int p = 0; p < tmp_num; p++)
			{
				for (int q = tmp_num - 1; q > p; q--)
				{
					if (xx[q] < xx[q - 1])
					{
						int tmp_int = xx[q];
						xx[q] = xx[q - 1];
						xx[q - 1] = tmp_int;
					}
				}
			}
			for (int p = 1; p < tmp_num; p += 2)
			{
				
				glBegin(GL_LINES);
				glVertex2i(xx[p], i);
				glVertex2i(xx[p - 1], i);
				glEnd();
				glFlush();
			}

		}

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
	glClear(GL_COLOR_BUFFER_BIT);
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
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(700, 200);
    glutInitWindowSize(500, WINDOW_HEIGHT);
    glutCreateWindow("First GLUT Sample");
	
    glutDisplayFunc(&myDisplay);
	//glutDisplayFunc(&renderScene);
	glutMouseFunc(myMouse);
	
	glutReshapeFunc(onReshape);
    glutMainLoop();
    return 0;
}