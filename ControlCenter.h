#pragma once
#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H
#include "TankType.h"
#include "Bullet_Biu.h"
#include <list>
#include <mutex>
using namespace std;


class ControlCenter
{
	list<int *> direction;//每个敌人的方向
	list<int *> count;//每个敌人要隔多久才换方向
	list<EVETank *> OtherTank;//敌方坦克（后话：这三个东西都应该用一个类装起来才放到链表里比较好，因为他们都是绑定的，同时出现，同时消失）
	list<Bullet_Biu *> AllBullet;
	list<TankType*> FriendTank;
	int NumberDead;//杀敌数
	int px;//随机道具出现的横坐标
	int py;//随机道具出现的纵坐标
	list<int >Increation;//用一个链表装着各种增益buff
	IMAGE BGImage1;//背景图
public:
	ControlCenter(list<EVETank> Other);
	ControlCenter(): NumberDead(0), Increation(false), Increation_HP(10), Increation_HurtHP(2), Increation_speed(2){ loadimage(&BGImage1, "bgm\\bg1.jpg");}
	void RuningTime();//敌人能运动
	void DisplayAuto(DWORD defa = SRCPAINT);//显示画面
	void FireBullet(TankType &Tank);//开枪
	void BulletRun();//子弹能运动
    bool KillTank(Bullet_Biu* it_bullet);//如果判断子弹当前位置是否打中坦克
	void AutoAttack();//敌人的枪的方向上有你的话就会开炮
	bool Is_EveEmpty() const { return OtherTank.empty(); }//判断敌人是否清空
	bool Is_UserEmpty() const;//判断玩家是否死亡
	void AddEveTank(int num =1);//增加敌方坦克
	void AddFriendTank(int num = 1);
	void AddUserTank();
	void UserAttack();//玩家攻击
	void UserMove(char ch);//玩家移动
	int GetNumberDead() const { return NumberDead; }
	void AddBossTank(int num=1);//增加BOSS坦克
	void AimAttack();//启用针对性进攻
	void FireDirBullet(TankType& Aim, TankType& mine);//对某个方向发射子弹
	void AimMove();//针对性移动
	void KillAllEVE();//秒杀全场
	bool Is_BossEmpty();//boss死了吗
	void AppearProps();//产生道具
	void DrawProps();//显示道具
	bool Is_GetProps();//道具是否已经被取走
	void RecoveryNormal();//去掉buff
	int GetCurrHP();//获得当前hp
	int Increation_HP;//hp增益
	int Increation_HurtHP;//伤害增益
	int Increation_speed;//移动速度增益
};


#endif // !CONTROLCENTER_H




