#include "Glew_and_Glut\glew-1.11.0\include\GL\glew.h"
#include "Glew_and_Glut\freeglut\include\GL\freeglut.h"
#include "Enemy.h"
#include "Tower.h"
#include <iostream>
#include <string>

#define COLUMNS 1000
#define ROWS 500

Enemy e("enemy1", 100, 10, 10, 10, 10, 10);
Tower t("tower1", 2,10,4);

float a = -0.8;
bool tower = false;
bool wave = false;
bool fire = false;
int life = 100;
float lifeReduc = 0.1;
GLint gFramesPerSecond = 0;
void *currentfont;
std::string lifeCount;
std::string moneyCount;


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

void drawstring(float x, float y, float z, std::string str)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (unsigned i=0; i<str.length(); i++)
	{
		glColor3f(0.0, 0.0, 0.0);
		glutBitmapCharacter(currentfont, (int)str[i]);
	}
}

void displayMe(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //képernyőtörlés

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(-1.0, 0.9, 0.0, "WAVE");

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(-0.9, 0.9, 0.0, "TOWER");

	//std::string s = std::to_string(23);
	lifeCount = "LIFE " + std::to_string(life);

	setFont(GLUT_BITMAP_HELVETICA_12); //Font set to helvetica with size 12
	glColor3f(1.0, 1.0, 0.0);
	drawstring(0.0, 0.9, 0.0, lifeCount);



	glBegin(GL_POLYGON);
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(-1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(1.0, 0.2, 0.0);
	glVertex3f(-1.0, 0.2, 0.0);
	glEnd();

	if (e.getHealth() > 50){
		e.kirajzol(a);
	}

	if (life > 0){
		glBegin(GL_TRIANGLES);
		glColor3f(0.5, 1.0, 0.5);
		glVertex3f((a - 0.1), 0.1, 0.0);
		glVertex3f((a - 0.1) - 0.05, 0.05, 0.0);
		glVertex3f((a - 0.1) + 0.05, 0.05, 0.0);
		glEnd();
	}
	

	//torony és lövedékek rajzolása
	t.kirajzol();
	t.kirajzolLovedek();


	if (fire == true)
	{
		t.Loves();
		if (t.getYLovedek() < 0.1)
		{ 
			t.setXY();
			t.setXYV((a + lifeReduc - t.getXLovedek()) / 50, -0.3 / 50);
			life -= t.getDamage();
			e.HpLower(t.getDamage()); //csökkentjük az életet a torony által meghatározott értékkel
			if (life == 50){ lifeReduc -= 0.1; }
			if (life == 0){
				wave = false; fire = false; a = -0.8;
				t.setXY();
				life = 100;
				lifeReduc = 0.1;
				e.reEnemy();
			}
		}
	}

	if (wave == true) //ha a wave elindult
	{
		a += 0.002;
		if (a >= 1.0) {
			wave = false; 
			fire = false; 
			a = -0.8; 
			t.setXY();
		}
	}

	glFlush();
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (wave == false && tower==false && x > 0 && x < 40 && y>10 && y < 30) { //ha a wavere kattintunk elindul a hullám
			wave = true;
			fire = true; //engedélyezi a folyamatos lövést
			t.setXYV((a - x) / 50, -0.3 / 50);
		}

		if (wave == false && x>40 && x < 80 && y>10 && y < 30) {  //ha a towerre kattintunk
			if (tower == false){
				tower = true;
			}
			else{
				tower = false;
			}
		}

		if (wave == false && tower == true) //ha a torony aktív akkor lehet rakosgatni a tornyokat
		{
			t.setTowerXY(float(x) / 800.0 * 2.0 - 1.0, float(y) / 600.0 * -2.0 + 1.0);
		}
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

void resize(int width, int height) {
	//figyelmen kívül hagyjuk a paramétereket és fix méretet állítunk be
	glutReshapeWindow(800, 600);
}

int main(int argc, char** argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world :D");
	//initialize();
	glutReshapeFunc(resize); //ne lehessen méretezni az ablakot
	glutTimerFunc(0, timer, 0);
	glutDisplayFunc(displayMe);
	glutKeyboardFunc(keys);
	glutMouseFunc(mouse);
	initialize();
	glutMainLoop();
	return 0;
}
