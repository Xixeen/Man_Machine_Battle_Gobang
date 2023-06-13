/*
  1、开发思路：

  项目框架：Player（玩家） Chess（棋盘） AI（机器人）
							chessGame（游戏控制）


*/
#include<iostream>
#include"GameContron.h"
using namespace std;

int main(void)
{
	Player player;
	AI ai;
	Chess chess(19,52,50,43);
	GameContron game(&player,&ai,&chess);
	game.play();//Link Start!

	return 0;
}