#pragma once
#include "config.h"
#include "tool.hpp"
using namespace std;

class mover
{
protected:
	int x = 14, y = 14;
	pair<int, int> dir = { 0,0 };
	int speed = 0;
	IMAGE* img = nullptr;
public:
	mover(){} // 默认构造函数
	mover(int x, int y, int speed = 0, IMAGE* image = nullptr) :
		x(x), y(y), speed(speed), img(image) {} // 重载构造函数

	virtual void update() = 0;
	void draw(int idx)
	{
		int idy = 0;
		if (dir == RIGHT) idy = 0;
		if (dir == LEFT) idy = 1;
		if (dir == UP) idy = 2;
		if (dir == DOWN) idy = 3;
		drawImg(x, y , 24, 24, img, idx * 24, idy * 24);
	}
	void setSpeed(int s) { this->speed = s; }
	void setX(int newx) { this->x = newx; }
	void setY(int newY) { this->y = newY; }
	void setImg(IMAGE* newimg) { this->img = newimg; }
	int getX() const { return x; }
	int getY() const { return y; }
};