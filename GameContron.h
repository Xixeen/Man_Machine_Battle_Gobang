#pragma once
#include"Player.h"
#include"AI.h"
#include"Chess.h"
//�����Ϸ���ƶ�
class GameContron
{
public:
	GameContron(Player* p, AI* a, Chess* c);
	void play();//��ʼ�Ծ֣���

private:
	//˽�г�Ա
	Player* player;
	AI* ai;
	Chess* chess;
};
