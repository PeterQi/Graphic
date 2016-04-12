#pragma once
#include <stack>
#include <math.h>
#define STATE_LENGTH 10000
using namespace std;
class LS_state
{
public:
	double x, y, Beta;
	LS_state(double sx, double sy, double sBeta)
	{
		x = sx;
		y = sy;
		Beta = sBeta;
	}

	LS_state()
	{
		x = 0;
		y = 0;
		Beta = 0;
	}
};
class LS
{
public:
	int n;
	void init_LS(double stheta, double slength, double slength_scale, char * start_state, LS_state start_ls, char *theP)
	{
		theta = stheta;
		length = slength;
		strcpy_s(state, start_state);
		state_now = start_ls;
		start_LS = start_ls;
		strcpy_s(P, theP);
		n = 0;
		length_scale = slength_scale;
	}
	LS()
	{

	}
	void ProcessF()
	{
		double next_x = state_now.x + length*cos(state_now.Beta);
		double next_y = state_now.y + length*sin(state_now.Beta);
		
		glBegin(GL_LINES);
		glVertex2i(int(state_now.x), int(state_now.y));
		glVertex2i(int(next_x), int(next_y));
		glEnd();
		glFlush();
		state_now.x = next_x;
		state_now.y = next_y;

	}
	void ProcessG()
	{
		double next_x = state_now.x + length*cos(state_now.Beta);
		double next_y = state_now.y + length*sin(state_now.Beta);

		state_now.x = next_x;
		state_now.y = next_y;
	}
	void ProcessPlus()
	{
		state_now.Beta -= theta;
	}
	void ProcessMinus()
	{
		state_now.Beta += theta;
	}
	void ProcessLeftBracket()
	{
		states_stk.push(state_now);
	}
	void ProcessRightBracket()
	{
		state_now = states_stk.top();
		states_stk.pop();
	}
	void ProcessP()
	{
		n++;
		length /= length_scale;
		char new_state[STATE_LENGTH];
		int j = 0;
		strcpy_s(new_state, "");
		int P_len = strlen(P);
		for (int i = 0; i < strlen(state); i++)
		{
			if (state[i] == 'F')
			{
				strcat_s(new_state, P);
				j += P_len;

			}
			else
			{
				new_state[j] = state[i];
				new_state[j + 1] = '\0';
				j++;
			}
		}
		strcpy_s(state, new_state);
	}
	void ProcessPaint()
	{
		state_now = start_LS;
		while (!states_stk.empty())
			states_stk.pop();
		for (int i = 0; i < strlen(state); i++)
		{
			switch (state[i])
			{
			case 'F':
				ProcessF();
				break;
			case 'G':
				ProcessG();
				break;
			case '+':
				ProcessPlus();
				break;
			case '-':
				ProcessMinus();
				break;
			case '[':
				ProcessLeftBracket();
				break;
			case ']':
				ProcessRightBracket();
				break;
			default:
				break;
			}

		}

	}
private:
	double theta;
	double length;
	double length_scale;
	char state[STATE_LENGTH];
	LS_state state_now;
	LS_state start_LS;
	stack <LS_state> states_stk;
	char P[100];
};