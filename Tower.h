#ifndef TOWER_H
#define TOWER_H

#include <string>
#include <iostream>

class Tower{
private:
	std::string Type;
	int Range;
	int Damage;
	int RateOfFire;
	float xLovedek; 
	float yLovedek;
	float xVLovedek;
	float yVLovedek;
	float towerX;
	float towerY;

public:
	Tower(std::string Type, int Range, int Damage, int RateOfFire);
	std::string getType() const;
	int getRange() const;
	int getDamage() const;
	int getRateOfFire() const;
	float getXLovedek() const;
	float getYLovedek()const;
	void kirajzol() const;
	void kirajzolLovedek() const;
	void setXYV(float xV, float yV);
	void setXY();
	void Loves();
	void setTowerXY(float x, float y);
};

#endif