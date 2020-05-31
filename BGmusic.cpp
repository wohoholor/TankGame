#include"BGmusic.h"


void PlayBeginSound()
{
	mciSendString("close bgm//BattleCity.wav", NULL, 0, 0);
	mciSendString("open bgm//BattleCity.wav", NULL, 0, 0);
	mciSendString("play bgm//BattleCity.wav", NULL, 0, 0);
}

void PlayGameOver()
{
	mciSendString("close bgm//Base.wav", NULL, 0, 0);
	mciSendString("close bgm//BaseBoss.wav", NULL, 0, 0);
	mciSendString("close bgm//GameOver.wav", NULL, 0, 0);
	mciSendString("open bgm//GameOver.wav", NULL, 0, 0);
	mciSendString("play bgm//GameOver.wav", NULL, 0, 0);
}

void PlayBase()
{
	mciSendString("close bgm//Base.wav", NULL, 0, 0);
	mciSendString("open bgm//Base.wav ", NULL, 0, 0);
	mciSendString("play bgm//Base.wav ", NULL, 0, 0);
}
void PlayBossBase()
{
	mciSendString("close bgm//BaseBoss.wav", NULL, 0, 0);
	mciSendString("open bgm//BaseBoss.wav", NULL, 0, 0);
	mciSendString("play bgm//BaseBoss.wav", NULL, 0, 0);
}
void PlayVictorySound()
{
	mciSendString("close bgm//Base.wav", NULL, 0, 0);
	mciSendString("close bgm//Victory.wav", NULL, 0, 0);
	mciSendString("open bgm//Victory.wav", NULL, 0, 0);
	mciSendString("play bgm//Victory.wav", NULL, 0, 0);
	Sleep(1000);
}
void PlayEndSound()
{
	mciSendString("close bgm//BaseBoss.wav", NULL, 0, 0);
	mciSendString("close bgm//Ending.wav", NULL, 0, 0);
	mciSendString("open bgm//Ending.wav", NULL, 0, 0);
	mciSendString("play bgm//Ending.wav", NULL, 0, 0);
}


void ThreadSound()
{
	mciSendString("close bgm//pconline.wav", NULL, 0, 0);
	mciSendString("open bgm//pconline.wav", NULL, 0, 0);
	mciSendString("play bgm//pconline.wav", NULL, 0, 0);
}