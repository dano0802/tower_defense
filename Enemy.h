#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <iostream>

class Enemy {

private:
	std::string Name;
	int Hp;
	int Speed;
	int Gold;
	int X1, X2, X3;

public:
	Enemy(std::string name, int Hp, int Speed, int Gold, int x1, int x2, int x3);
	std::string getName() const;
	int getHealth() const;
	int getSpeed() const;
	int getGold() const;
	void HpLower(int value);
	void reEnemy();
	void kirajzol(float a);

};

#endif