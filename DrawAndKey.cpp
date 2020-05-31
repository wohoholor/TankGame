#include"DrawAndKey.h"
using namespace std;

void draw_Five(int x, int y, int r, COLORREF C, COLORREF BG)
{
	COLORREF save_color = getfillcolor();
	setfillcolor(BG);
	fillcircle(x, y, r);
	setlinecolor(C);
	int x1[5];
	int y1[5];
	double jio = 72.0;
	for (int i = 0; i < 5; ++i)
	{
		x1[i] = r * cos(((jio * i) / 180) * PI);
		y1[i] = r * sin(((jio * i) / 180) * PI);
	}
	for (int i = 0; i < 3; ++i)
	{
		line(x + x1[i], y + y1[i], x + x1[(i + 3) % 5], y + y1[(i + 3) % 5]);
		line(x + x1[i], y + y1[i], x + x1[(i + 2) % 5], y + y1[(i + 2) % 5]);
	}
	setfillcolor(save_color);
}

void heart(int x0, int y0, int size, COLORREF C)
{
	double  m, n, x, y; double i;
	for (i = 0; i <= 2 * size; i = i + 0.01)
	{
		//产生极坐标点
		m = i;
		n = -size * (((sin(i) * sqrt(fabs(cos(i)))) / (sin(i) + 1.4142)) - 2 * sin(i) + 2);
		//转换为笛卡尔坐标
		x = n * cos(m) + x0;
		y = n * sin(m) + y0;
		putpixel(x, y, C);
	}
}

void HowAboutLife(int count, int numKill,int hp)
{
	string temp = to_string(count);
	string tn = to_string(numKill);
	string h = to_string(hp);
	outtextxy(80, NUMPOS, temp.c_str());
	outtextxy(350, NUMPOS, tn.c_str());
	char hhh[] = "HP值:";
	outtextxy(500, NUMPOS, hhh);
	outtextxy(600, NUMPOS, h.c_str());
}

void ScenceSet()
{
	setlinecolor(YELLOW);
	rectangle(30, 20, 930, 680);
	heart(30, 700, 8, RED);
	draw_Five(300, 713, 18, RGB(65, 105, 225), RGB(127, 255, 170));
}

void SubLife(ControlCenter& center,int &num)
{
	if (center.Is_UserEmpty() && num != 0)
	{
		--num;
		center.AddUserTank();
		Sleep(100);
	}
}

void MoveButton(ControlCenter& center)
{
	if (GetAsyncKeyState(0x57) & 0x8000)
		center.UserMove(UP);
	else if (GetAsyncKeyState(0x41) & 0x8000)
		center.UserMove(LEFT);
	else if (GetAsyncKeyState(0x53) & 0x8000)
		center.UserMove(DOWN);
	else if (GetAsyncKeyState(0x44) & 0x8000)
		center.UserMove(RIGHT);
}

bool FuntionButton(ControlCenter &center)
{
	if (GetAsyncKeyState(0x4a) & 0x8000)
	{
		thread th1(ThreadSound);
		center.UserAttack();
		th1.join();
	}
	if (GetAsyncKeyState(0x4b) & 0x8000)
		center.AddEveTank();
	if ((GetAsyncKeyState(0x30) & 0x8000) && (GetAsyncKeyState(0x11) & 0x8000))
		center.KillAllEVE();
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		return false;
	
	return true;
}


void NewVersion3()
{
	BeforePlay();
	int Life_num = 5;
	srand((unsigned)time(0));
	ScenceSet();
	ControlCenter center;
	center.AddUserTank();
	BeginBatchDraw();
	int EveCount = 0;
	int UserMoveCount = 0;
	int UserAttackCount = 0;
	while (1)
	{
		if (EveCount == EVESLOWSPEED)
		{
			center.RuningTime();
			center.AutoAttack();
			EveCount = 0;
		}
		if (UserMoveCount == USERMOVESLOWSPEED)
		{
			UserMoveCount = 0;
			MoveButton(center);
		}
		if (UserAttackCount == USERBULLETSLOWSPEED)
		{
			UserAttackCount = 0;
			if (!FuntionButton(center))
				break;
		}
		center.BulletRun();
		center.DisplayAuto();
		SubLife(center, Life_num);
		HowAboutLife(Life_num, center.GetNumberDead(), center.GetCurrHP());
		FlushBatchDraw();
		Sleep(5);
		clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);
		++EveCount;
		++UserMoveCount;
		++UserAttackCount;
	}
	EndBatchDraw();
}


