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

void ScenceSet();//设置场景
void HowAboutLife(int count, int numKill,int hp);//生命条数的显示
void heart(int x0, int y0, int size, COLORREF C);//画心形
void draw_Five(int x, int y, int r, COLORREF C, COLORREF BG);//画五角星的函数
void BeforePlay();//玩之前的游戏界面
void NewVersion3();
bool FuntionButton(ControlCenter& center);//攻击或其它按钮按下
void MoveButton(ControlCenter& center);//移动按钮按下
void DiaplayWin();//显示赢的画面
void DiaplayGameOver();//显示输了的画面
void LevelWin();//阶段性胜利画面
void ThankList();//致谢
bool IfYouDead();//死了的画面
void PauseAll();//暂停

#endif // !DRAWANDKEY_H

