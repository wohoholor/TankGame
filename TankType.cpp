#include "TankType.h"
#define PI 3.14159



int TankType::GetGunPosx()
{
	switch (derection)
	{
	case 0:
	case 2:
		return (x + 0.5 * squre_edge);
	case 1:
		return (x + squre_edge + gun_len);
	case 3:
		return (x - gun_len);
	default:
		break;
	}
	return 0;
}

int TankType::GetGunPosy()
{
	switch (derection)
	{
	case 0:
		return (y - gun_len);
	case 2:
		return (y + squre_edge +gun_len);
	case 1:
	case 3:
		return (y + squre_edge * 0.5);
	default:
		break;
	}
	return 0;
}

void TankType::move(char ch)
{
	switch (ch)
	{
	case UP:
		if (y - gun_len - move_speed < graph_y1)
			break;
		derection = 0;
		y -= move_speed;
		areax1 = x;
		areax2 = x + squre_edge;
		areay1 = y - gun_len;
		areay2 = y + squre_edge;
		break;
	case DOWN:
		if (y + squre_edge + gun_len + move_speed > graph_y2)
			break;
		derection = 2;
		y += move_speed;
		areax1 = x;
		areax2 = x + squre_edge;
		areay1 = y;
		areay2 = y + squre_edge+gun_len;
		break;
	case LEFT:
		if (x - gun_len - move_speed < graph_x1)
			break;
		derection = 3;
		x -= move_speed;
		areax1 = x-gun_len;
		areax2 = x + squre_edge;
		areay1 = y;
		areay2 = y + squre_edge;
		break;
	case RIGHT:
		if (x + squre_edge + gun_len + move_speed > graph_x2)
			break;
		derection = 1;
		x += move_speed;
		areax1 = x;
		areax2 = x + squre_edge + gun_len;
		areay1 = y;
		areay2 = y + squre_edge;
		break;
	default:
		break;
	}
}

void TankType::display()
{
	COLORREF save_color = getfillcolor();
	setlinecolor(BLACK);
	setfillcolor(main_color);
	fillrectangle(x, y, x + squre_edge, y + squre_edge);
	switch (derection)
	{
	case 0:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y - gun_len, x + squre_edge / 2 + gun_wide / 2, y);
		break;
	case 1:
		fillrectangle(x + squre_edge, y + squre_edge / 2 - gun_wide / 2, x + squre_edge + gun_len, y + squre_edge / 2 + gun_wide / 2);
		break;
	case 2:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y + squre_edge, x + squre_edge / 2 + gun_wide / 2, y + squre_edge + gun_len);
		break;
	case 3:
		fillrectangle(x - gun_len, y + squre_edge / 2 - gun_wide / 2, x, y + squre_edge / 2 + gun_wide / 2);
		break;
	default:
		break;
	}
	setfillcolor(save_color);
}

void draw_line(int derection,int x, int y,int track_lenth,int track_wide,int squre_edge, COLORREF track_color)
{
	setlinecolor(BLACK);
	setfillcolor(track_color);
	switch (derection)
	{
	case 0:
	case 2:
		fillrectangle(x - track_wide, y - (track_lenth / 2 - squre_edge / 2), x, y + squre_edge + (track_lenth / 2 - squre_edge / 2));
		fillrectangle(x + squre_edge, y - (track_lenth / 2 - squre_edge / 2), x + track_wide + squre_edge, y + squre_edge + (track_lenth / 2 - squre_edge / 2));
		line(x - track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, x, y - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth);
		line(x - track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, x, y - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth);
		line(x - track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, x, y - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth);
		line(x + squre_edge, y - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, x + squre_edge + track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth);
		line(x + squre_edge, y - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, x + squre_edge + track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth);
		line(x + squre_edge, y - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, x + squre_edge + track_wide, y - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth);
		break;
	case 1:
	case 3:
		fillrectangle(x - (track_lenth / 2 - squre_edge / 2), y - track_wide, x + squre_edge + (track_lenth / 2 - squre_edge / 2), y);
		fillrectangle(x - (track_lenth / 2 - squre_edge / 2), y + squre_edge, x + squre_edge + (track_lenth / 2 - squre_edge / 2), y + squre_edge + track_wide);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, y - track_wide, x - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, y);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, y + squre_edge, x - (track_lenth / 2 - squre_edge / 2) + 0.25 * track_lenth, y + squre_edge + track_wide);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, y - track_wide, x - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, y);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, y + squre_edge, x - (track_lenth / 2 - squre_edge / 2) + 0.5 * track_lenth, y + squre_edge + track_wide);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, y - track_wide, x - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, y);
		line(x - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, y + squre_edge, x - (track_lenth / 2 - squre_edge / 2) + 0.75 * track_lenth, y + squre_edge + track_wide);
		break;
	}
}

MyTank::MyTank():TankType(), track_wide(14), track_lenth(40), track_color(BLUE)
{
	gun_len = 18;
	HP = 5;
	move_speed = 2;
	loadimage(&img, _T("bgm\\tank1.jpg"), squre_edge+gun_len,squre_edge+gun_len);
	loadimage(&fimg, _T("bgm\\ftank1.jpg"), squre_edge+gun_len, squre_edge+gun_len);
	/*loadimage(&imgR, _T("bgm\\tank3R.jpg"), squre_edge * 3, squre_edge * 3);
	loadimage(&fimgR, _T("bgm\\ftank3R.jpg"), squre_edge * 3, squre_edge * 3);
	loadimage(&imgB, _T("bgm\\tank3B.jpg"), squre_edge * 3, squre_edge * 3);
	loadimage(&fimgB, _T("bgm\\ftank3B.jpg"), squre_edge * 3, squre_edge * 3);
	loadimage(&imgL, _T("bgm\\tank3L.jpg"), squre_edge * 3, squre_edge * 3);
	loadimage(&fimgL, _T("bgm\\ftank3L.jpg"), squre_edge * 3, squre_edge * 3);*/
}

