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
	list<int *> direction;//ÿ�����˵ķ���
	list<int *> count;//ÿ������Ҫ����òŻ�����
	list<EVETank *> OtherTank;//�з�̹�ˣ��󻰣�������������Ӧ����һ����װ�����ŷŵ�������ȽϺã���Ϊ���Ƕ��ǰ󶨵ģ�ͬʱ���֣�ͬʱ��ʧ��
	list<Bullet_Biu *> AllBullet;
	list<TankType*> FriendTank;
	int NumberDead;//ɱ����
	int px;//������߳��ֵĺ�����
	int py;//������߳��ֵ�������
	list<int >Increation;//��һ������װ�Ÿ�������buff
	IMAGE BGImage1;//����ͼ
public:
	ControlCenter(list<EVETank> Other);
	ControlCenter(): NumberDead(0), Increation(false), Increation_HP(10), Increation_HurtHP(2), Increation_speed(2){ loadimage(&BGImage1, "bgm\\bg1.jpg");}
	void RuningTime();//�������˶�
	void DisplayAuto(DWORD defa = SRCPAINT);//��ʾ����
	void FireBullet(TankType &Tank);//��ǹ
	void BulletRun();//�ӵ����˶�
    bool KillTank(Bullet_Biu* it_bullet);//����ж��ӵ���ǰλ���Ƿ����̹��
	void AutoAttack();//���˵�ǹ�ķ���������Ļ��ͻῪ��
	bool Is_EveEmpty() const { return OtherTank.empty(); }//�жϵ����Ƿ����
	bool Is_UserEmpty() const;//�ж�����Ƿ�����
	void AddEveTank(int num =1);//���ӵз�̹��
	void AddFriendTank(int num = 1);
	void AddUserTank();
	void UserAttack();//��ҹ���
	void UserMove(char ch);//����ƶ�
	int GetNumberDead() const { return NumberDead; }
	void AddBossTank(int num=1);//����BOSS̹��
	void AimAttack();//��������Խ���
	void FireDirBullet(TankType& Aim, TankType& mine);//��ĳ���������ӵ�
	void AimMove();//������ƶ�
	void KillAllEVE();//��ɱȫ��
	bool Is_BossEmpty();//boss������
	void AppearProps();//��������
	void DrawProps();//��ʾ����
	bool Is_GetProps();//�����Ƿ��Ѿ���ȡ��
	void RecoveryNormal();//ȥ��buff
	int GetCurrHP();//��õ�ǰhp
	int Increation_HP;//hp����
	int Increation_HurtHP;//�˺�����
	int Increation_speed;//�ƶ��ٶ�����
};


#endif // !CONTROLCENTER_H




