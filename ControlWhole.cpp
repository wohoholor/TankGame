#include "ControlWhole.h"
#include"DrawAndKey.h"
#include"BGmusic.h"


int NGame(ControlCenter &center,int EveMove,int EveAttack, int UserAttack,int UserMove)// 0 正常 1 退出 2赢了 3死了 
{
	static int EveMoveCount = 0;
	static int EveAttackCount = 0;
	static int UserMoveCount = 0;
	static int UserAttackCount = 0;
	if (EveMoveCount >= EveMove)
	{
		center.RuningTime();
		EveMoveCount = 0;
	}
	if (EveAttackCount >= EveAttack)
	{
		center.AutoAttack();
		EveAttackCount = 0;
	}
	if (UserMoveCount >= UserMove)
	{
		PauseAll();
		UserMoveCount = 0;
		MoveButton(center);
	}
	if (UserAttackCount >= UserAttack)
	{
		UserAttackCount = 0;
		if (!FuntionButton(center))//esc退出
			return 1;
	}
	if (center.Is_UserEmpty())//死了一条命
	{
		return 3;
	}
	if (center.Is_EveEmpty())//赢了
	{
		return 2;
	}
	++EveMoveCount;
	++EveAttackCount;
	++UserMoveCount;
	++UserAttackCount;
	return 0;
}

bool ControlWhole::NormalGame(int EveNum,int time_value)
{
	static int num = 0;
	++num;
	if (num % 2&& AutoChangeSpeed)
	{
		--user_move_speed;
		--user_attack_speed;
		--eve_move_speed;
	}
	Sleep(2500);
	PlayBase();
	center.AddEveTank(EveNum);
	int ttt = rand() % 2;
	if(ttt==1)
		center.AppearProps();
	BeginBatchDraw();
	int timeClock = time_value;
	while (1)
	{
		ScenceSet();
		int temp = NGame(center, eve_move_speed, eve_attack_speed, user_attack_speed, user_move_speed);
		if (temp==1)//退出
			break;
		else if (temp == 2)//消灭了敌人
		{
			DiaplayWin();
			EndBatchDraw();
			return true;
		}
		else if (temp == 3)//被敌人消灭
		{
			if (Life_num > 0)
			{
				--Life_num;
				center.AddUserTank();
			}
			else
			{
				DiaplayGameOver();
				EndBatchDraw();
				return false;
			}
		}
		if (center.Is_GetProps())
			--timeClock;
		if (timeClock <= 0)
		{
			center.RecoveryNormal();
			timeClock = time_value;
		}
		center.DrawProps();
		center.BulletRun();
		center.DisplayAuto();
		HowAboutLife(Life_num, center.GetNumberDead(), center.GetCurrHP());
		FlushBatchDraw();
		Sleep(5);
		cleardevice();
		/*clearrectangle(500, NUMPOS - 10, graph_x2, NUMPOS + 50);
		clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);*/
	}
}


bool ControlWhole::Soldier_Stage(vector<int> vec)
{
	if (vec.empty())
		return true;
	else
	{
		for (int i = 0; i < vec.size(); ++i)
		{
			if (NormalGame(vec[i]))
				continue;
			else
				return false;
		}
	}
	return true;
}

bool ControlWhole::Soldier_Stage()
{
	for (int i = 0; i < TurnNum.size(); ++i)
	{
		if (NormalGame(TurnNum[i]))
			continue;
		else
			return false;
	}
	return true;
}

int NGame2(ControlCenter& center, int BossMove, int BossAttack, int UserAttack, int UserMove ,int BossCall,int BossSpecial ,int call_num,int special_hurt=5)
{//boss移动速度（值越大越慢，其它同理）
	static int BossA_move = 0;
	static int BossA_attack = 0;
	static int UserMoveCount = 0;
	static int UserAttackCount = 0;
	static int Boss_special = 0;
	static int CallSpeed = 0;
	if (BossCall <= CallSpeed)
	{
		center.AddEveTank(call_num);
		CallSpeed = 0;
	}
	if (BossA_move >= BossMove)
	{
		center.AimMove();
		BossA_move = 0;
	}
	if (BossA_attack >= BossAttack)
	{
		center.AutoAttack();
		BossA_attack = 0;
	}
	if (UserMoveCount >= UserMove)
	{
		PauseAll();
		UserMoveCount = 0;
		MoveButton(center);
	}
	if (UserAttackCount >= UserAttack)
	{
		UserAttackCount = 0;
		if (!FuntionButton(center))
			return 1;
	}
	if (Boss_special >= BossSpecial)
	{
		Boss_special = 0;
		for (int i = 0; i < special_hurt; ++i)
			center.AimAttack();
	}
	if (center.Is_UserEmpty())//死了一条命
		return 3;
	if (center.Is_BossEmpty())//赢了
		return 2;
	++BossA_move;
	++BossA_attack;
	++UserMoveCount;
	++UserAttackCount;
	++Boss_special;
	++CallSpeed;
	return 0;
}

bool ControlWhole::Boss_StageA(int numBoss,int numSoldier,int time_value,int call_num)
{
	Sleep(2500);
	PlayBossBase();
	center.AddBossTank(numBoss);
	center.AddEveTank(numSoldier);
	BeginBatchDraw();
	if (user_move_speed <= 2)//移动速度太快没意思
		user_move_speed = 3;
	int timeClock = time_value;
	while (1)
	{
		ScenceSet();
		int temp = NGame2(center, Boss_move_speed, Boss_attack_speed, user_attack_speed, user_move_speed, CallSoldier_speed,BossSpecial_speed,Call_num);
		if (temp == 1)
			break;
		else if (temp == 2)
		{
			LevelWin();
			EndBatchDraw();
			return true;
		}
		else if (temp == 3)
		{
			if (Life_num > 0)
			{
				--Life_num;
				center.AddUserTank();
			}
			else
			{
				DiaplayGameOver();
				EndBatchDraw();
				return false;
			}
		}
		if (center.Is_GetProps())
			--timeClock;
		if (timeClock < 0)
		{
			timeClock = time_value;
			center.RecoveryNormal();
		}
		center.DrawProps();
		center.BulletRun();
		center.DisplayAuto(NOTSRCERASE);
		HowAboutLife(Life_num, center.GetNumberDead(),center.GetCurrHP());
		FlushBatchDraw();
		Sleep(5);
		cleardevice();
		/*clearrectangle(500, NUMPOS - 10, graph_x2, NUMPOS + 50);
		clearrectangle(graph_x1, graph_y1, graph_x2, graph_y2);*/
	}
}

bool ControlWhole::CombainationA()
{
	if (Soldier_Stage())
		if (Boss_StageA())
			return true;
	return false;
}

void ControlWhole::DeleteAllEve()
{
	center.KillAllEVE();
}