void MyTank::display()
{ 
	IMAGE temp;
	switch (derection)
	{
	case 0:
		putimage(x, y, &fimg, NOTSRCERASE);
		putimage(x, y, &img, SRCINVERT);
		break;
	case 1:
		rotateimage(&temp, &fimg, 1.5 * PI, BLACK);
		putimage(x , y , &temp, NOTSRCERASE);
		rotateimage(&temp, &img, 1.5 * PI, BLACK);
		putimage(x, y, &temp, SRCINVERT);
		break;
	case 2:
		rotateimage(&temp, &fimg, PI, BLACK);
		putimage(x, y, &temp, NOTSRCERASE);
		rotateimage(&temp, &img, PI, BLACK);
		putimage(x, y, &temp, SRCINVERT);
		break;
	case 3:
		rotateimage(&temp, &fimg, 0.5 * PI, BLACK);
		putimage(x, y, &temp, NOTSRCERASE);
		rotateimage(&temp, &img, 0.5 * PI, BLACK);
		putimage(x, y, &temp, SRCINVERT);
		break;
	default:
		break;
	}
}


void EVETank::display()
{
	COLORREF save_color = getfillcolor();
	setfillcolor(main_color);
	fillrectangle(x, y, x + squre_edge, y + squre_edge);
	switch (derection)
	{
	case 0:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y - gun_len, x + squre_edge / 2 + gun_wide / 2, y);
		break;
	case 1:
		fillrectangle(x + squre_edge, y + squre_edge / 2 - gun_wide / 2, x + squre_edge + gun_len, y + squre_edge / 2 + gun_wide / 2);
		break;
	case 2:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y + squre_edge, x + squre_edge / 2 + gun_wide / 2, y + squre_edge + gun_len);
		break;
	case 3:
		fillrectangle(x - gun_len, y + squre_edge / 2 - gun_wide / 2, x, y + squre_edge / 2 + gun_wide / 2);
		break;
	default:
		break;
	}
	draw_line(derection, x, y, track_lenth, track_wide, squre_edge, track_color);
	setfillcolor(save_color);
}

BossTank::BossTank(int edge,int dir,int glen,int gwide,int x1,int y1, COLORREF mcolor,int r,COLORREF radcolor,int hp, int move_s):EVETank()
{
	squre_edge = edge;
	derection = dir;
	gun_len = glen;
	gun_wide = gwide;
	x = x1;
	y = y1;
	radius = r;
	main_color = mcolor;
	radius_color = radcolor;
	HP = hp;
	move_speed = move_s;
}

void draw_pie(int x, int y, int edge, int size, COLORREF colo)
{
	COLORREF save_color = getfillcolor();
	setfillcolor(colo);
	solidpie(x - size * 0.5, y - size * 0.5, x + size * 0.5, y + size * 0.5, 0, PI * 1.5);
	solidpie(x - size * 0.5 + edge, y - size * 0.5, x + size * 0.5 + edge, y + size * 0.5, -PI * 0.5, PI);
	solidpie(x - size * 0.5, y - size * 0.5 + edge, x + size * 0.5, y + size * 0.5 + edge, 0.5 * PI, 0);
	solidpie(x - size * 0.5 + edge, y - size * 0.5 + edge, x + size * 0.5 + edge, y + size * 0.5 + edge, PI, PI * 0.5);
	setfillcolor(save_color);
}

void BossTank::display()
{
	COLORREF save_color = getfillcolor();
	setfillcolor(main_color);
	fillrectangle(x, y, x + squre_edge, y + squre_edge);
	switch (derection)
	{
	case 0:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y - gun_len, x + squre_edge / 2 + gun_wide / 2, y);
		break;
	case 1:
		fillrectangle(x + squre_edge, y + squre_edge / 2 - gun_wide / 2, x + squre_edge + gun_len, y + squre_edge / 2 + gun_wide / 2);
		break;
	case 2:
		fillrectangle(x + squre_edge / 2 - gun_wide / 2, y + squre_edge, x + squre_edge / 2 + gun_wide / 2, y + squre_edge + gun_len);
		break;
	case 3:
		fillrectangle(x - gun_len, y + squre_edge / 2 - gun_wide / 2, x, y + squre_edge / 2 + gun_wide / 2);
		break;
	default:
		break;
	}
	draw_pie(x, y, squre_edge, radius, radius_color);
	setfillcolor(save_color);
}

void TankType::move(TankType &f)
{
	if (y + 0.5 * squre_edge > f.GetPosY() + f.GetSqure())
	{
		derection = 0;
		y-=move_speed;
	}
	else if (y + 0.5 * squre_edge < f.GetPosY() )
	{
		derection = 2;
		y+= move_speed;
	}
	else
	{
		if (x + squre_edge < f.GetPosX())
		{
			derection = 1;
			x += move_speed;
		}
		else if (x > f.GetPosX() + f.GetSqure())
		{
			derection = 3;
			x -= move_speed;
		}
		else
		{
			if (y <= graph_y2 - 100)
			{
				y += 50;
				derection = 0;
				return;
			}
			else
			{
				y -= 200;
				derection = 2;
			}
		}
	}
}
