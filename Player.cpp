#include "Player.h"
#include<iostream>
using namespace std;
void Player::init(Chess* c)
{
	this->chess = c;
}
void Player::Player_go()
{
	//��ȡ�����Ϣ
	MOUSEMSG msg;
	msg.x, msg.y;
	ChessPos pos;
	//�ж������Ƿ���Ч,�Լ����ӹ���
	while(1)
	{ 
		msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN && chess->ClickBoard(msg.x,msg.y,&pos))
			{ 
				break;
			}
	}
	/*if ()
	{
		cout << "��Ч�����" << endl;
	}*/
	if(chess->ClickBoard(msg.x,msg.y,&pos))
	{
		std::cout << pos.x << " , " << pos.y << endl;
	}
	chess->ChessPlace(&pos,CHESS_BLACK);
	
}
