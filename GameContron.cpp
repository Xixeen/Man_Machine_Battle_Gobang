#include "GameContron.h"


GameContron::GameContron(Player* p, AI* a, Chess* c)
{
	this->player = p; this->ai = a; this->chess = c;
	p->init(c);
	a->init(c);
}
//Link Start�����������룩
void GameContron::play()
{
	//��ʼ������
	chess->init();

	while (1)
	{
		//Ĭ��������ߣ�
		player->Player_go();
		if (this->chess->OverCheck())
		{
			chess->init();//������������
			continue;
		}
		ai->AI_go_newHand();
		if (this->chess->OverCheck())
		{
		
			chess->init();//������������
		//	ai->init(chess);
			continue;
		}

	}
}
