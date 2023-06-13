#pragma once
#include"Chess.h"
//#include<vector>
class AI
{
public:
	//��ʼ��
	void init(Chess *c);
	//AI������
	void AI_go_newHand();
	void AI_go_middleBrow();
	void AI_go_higherSkilled();

private:
	Chess* chess;
	//����AI���� Ҫ��AIȥ˼�������̣�13��13����ÿ����ġ���ֵ����С����AI�ڼ�ֵ���ĵ㴦����
	vector<vector<int>> ValueMap;

	

	//��������ĺ���
	void CalculateScore();

	void Cal_go_newHand();

	void Cal_go_middleBrow();

	ChessPos think();
};
