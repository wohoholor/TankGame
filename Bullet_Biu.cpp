#include "Bullet_Biu.h"

void Bullet_Biu::move()
{
	switch (direction)
	{
	case 0:
		if (y - BULLET_SPEED <= graph_y1)
		{
			y = graph_y1;
			break;
		}
		y -= BULLET_SPEED;
		break;
	case 1:
		if (x + BULLET_SPEED >= graph_x2)
		{
			x = graph_x2;
			break;
		}
		x += BULLET_SPEED;
		break;
	case 2:
		if (y + BULLET_SPEED >= graph_y2)
		{
			y = graph_y2;
			break;
		}
		y += BULLET_SPEED;
		break;
	case 3:
		if (x - BULLET_SPEED <= graph_x1)
		{
			x = graph_x1;
			break;
		}
		x -= BULLET_SPEED;
		break;
	default:
		break;
	}
}

void Bullet_Biu::display()
{
	COLORREF save_color = getfillcolor();
	setlinecolor(BLACK);
	setfillcolor(bullet_color);
	switch (direction)
	{
	case 0:
		fillrectangle(x - 0.5 * wide, y, x + 0.5 * wide, y + lenth);
		break;
	case 1:
		fillrectangle(x - lenth, y - 0.5 * wide, x, y + 0.5 * wide);
		break;
	case 2:
		fillrectangle(x - 0.5 * wide, y - lenth, x + 0.5 * wide, y);
		break;
	case 3:
		fillrectangle(x, y - 0.5 * wide, x + lenth, y + 0.5 * wide);
		break;
	}
	setfillcolor(save_color);
}

DirBullet::DirBullet(int a, int b, int aimx, int aimy):Bullet_Biu(a, b, 0),radius(10)
{
	bullet_color = RGB(rand() % 256, rand() % 256, rand() % 256);
	if (aimy > b)
	{
		direction = 2;
		alpha = (static_cast<double>(aimx - a)) / (aimy - b);
	}
	else
	{
		direction = 0;
		alpha = (static_cast<double>(aimx - a)) / (b - aimy);
	}
}

void DirBullet::move()
{
	double tempy = sqrt(pow(bullet_speed, 2) / (1 + pow(alpha, 2)));
	double tempx = tempy * alpha + x;
	switch (direction)
	{
	case 0:
		
		if (y - tempy <= graph_y1 +radius)
		{
			y = graph_y1;
			break;
		}
		if (tempx >= graph_x2 - radius)
		{
			x = graph_x2;
			break;
		}
		if (tempx <= graph_x1 + radius)
		{
			x = graph_x1;
			break;
		}
		y -= tempy;
		x = tempx;
		break;
	case 2:
		if (y + tempy >= graph_y2 - radius)
		{
			y = graph_y2;
			break;
		}
		if (tempx >= graph_x2 - radius)
		{
			x = graph_x2;
			break;
		}
		if (tempx <= graph_x1 + radius)
		{
			x = graph_x1;
			break;
		}
		y += tempy;
		x = tempx;
		break;
	default:
		break;
	}
}

void DirBullet::display()
{
	COLORREF save_color = getfillcolor();
	setfillcolor(bullet_color);
	fillcircle(x, y, radius);
	setfillcolor(save_color);
}