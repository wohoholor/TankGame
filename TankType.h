#pragma once
#ifndef TANKTYPE_H
#define TANKTYPE_H
#include <graphics.h>
#include <conio.h>
#include <ctime>

#define graph_x1 31//内框坐标
#define graph_x2 929
#define graph_y1 21
#define graph_y2 679
#define GUNLEN 15
#define SQUREEDGE 30
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define ATTACK_BUTTON 'j'
#define ADDEVE_BUTTON 'k'
#define GETLIVE_BUTTON 'l'
#define QUIT_BUTTON 'q'
#define VRATE 2//用于调整子弹速度

class TankType
{
protected:
	int squre_edge;//正方形的边
	int derection;//此时的方向
	int gun_len;//炮的长度
	int gun_wide;//炮宽度
	int x;//正方形左上角x坐标
	int y;//正方形左上角y左边
	int areax1;
	int areax2;
	int areay1;
	int areay2;//这四个好像没用到
	int numKill;//杀敌数
	COLORREF main_color;//主要颜色
public:
	TankType() :squre_edge(SQUREEDGE), derection(0), gun_len(GUNLEN), x(480), y(600), gun_wide(6), areax1(480), areay1(600), areax2(480 + 30), areay2(600 + 30), main_color(WHITE), numKill(0), HP(1), harmH(1), move_speed(1) {}
	TankType(int x1, int y1) :squre_edge(SQUREEDGE), derection(0), gun_len(GUNLEN), x(x1), y(y1), gun_wide(6), areax1(x1), areay1(y1), areax2(x1 + 30), areay2(y1 + 30), main_color(WHITE), numKill(0), HP(1), harmH(1), move_speed(1) {}
	virtual void display();
	void move(char ch);
	virtual void move(TankType& f);
	virtual int GetGunPosx();
	virtual int GetGunPosy();
	int GetPosX() { return x; }
	int GetPosY() { return y; }
	int GetDirection() { return derection; }
	int GetGunlen(){ return gun_len;}
	virtual int GetSqure() { return squre_edge; }
	virtual int GetID() { return 0; }
	int HP;
	int harmH;//攻击伤害
	int move_speed;//移动速度
};

class MyTank :public TankType
{
	int track_wide;//履带的宽
	int track_lenth;//履带的长
	COLORREF track_color;
	IMAGE img;//我的坦克的贴图
	IMAGE fimg;//掩模
	/*IMAGE imgL;
	IMAGE fimgL;
	IMAGE imgB;
	IMAGE fimgB;
	IMAGE imgR;
	IMAGE fimgR;*/
public:
	MyTank();
	MyTank(int a, int b) :MyTank() { x = a; y = b; }
	void display();
	virtual int GetID() { return 1; }
	int GetSqure() { return squre_edge+gun_len; }
	int GetGunPosx()
	{
		if (derection == 0 || derection == 2)
			return x + (squre_edge + gun_len) * 0.5;
		else if (derection == 1)
			return x + squre_edge + gun_len;
		else
			return x;
	}
	int GetGunPosy()
	{
		if (derection == 1 || derection == 3)
			return y + (squre_edge + gun_len) * 0.5;
		else if (derection == 0)
			return y;
		else
			return y + (squre_edge + gun_len);
	}
};


class EVETank :public TankType //普通敌方坦克
{
	int track_wide;
	int track_lenth;
	COLORREF track_color;//履带颜色
public:
	EVETank(int a, int b) :TankType(a, b), track_wide(10), track_lenth(40), track_color(WHITE){ main_color = YELLOW; HP = 2;}
	EVETank(int a, int b, COLORREF color) :TankType(a, b), track_wide(10), track_lenth(40), track_color(WHITE) { main_color = color; HP = 2; }
	EVETank() :TankType(), track_wide(10), track_lenth(40), track_color(WHITE) { main_color = YELLOW; HP = 2; }
	virtual void display();
	virtual int GetID() { return 2; }
};


class BossTank : public EVETank //BOSS
{
	int radius;
	int radius_color;
public:
	BossTank(int edge = 50, int dir = 2, int glen = 24, int gwide = 10, int x1 = 360, int y1 = 120, COLORREF mcolor = RGB(134, 156, 250), int r = 16, COLORREF radcolor = RGB(44, 44, 44), int hp = 30, int move_s = 2);
	BossTank(int a, int b, COLORREF color, COLORREF radcolor) :BossTank() { x = a; y = b; main_color = color; radius_color = radcolor; }
	void display();
	//void move(TankType &f);
	int GetID() { return 3; }
};





#endif // !TANKTYPE_H



