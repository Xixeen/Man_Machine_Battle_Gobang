/*
  1������˼·��

  ��Ŀ��ܣ�Player����ң� Chess�����̣� AI�������ˣ�
							chessGame����Ϸ���ƣ�


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