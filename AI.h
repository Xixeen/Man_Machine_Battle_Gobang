#pragma once
#include"Chess.h"
//#include<vector>
class AI
{
public:
	//初始化
	void init(Chess *c);
	//AI的落子
	void AI_go_newHand();
	void AI_go_middleBrow();
	void AI_go_higherSkilled();

private:
	Chess* chess;
	//对于AI走棋 要让AI去思考这棋盘（13×13）中每个点的“价值”大小，让AI在价值最大的点处落子
	vector<vector<int>> ValueMap;

	

	//计算分数的函数
	void CalculateScore();

	void Cal_go_newHand();

	void Cal_go_middleBrow();

	ChessPos think();
};