void BeforePlay()
{
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = 30;						// 设置字体高度为 48
	_tcscpy_s(f.lfFaceName, _T("黑体"));		// 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);
	vector<string> str;
	str.push_back("W: 向上;");
	str.push_back("A: 向左;");
	str.push_back("S: 向下;");
	str.push_back("D: 向右;");
	str.push_back("J: 攻击;");
	str.push_back("K: 产生新敌人;");
	str.push_back("空格键: 游戏暂停;");
	str.push_back("? 表示有随机增幅;");
	str.push_back("ESC: 退出;");
	str.push_back("抵制不良游戏 拒绝盗版游戏 注意自我保护 谨防受骗上当");
	str.push_back("适度游戏益脑 沉迷游戏伤身 合理安排时间 享受健康生活");
	str.push_back("随着游戏时间的增长，游戏体验会持续上升，请按任意键继续！");
	int xp = 300, yp = 180;
	int hgap = 40;
	for (int i = 0; i < str.size()-1; ++i)
	{
		if (i >= 9)
		{
			xp = 60;
			yp = 560;
			hgap = 50;
			outtextxy(xp, yp + (i - 9) * hgap, str[i].c_str());
			continue;
		}
		outtextxy(xp, yp + i * hgap, str[i].c_str());
	}

	/*for (int i = 8; i < str.size()-1; ++i)
		outtextxy(xp, yp + i * hgap, str[i].c_str());*/
	COLORREF save_color = gettextcolor();
	settextcolor(RGB(255, 211, 155));
	char s[] = "新版坦克大战";
	f.lfHeight = 50;
	settextstyle(&f);
	outtextxy(240, 100, s);;
	f.lfHeight = 30;
	settextstyle(&f);
	settextcolor(save_color);
	save_color = gettextcolor();
	settextcolor(RGB(128, 128, 128));
	outtextxy(50, graph_y2, str[str.size()-1].c_str());
	settextcolor(save_color);
	_getch();
	cleardevice();
	PlayBeginSound();
}

void DiaplayWin()
{
	static int num = 0;
	clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);
	vector<string> str;
	str.push_back("我们守住了一波兵线");
	str.push_back("稳住我们能赢");
	str.push_back("还有一大波敌人正在来袭");
	str.push_back("终局之战！");
	outtextxy(340, 300, str[num%4].c_str());
	PlayVictorySound();
	++num;
}

void DiaplayGameOver()
{
	clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);
	char s[] = "Good Game";
	outtextxy(360, 300, s);
	PlayGameOver();
}

bool IfYouDead()
{
	cleardevice();
	loadimage(NULL, "bgm\\wxx.jpg");
	vector<string> str;
	str.push_back("打不过？赶紧给他打钱，秘籍秒到手！");
	str.push_back("按空格键继续，或者按ESC退出游戏");
	for (int i=0;i<str.size();++i)
		outtextxy(300, 600+i*60, str[i].c_str());
	while (1)
	{
		if (GetAsyncKeyState(0x20) & 0x8000)
			return true;
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return false;
	}
}

void LevelWin()
{
	clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);
	char s[] = "大魔王被我们打败啦哈哈哈哈哈哈哈";
	outtextxy(200, 300, s);
	PlayEndSound();
}

void ThankList()
{
	Sleep(2000);
	cleardevice();
	vector<string> str;
	str.push_back("总策划：  我得有个名字");
	str.push_back("特效总监：我得有个名字");
	str.push_back("平面美术：我得有个名字");
	str.push_back("程序设计：我得有个名字");
	str.push_back("音乐指导：我得有个名字");
	str.push_back("后期技术：我得有个名字");
	str.push_back("发行人：  我得有个名字");
	str.push_back("背景音乐：坦克大战原音、魂斗罗原音");
	str.push_back("感谢支持，按Esc退出");
	int gap = 50;
	for (int i=0;i<str.size();++i)
		outtextxy(280, 200+gap*i, str[i].c_str());
	while (1)
	{
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			return;
	}
}


void PauseAll()
{
	if (GetAsyncKeyState(0x20) & 0x8000)
	{
		Sleep(10);
		if (GetAsyncKeyState(0x20) & 0x8000)
		{
			mciSendString("pause bgm//Base.wav ", NULL, 0, 0);
			mciSendString("pause bgm//BaseBoss.wav ", NULL, 0, 0);
			system("pause");
			while (!(GetAsyncKeyState(0x20) & 0x8000));
			mciSendString("resume bgm//Base.wav ", NULL, 0, 0);
			mciSendString("resume bgm//BaseBoss.wav ", NULL, 0, 0);
			Sleep(300);
		}
	}
}