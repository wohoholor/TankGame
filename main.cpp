#include <iostream>
#include"DrawAndKey.h"
#include "ControlWhole.h"

using namespace std;


int main()
{
	srand((unsigned)time(0));
	initgraph(960, 740);   // ����ͼ�ν���
	COLORREF save_color = getfillcolor();
	while (1) {
		BeforePlay();
		char s[] = "������...";
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
	//system("pause");       // �����������
	closegraph();          // �ر�ͼ�ν���
}