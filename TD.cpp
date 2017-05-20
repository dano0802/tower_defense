#include "Glew_and_Glut\glew-1.11.0\include\GL\glew.h"
#include "Glew_and_Glut\freeglut\include\GL\freeglut.h"
#include <iostream>

float a = -0.8;
bool wave = false;
GLint gFramesPerSecond = 0;
void *currentfont;

void initialize()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}


void FPS(void) {
	static GLint Frames = 0;         // frames averaged over 1000mS
	static GLuint Clock;             // [milliSeconds]
	static GLuint NextClock = 0;     // [milliSeconds]

	++Frames;
	Clock = glutGet(GLUT_ELAPSED_TIME); //has limited resolution, so average over 1000mS
	if (Clock < NextClock) return;

	gFramesPerSecond = Frames / 1; // store the averaged number of frames per second

	NextClock = Clock + 1000; // 1000mS=1S in the future
	Frames = 0;
}

void timer(int value)
{
	const int desiredFPS = 120;
	glutTimerFunc(1000 / desiredFPS, timer, ++value);
	GLfloat dt = (gFramesPerSecond>0 ? 1.0 / gFramesPerSecond : 1.0);

	//put your specific idle code here
	//... this code will run at desiredFPS
	//gAngle += dt*360. / 8.; //rotate 360 degrees every 8 seconds
	//end your specific idle code here

	FPS(); //only call once per frame loop to measure FPS
	glutPostRedisplay(); // initiate display() call at desiredFPS rate
}


void setFont(void *font)
{
	currentfont = font;                      // Set the currentfont to the font
}

void drawstring(float x, float y, float z, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, *c);
	}
}

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(-1.0, 0.9, 0.0, "WAVE");

	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.2, 0.0);
	glVertex3f(-1.0, 0.2, 0.0);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.5,1.0,0.5);
	glVertex3f(a, 0.1, 0.0);
	glVertex3f(a-0.05, 0.05, 0.0);
	glVertex3f(a+0.05, 0.05, 0.0);
	glEnd();


	if (wave == true)
	{
		a += 0.005;
		if (a >= 1.0) { wave = false; a = -0.8; }
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && wave==false && x>0 && x<40 && y>10 && y<30) {
		wave = true;
		//glutPostRedisplay();
	}
}

void keys(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27:                    // 27 is for Esc key
				exit(0);
				break;
		case 32:
			a -= 0.1;
				break;
		default:
				break;
	}
}


int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world :D");
	//initialize();
	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(displayMe);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	initialize();
	glutMainLoop();
	return 0;
}