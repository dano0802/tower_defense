#include "Glew_and_Glut\glew-1.11.0\include\GL\glew.h"
#include "Glew_and_Glut\freeglut\include\GL\freeglut.h"
#include "Enemy.h"

Enemy::Enemy(std::string name, int hp, int speed, int gold, int x1, int x2, int x3){
	Name = name;
	Hp = hp;
	Speed = speed;
	Gold = gold;
	X1 = x1;
	X2 = x2;
	X3 = x3;
}
std::string Enemy::getName() const{
	return Name;
}
int Enemy::getHealth() const{
	return Hp;
}
int Enemy::getSpeed() const{
	return Speed;
}
int Enemy::getGold() const{
	return Gold;
}
void Enemy::HpLower(int value){
	Hp -= value;
}
void Enemy::reEnemy(){
	Hp = 100;
}

void Enemy::kirajzol(float a){
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 1.0, 0.5); ///szín
	glVertex3f(a, 0.1, 0.0);
	glVertex3f(a - 0.05, 0.05, 0.0);
	glVertex3f(a + 0.05, 0.05, 0.0);
	glEnd();
}