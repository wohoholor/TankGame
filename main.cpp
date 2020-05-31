#include <iostream>
#include"DrawAndKey.h"
#include "ControlWhole.h"

using namespace std;


int main()
{
	srand((unsigned)time(0));
	initgraph(960, 740);   // 创建图形界面
	COLORREF save_color = getfillcolor();
	while (1) {
		BeforePlay();
		char s[] = "加载中...";
		outtextxy(420, 310, s);;
		Sleep(1500);
		ControlCenter center;
		ControlWhole game(center);
		if (game.CombainationA())
		{
			ThankList();
			break;
		}
		else
		{
			if (IfYouDead())
				continue;
			else
				break;
		}
	}
	//system("pause");       // 按任意键继续
	closegraph();          // 关闭图形界面
}