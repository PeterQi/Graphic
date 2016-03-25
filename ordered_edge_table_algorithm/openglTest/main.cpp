#include <GL/glut.h>
#include <stdio.h>
#define WINDOW_HEIGHT 500
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

void myMouse(int button, int state, int x, int y)
{

	
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
	{
		//while (x<1000 && y<1000) {
		glBegin(GL_POINTS);
		glVertex2i(x, WINDOW_HEIGHT - y);
		printf("%d,%d\n", x, y);
		//glVertex2i(x - 250, 250 - y);
		//}

		glEnd();
		glFlush();
	}
	
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2i(0, 0);
	glVertex2i(250, 250);
	glVertex2i(-250, -250);
	glVertex2i(125, 125);
	glEnd();
	glFlush();
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
	Drawing();
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
void myIdle(void)
{

}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);;
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(700, 400);
    glutInitWindowSize(500, WINDOW_HEIGHT);
    glutCreateWindow("First GLUT Sample");
    glutDisplayFunc(&myDisplay);
	//glutDisplayFunc(&renderScene);
	glutMouseFunc(myMouse);
	
	glutReshapeFunc(onReshape);
    glutMainLoop();
    return 0;
}