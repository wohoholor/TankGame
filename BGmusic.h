#pragma once
#ifndef BGMUSIC_H
#define BGMUSIC_H
#include<Windows.h>
#include<mmsystem.h>

#pragma comment(lib,"Winmm.lib")


void PlayBeginSound();
void PlayGameOver();
void PlayBase();
void PlayBossBase();
void PlayVictorySound();
void PlayEndSound();
void ThreadSound();









#endif // !BGMUSIC_H
