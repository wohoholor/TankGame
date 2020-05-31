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
	int Life_num;//��������
	vector<int> TurnNum;//��һ��vector��װ����ؿ���С��������1��3��5��6��ʾһ���Ĺأ�ÿ���ؿ�С������Ϊ1��3��5��6��
	bool AutoChangeSpeed;//������Ϸ�ؿ��Ľ��У��Ƿ����������ƶ��ٶ�
	int BossSpecial_speed;//BOSS���⼼�ܵ�CD
	int CallSoldier_speed;//BOSS�ٻ����ܵ�CD
	int Call_num;//BOSSÿ�����ٻ�������
public:
	ControlWhole(ControlCenter& cen) : center(cen), user_move_speed(5), user_attack_speed(15), eve_move_speed(8), eve_attack_speed(25), Life_num(5), AutoChangeSpeed(true), Boss_move_speed(7),Boss_attack_speed(10), BossSpecial_speed(500), CallSoldier_speed(1000), Call_num(2){ TurnNum = { 3,5,10,20 }; center.AddUserTank(); }
	bool NormalGame(int EveNum,int time_value = 4000);//time_valueΪbuff����ʱ��
	bool Soldier_Stage(vector<int> vec);
	bool Soldier_Stage();
	bool Boss_StageA(int numBoss = 1, int numSoldier = 5,int time_value=4000,int call_num =2);
	bool CombainationA();
	void DeleteAllEve();

};



#endif // !CONTROLWHOLE_H



