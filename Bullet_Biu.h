#pragma once
#ifndef BULLET_BIU
#define BULLET_BIU
#define BULLET_SPEED 3
#include"TankType.h"
#include<list>
using namespace std;

class Bullet_Biu
{
protected:
	int x;
	int y;
	int bullet_speed;
	int wide;
	int lenth;
	int direction;
	int HurtHP;
	COLORREF bullet_color;
public:
	Bullet_Biu(int a, int b, int d) : bullet_speed(BULLET_SPEED), wide(6), lenth(10), direction(d), bullet_color(GREEN), y(b),x(a), HurtHP(1){ }
	Bullet_Biu(int a, int b, int d, int harm) :Bullet_Biu(a, b, d) { HurtHP = harm; }
	virtual void move();
	virtual void display();
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetHurtHP() { return HurtHP; }
};


class DirBullet : public Bullet_Biu
{
	double alpha;
	int radius;
public:
	DirBullet(int a, int b, int aimx, int aimy);
	void move();
	void display();
};








#endif // !BULLET_BIU



