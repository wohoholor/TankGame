#pragma once
#ifndef CONTROLWHOLE_H
#define CONTROLWHOLE_H
#include "ControlCenter.h"
#include <vector>

class ControlWhole
{
	ControlCenter &center;
	int user_move_speed;
	int user_attack_speed;
	int eve_move_speed;
	int eve_attack_speed;
	int Boss_move_speed;
	int Boss_attack_speed;//
	int Life_num;//生命条数
	vector<int> TurnNum;//用一个vector来装多个关卡的小兵数量（1，3，5，6表示一个四关，每个关卡小兵数量为1，3，5，6）
	bool AutoChangeSpeed;//随着游戏关卡的进行，是否逐渐提高玩家移动速度
	int BossSpecial_speed;//BOSS特殊技能的CD
	int CallSoldier_speed;//BOSS召唤技能的CD
	int Call_num;//BOSS每次能召唤几个兵
public:
	ControlWhole(ControlCenter& cen) : center(cen), user_move_speed(5), user_attack_speed(15), eve_move_speed(8), eve_attack_speed(25), Life_num(5), AutoChangeSpeed(true), Boss_move_speed(7),Boss_attack_speed(10), BossSpecial_speed(500), CallSoldier_speed(1000), Call_num(2){ TurnNum = { 3,5,10,20 }; center.AddUserTank(); }
	bool NormalGame(int EveNum,int time_value = 4000);//time_value为buff持续时间
	bool Soldier_Stage(vector<int> vec);
	bool Soldier_Stage();
	bool Boss_StageA(int numBoss = 1, int numSoldier = 5,int time_value=4000,int call_num =2);
	bool CombainationA();
	void DeleteAllEve();

};



#endif // !CONTROLWHOLE_H



