#pragma once
#include"Player.h"
#include"AI.h"
#include"Chess.h"
//棋局游戏控制端
class GameContron
{
public:
	GameContron(Player* p, AI* a, Chess* c);
	void play();//开始对局！！

private:
	//私有成员
	Player* player;
	AI* ai;
	Chess* chess;
};
