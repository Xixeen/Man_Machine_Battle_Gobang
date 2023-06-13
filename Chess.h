#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
struct ChessPos
{
	int x;
	int y;

	//дһ��Ĭ�Ϲ���
	ChessPos(int x = 0, int y = 0) :x(x), y(y) {}
};

typedef enum
{
	CHESS_WHITE = -1,
	CHESS_BLACK = 1
}ChessKind;

class Chess
{
public:
	Chess(int MapSize, int Bound_x, int Bound_y, float PieceSize);
	//��ʼ�����̣��������̵�ͼƬ��Դ����ʼ���������
	void init();
	//�ж��Ƿ���Ч���ӣ������Ч���������x��y����ṹ������ж�
	bool ClickBoard(int x, int y, ChessPos* p);
	//���� (�У��У��ڰ�������)
	void ChessPlace(ChessPos *s,ChessKind val);
	//��ȡ���̴�С��13��15��19��
	int GetSize();
	//��ȡ������Ϣ�����壿���壿�գ�
	int GetData(ChessPos* pos);
	int GetData(int row, int col);//���ذ汾

	//�Ż����� �ж����ӵ�X��Y�����Ƿ�Ϸ�
	bool Judge(int x, int y);
	//�������Ƿ����
	bool OverCheck();
private:
	bool ret = false;
	IMAGE BlackPiece;//��������
	IMAGE WhitePiece;//��������


	int MapSize;//���̴�С��13��15��17��19��
	int Bound_x;//������߽�
	int Bound_y;//�����ϱ߽�
	float PieceSize;//���Ӵ�С������С�����С��
	

	// �洢��ǰ��ֵ����ӷֲ����ݣ� 0���հף�1�����ӣ�-1������
	vector<vector<int>> Map;

	//��ʾ�����ֵ�˭����
	bool PlayerFlag;//true:���ӣ� false:����


};