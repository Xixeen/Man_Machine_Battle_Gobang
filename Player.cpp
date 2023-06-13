#include "Player.h"
#include<iostream>
using namespace std;
void Player::init(Chess* c)
{
	this->chess = c;
}
void Player::Player_go()
{
	//获取鼠标消息
	MOUSEMSG msg;
	msg.x, msg.y;
	ChessPos pos;
	//判断落子是否有效,以及落子功能
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
		cout << "无效点击！" << endl;
	}*/
	if(chess->ClickBoard(msg.x,msg.y,&pos))
	{
		std::cout << pos.x << " , " << pos.y << endl;
	}
	chess->ChessPlace(&pos,CHESS_BLACK);
	
}
