#pragma once
#ifndef DRAWANDKEY_H
#define DRAWANDKEY_H
#include<vector>
#include <graphics.h>
#include <conio.h>
#include <Windows.h>
#include <math.h>
#include <string>
#include <thread>
#include "ControlCenter.h"
#include "BGmusic.h"
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
#define PI 3.1415927
#define NUMPOS 700
#define EVESLOWSPEED 10
#define USERMOVESLOWSPEED 5
#define USERBULLETSLOWSPEED 20

void ScenceSet();//���ó���
void HowAboutLife(int count, int numKill,int hp);//������������ʾ
void heart(int x0, int y0, int size, COLORREF C);//������
void draw_Five(int x, int y, int r, COLORREF C, COLORREF BG);//������ǵĺ���
void BeforePlay();//��֮ǰ����Ϸ����
void NewVersion3();
bool FuntionButton(ControlCenter& center);//������������ť����
void MoveButton(ControlCenter& center);//�ƶ���ť����
void DiaplayWin();//��ʾӮ�Ļ���
void DiaplayGameOver();//��ʾ���˵Ļ���
void LevelWin();//�׶���ʤ������
void ThankList();//��л
bool IfYouDead();//���˵Ļ���
void PauseAll();//��ͣ

#endif // !DRAWANDKEY_H

