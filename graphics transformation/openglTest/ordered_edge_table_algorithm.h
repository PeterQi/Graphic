#pragma once


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
void fill(int button, int state, int x, int y, segments *seg, int *Ly_line, int *Hy_line, int &num, int &first_x, int &first_y,
	int &Last_x, int &Last_y, NET **nets, NET *aet)//直接放入myMouse
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		glVertex2i(x, WINDOW_HEIGHT - y);
		if (num > 0)
		{
			seg[num - 1].setSegments(Last_x, x, Last_y, WINDOW_HEIGHT - y);
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

		//printf("%d\n%d\n", lowest_y, highest_y);
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


/*
NET *nets[WINDOW_HEIGHT];
NET *aet;

segments seg[SEGMENT_NUM];
int Ly_line[SEGMENT_NUM];
int Hy_line[SEGMENT_NUM];
int num = 0;
int Last_x, Last_y;
int first_x, first_y;
*/
/*
void myMouse(int button, int state, int x, int y)
{
fill(button, state, x, y, seg, Ly_line, Hy_line, num, first_x, first_y, Last_x, Last_y, nets, aet);
}

void display()
{
//glClear(GL_COLOR_BUFFER_BIT);
glBegin(GL_LINE_LOOP);
}

void myDisplay(void)
{
glClear(GL_COLOR_BUFFER_BIT);
display();
//Drawing();
}*/

void init_fill(int *Ly_line, int *Hy_line)
{
	
	for (int i = 0; i < SEGMENT_NUM; i++)
	{
		Ly_line[i] = i;
		Hy_line[i] = i;
	}
}
