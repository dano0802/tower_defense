#include "Glew_and_Glut\glew-1.11.0\include\GL\glew.h"
#include "Glew_and_Glut\freeglut\include\GL\freeglut.h"
#include "Tower.h"

Tower::Tower(std::string type, int range, int damage, int rateOfFire){
	Type = type;
	Range=range;
	Damage=damage;
	RateOfFire = rateOfFire;
	xLovedek = 0.0;
	yLovedek = 0.4;
	xVLovedek = 0.0;
	yVLovedek = 0.0;
	towerX = 0.1;
	towerY = 0.5;
}

int Tower::getRateOfFire() const{
	return RateOfFire;
}
std::string Tower::getType() const {
	return Type;
}
int Tower::getRange() const{
	return Range;
}
int Tower::getDamage() const{
	return Damage;
}

float Tower::getXLovedek() const {
	return xLovedek;
}

float Tower::getYLovedek() const {
	return yLovedek;
}

void Tower::kirajzol() const{
	glBegin(GL_POLYGON);
	glColor3f(0.4, 0.1, 0.9);
	glVertex3f(this->towerX, this->towerY, 0.0);
	glVertex3f(this->towerX + 0.1, this->towerY, 0.0);
	glVertex3f(this->towerX + 0.1, this->towerY-0.1, 0.0);
	glVertex3f(this->towerX, this->towerY-0.1, 0.0);
	glEnd();
}

void Tower::kirajzolLovedek() const{
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.9, 0.4);
	glVertex3f(this->xLovedek, this->yLovedek, 0.0);
	glVertex3f(this->xLovedek + 0.02, this->yLovedek, 0.0);
	glVertex3f(this->xLovedek + 0.02, this->yLovedek - 0.02, 0.0);
	glVertex3f(this->xLovedek, this->yLovedek - 0.02, 0.0);
	glEnd();
}


void Tower::setXYV(float xV, float yV){ //beállítja a lövedék irányát
	this->xVLovedek = xV;
	this->yVLovedek = yV;
}

void Tower::setXY(){ //beállítja a lövedék indulási helyét
	this->xLovedek = this->towerX;
	this->yLovedek = this->towerY;
}

void Tower::Loves(){ //lõ
	this->xLovedek += this->xVLovedek;
	this->yLovedek += this->yVLovedek;
}

void Tower::setTowerXY(float x, float y){ //beállítja a torony helyét
	this->towerX = x;
	this->towerY = y;
}