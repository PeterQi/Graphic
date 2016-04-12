#pragma once

void move(GLubyte *pPixelData, int dx, int dy)
{
	int start_y, start_x, end_y, end_x;
	if (dx > 0)
	{
		start_x = dx * 4;
		end_x = WINDOW_WIDTH * 4;
	}
	else
	{
		start_x = 0;
		end_x = (WINDOW_WIDTH + dx) * 4;
	}
	if (dy > 0)
	{
		start_y = dy;
		end_y = WINDOW_HEIGHT;
	}
	else
	{
		start_y = 0;
		end_y = WINDOW_HEIGHT + dy;
	}
	if (dy > 0)
		for (int i = dy; i < WINDOW_HEIGHT + dy; i++)
		{
			if (dx > 0)
				for (int j = dx * 4; j < WINDOW_WIDTH * 4 + dx * 4; j++)
				{
					if (i < start_y || j < start_x || i >= end_y || j >= end_x)
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = 0;
					else
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = pPixelData[i * WINDOW_WIDTH * 4 + j];
				}
			else
				for (int j = WINDOW_WIDTH * 4 + dx * 4; j > dx * 4; j--)
				{
					if (i < start_y || j < start_x || i >= end_y || j >= end_x)
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = 0;
					else
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = pPixelData[i * WINDOW_WIDTH * 4 + j];
				}
		}
	else
		for (int i = WINDOW_HEIGHT + dy - 1; i >= dy; i--)
		{
			if (dx > 0)
				for (int j = dx * 4; j < WINDOW_WIDTH * 4 + dx * 4; j++)
				{
					if (i < start_y || j < start_x || i >= end_y || j >= end_x)
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = 0;
					else
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = pPixelData[i * WINDOW_WIDTH * 4 + j];
				}
			else
				for (int j = WINDOW_WIDTH * 4 + dx * 4 - 4; j >= dx * 4; j--)
				{
					if (i < start_y || j < start_x || i >= end_y || j >= end_x)
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = 0;
					else
						pPixelData[(i - dy)* WINDOW_WIDTH * 4 + j - dx * 4] = pPixelData[i * WINDOW_WIDTH * 4 + j];
				}
		}
}

int *move2(int x, int y, int dx, int dy)
{
	int *re = new int[2];
	re[0] = x + dx;
	re[1] = y + dy;
	return re;
}
int *rotate(int x, int y, double angel)
{
	int *re = new int[2];
	double c = cos(angel);
	double s = sin(angel);
	re[0] = int(x*c - y*s);
	re[1] = int(x*s + y*c);
	return re;
}
int *Scale(int x, int y, double sca)
{
	int *re = new int[2];
	re[0] = int(x*sca);
	re[1] = int(y*sca);
	return re;
}

void Changing(GLubyte *pPixelData, GLubyte *pNewData)
{
	int i, j;
	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++)
		{
			for (int p = 0; p < 4; p++)
				pNewData[i*WINDOW_WIDTH * 4 + j * 4 + p] = 0;
		}
	}
	printf("Changing...\n");
	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH * 4; j++)
		{
			int * tmp = new int[2];
			//tmp = move2(j, i, 50, -50);
			//tmp = rotate(j, i, PI / 180 * 3);
			tmp = Scale(j, i, 2);
			if (tmp[0]<0 || tmp[0] >= WINDOW_WIDTH * 4 || tmp[1]<0 || tmp[1] >= WINDOW_HEIGHT)
				continue;


			pNewData[tmp[1] * WINDOW_WIDTH * 4 + tmp[0]] = pPixelData[i*WINDOW_WIDTH * 4 + j];

		}
	}
	printf("Copying\n");
	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH * 4; j++)
		{
			pPixelData[i*WINDOW_WIDTH * 4 + j] = pNewData[i*WINDOW_WIDTH * 4 + j];
		}
	}
	printf("Done\n");
}
class Point
{
public:
	int x;
	int y;
};

void transform(int button, int state, int x, int y, int &count, int &num, Point *pts)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (count <= 0)
		{
			count = 0;
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_POLYGON);
			glVertex2i(x, WINDOW_HEIGHT - y);
			pts[count].x = x;
			pts[count].y = WINDOW_HEIGHT - y;
			count++;
		}
		else if (count > 0)
		{
			glVertex2i(x, WINDOW_HEIGHT - y);
			pts[count].x = x;
			pts[count].y = WINDOW_HEIGHT - y;
			count++;
		}

	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		if (count >= 0)
		{
			glEnd();
			glFlush();
			num = count;
			count = -1;

		}
		else
		{
			glClear(GL_COLOR_BUFFER_BIT);
			/*glReadPixels(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);
			//move(pPixelData, 10, -10);
			Changing(pPixelData);

			glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);*/

			int tmp_change = int(random(0, 3));
			glBegin(GL_POLYGON);
			if (tmp_change == 0)
			{
				double sc = random(0.8, 1.2);
				for (int i = 0; i < num; i++)
				{
					int *tmp = Scale(pts[i].x, pts[i].y, sc);
					pts[i].x = tmp[0];
					pts[i].y = tmp[1];
					glVertex2i(pts[i].x, pts[i].y);
				}
			}
			else if (tmp_change == 1)
			{
				double an = random(-PI / 5, PI / 5);
				for (int i = 0; i < num; i++)
				{
					int *tmp = rotate(pts[i].x, pts[i].y, an);
					pts[i].x = tmp[0];
					pts[i].y = tmp[1];
					glVertex2i(pts[i].x, pts[i].y);
				}
			}
			else
			{
				int dx = int(random(-100, 100));
				int dy = int(random(-100, 100));
				for (int i = 0; i < num; i++)
				{
					int *tmp = move2(pts[i].x, pts[i].y, dx, dy);
					pts[i].x = tmp[0];
					pts[i].y = tmp[1];
					glVertex2i(pts[i].x, pts[i].y);
				}
			}
			glEnd();

			glFlush();
		}
	}
}
