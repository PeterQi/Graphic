#pragma once
#include "ordered_edge_table_algorithm.h"
class Point2
{
public:
	int x, y;
	int code;
	Point2()
	{
		x = 0;
		y = 0;
		code = 0;
	}
	void coding(int i)
	{
		int addend = 1;
		addend = addend << i;
		code += addend;
	}
	void getCode(int Lx, int Hx, int Ly, int Hy)
	{
		if (x < Lx)
		{
			coding(0);
		}
		else if (x > Hx)
		{
			coding(1);
		}
		if (y < Ly)
		{
			coding(2);
		}
		else if (y > Hy)
		{
			coding(3);
		}
	}
};
class Segment
{
public:
	Point2 A, B;
	Segment()
	{
		return;
	}
	int intersectionY(int y)
	{
		segments tmps;
		tmps.setSegments(A.x, B.x, A.y, B.y);
		return (int)((-tmps.B*y - tmps.C) / tmps.A);
	}
	int intersectionX(int x)
	{
		segments tmps;
		tmps.setSegments(A.x, B.x, A.y, B.y);
		return (int)((-tmps.A*x - tmps.C) / tmps.B);
	}
	
};
class Rectangle2
{
public:
	int Lx, Hx, Ly, Hy;
	Rectangle2()
	{
		return;
	}
	void setRectangle(int tlx, int thx, int tly, int thy)
	{
		Lx = (tlx < thx) ? tlx : thx;
		Hx = (tlx > thx) ? tlx : thx;
		Ly = (tly < thy) ? tly : thy;
		Hy = (tly > thy) ? tly : thy;
	}
	void Cohen(Segment s)
	{
		s.A.getCode(Lx, Hx, Ly, Hy);
		s.B.getCode(Lx, Hx, Ly, Hy);
		if (s.A.code == 0 && s.B.code == 0)
		{
			glBegin(GL_LINES);
			glVertex2i(s.A.x, s.A.y);
			glVertex2i(s.B.x, s.B.y);
			glEnd();
			//std::cout << '(' << s.A.x << ',' << s.A.y << ')' << '(' << s.B.x << ',' << s.B.y << ')' << endl;
		}
		else if (s.A.code & s.B.code)
		{
			//cout << s.A.code << '&' << s.B.code << endl;
			return;
		}
		else
		{
			int y1, y2, x1, x2;
			if (s.A.x != s.B.x)
			{
				y1 = s.intersectionX(Lx);
				y2 = s.intersectionX(Hx);
			}
			if (s.A.y != s.B.y)
			{
				x1 = s.intersectionY(Ly);
				x2 = s.intersectionY(Hy);
			}
			if (s.A.x == s.B.x)
			{
				int start_y = Ly;
				int end_y = Hy;
				glBegin(GL_LINES);
				glVertex2i(s.A.x, start_y);
				glVertex2i(s.A.x, end_y);
				glEnd();
				//std::cout << '(' << s.A.x << ',' << start_y << ')' << '(' << s.A.x << ',' << end_y << ')' << endl;
			}
			else
			{
				bool flag = false;
				int num2 = 0;
				Point2 p[2];
				Point2 AB[2];
				if (y1 >= Ly && y1 <= Hy)
				{
					flag = true;
					p[num2].x = Lx;
					p[num2].y = y1;
					num2++;
				}
				if (y2 >= Ly && y2 <= Hy)
				{
					flag = true;
					p[num2].x = Hx;
					p[num2].y = y2;
					num2++;
				}
				if (x1 >= Lx && x1 <= Hx)
				{
					flag = true;
					p[num2].x = x1;
					p[num2].y = Ly;
					num2++;
				}
				if (x2 >= Lx && x2 <= Hx)
				{
					flag = true;
					p[num2].x = x2;
					p[num2].y = Hy;
					num2++;
				}
				if (!flag)
				{
					return;
				}
				if (s.A.x < s.B.x)
				{
					AB[0] = s.A;
					AB[1] = s.B;
				}
				else
				{
					AB[0] = s.B;
					AB[1] = s.A;
				}
				if (p[1].x < p[0].x)
				{
					Point2 tmp = p[0];
					p[0] = p[1];
					p[1] = tmp;
				}
				if (p[0].x < AB[0].x)
				{
					p[0] = AB[0];
				}
				if (p[1].x > AB[1].x)
				{
					p[1] = AB[1];
				}
				glBegin(GL_LINES);
				glVertex2i(p[0].x, p[0].y);
				glVertex2i(p[1].x, p[1].y);
				glEnd();
				//std::cout << '(' << p[0].x << ',' << p[0].y << ')' << '(' << p[1].x << ',' << p[1].y << ')' << endl;
			}
		}
	}
};

void Cohen_mouse(int button, int state, int x, int y, int &num, Segment *segs, bool &is_seg, bool &cutting, Point2 *recP, int &rec_num)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		if (cutting)
		{
			if (rec_num == 0)
			{
				glClear(GL_COLOR_BUFFER_BIT);
				recP[rec_num].x = x;
				recP[rec_num].y = WINDOW_HEIGHT - y;
				rec_num++;
			}
			else
			{
				glEnd();
				recP[rec_num].x = x;
				recP[rec_num].y = WINDOW_HEIGHT - y;
				rec_num++;
				Rectangle2 newRec;
				newRec.setRectangle(recP[0].x, recP[1].x, recP[0].y, recP[1].y);
				glBegin(GL_LINE_LOOP);
				glVertex2i(newRec.Lx, newRec.Ly);
				glVertex2i(newRec.Lx, newRec.Hy);
				glVertex2i(newRec.Hx, newRec.Hy);
				glVertex2i(newRec.Hx, newRec.Ly);
				glEnd();
				for (int i = 0; i < num; i++)
				{
					newRec.Cohen(segs[i]);
				}


				glFlush();
				num = 0;
				cutting = false;
				rec_num = 0;
			}
			return;

		}
		if (num == 0)
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
		if (is_seg)
		{
			segs[num].A.x = x;
			segs[num].A.y = WINDOW_HEIGHT - y;
			is_seg = !is_seg;
		}
		else
		{
			segs[num].B.x = x;
			segs[num].B.y = WINDOW_HEIGHT - y;
			is_seg = !is_seg;

			glBegin(GL_LINES);
			glVertex2i(segs[num].A.x, segs[num].A.y);
			glVertex2i(x, WINDOW_HEIGHT - y);
			glEnd();
			glFlush();

			num++;
			cout << num << endl;
		}

	}
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON)
	{
		glEnd();
		glFlush();
		cutting = true;
		is_seg = true;
	}
}
