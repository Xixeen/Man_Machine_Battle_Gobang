#include "GameContron.h"


GameContron::GameContron(Player* p, AI* a, Chess* c)
{
	this->player = p; this->ai = a; this->chess = c;
	p->init(c);
	a->init(c);
}
//Link Start！（刀剑乱入）
void GameContron::play()
{
	//初始化棋盘
	chess->init();

	while (1)
	{
		//默认玩家先走；
		player->Player_go();
		if (this->chess->OverCheck())
		{
			chess->init();//更新棋盘数据
			continue;
		}
		ai->AI_go_newHand();
		if (this->chess->OverCheck())
		{
		
			chess->init();//更新棋盘数据
		//	ai->init(chess);
			continue;
		}

	}
}
