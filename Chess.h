#pragma once
#include<graphics.h>
#include<vector>
using namespace std;
struct ChessPos
{
	int x;
	int y;

	//写一个默认构造
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
	//初始化棋盘，加载棋盘的图片资源，初始化相关数据
	void init();
	//判断是否有效落子，如果有效，将传入的x，y存入结构体进行判断
	bool ClickBoard(int x, int y, ChessPos* p);
	//落子 (行，列，黑白棋子数)
	void ChessPlace(ChessPos *s,ChessKind val);
	//获取棋盘大小（13，15，19）
	int GetSize();
	//获取落子信息：黑棋？白棋？空？
	int GetData(ChessPos* pos);
	int GetData(int row, int col);//重载版本

	//优化函数 判断棋子的X，Y坐标是否合法
	bool Judge(int x, int y);
	//检查棋局是否结束
	bool OverCheck();
private:
	bool ret = false;
	IMAGE BlackPiece;//黑棋棋子
	IMAGE WhitePiece;//白棋棋子


	int MapSize;//棋盘大小（13，15，17，19）
	int Bound_x;//棋盘左边界
	int Bound_y;//棋盘上边界
	float PieceSize;//棋子大小（棋盘小方格大小）
	

	// 存储当前棋局的棋子分布数据， 0：空白；1：黑子；-1：白子
	vector<vector<int>> Map;

	//表示现在轮到谁下棋
	bool PlayerFlag;//true:黑子， false:白子


};