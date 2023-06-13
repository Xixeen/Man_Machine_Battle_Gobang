#include "Chess.h"
#include<mmsystem.h>
#include<iostream>
#pragma comment(lib,"winmm.lib")
//�������ṩһ�����ֲ��ŵĹ���
using namespace std;
Chess::Chess(int MapSize, int Bound_x, int Bound_y, float PieceSize)
{
    this->MapSize = MapSize;
    this->Bound_x = Bound_x;
    this->Bound_y = Bound_y;
    this->PieceSize = PieceSize;
    //��ʱĬ��Player����
    this->PlayerFlag = CHESS_BLACK;

    for (int i = 0; i < MapSize; i++)
    {
        vector<int> row;
        for (int j = 0; j < MapSize; j++)
        {
            row.push_back(0);//����0��ԭ����ÿ����ֿ�ʼ��Ҫ�������!
        }
        this->Map.push_back(row);
    }
}

void Chess::init()
{
    //ʹ��ͼ�ο⣬��ʾ���̣����� ��easyx��
    

    //������Ϸ����
    initgraph(900, 895, EW_SHOWCONSOLE);

    //��ʾ����ͼƬ
    loadimage(0, "GoBang/pic/����3.png");

    //���ſ�ʼ��ʾ����
    mciSendString("play GoBang/mus/ReadyGo.wav", 0, 0, 0);

    //���غڰ�����
    loadimage(&BlackPiece, "GoBang/pic/black01.png",PieceSize,PieceSize,true);

    loadimage(&WhitePiece, "GoBang/pic/white.png", PieceSize, PieceSize, true);

    //��������
    //for (int i = 0; i < Map.size(); i++)
    //{
    //    //vector<int>m1 =0;
    //    for (int j = 0; j < Map.size(); j++)
    //    {
    //        Map[i][j] = 0;
    //    }
    //}

    PlayerFlag = 1;

}

bool Chess::ClickBoard(int x, int y, ChessPos* p)
{
    //�趨��ֵ
    float threshold = PieceSize * 0.4;
    ret = false;
    //�ж����Ͻ�
    int x1 = (x - this->Bound_x) / this->PieceSize;
    int y1= (y - this->Bound_y) / this->PieceSize;
    float dir1 = pow(pow(abs(x - (x1 * this->PieceSize+ this->Bound_x)), 2) + pow(abs(y - (y1 * this->PieceSize+ this->Bound_y)), 2),1.0 / 2);
   
    //�ж����Ͻ�
    int x2 = (x - this->Bound_x) / this->PieceSize+1;
    int y2 = (y - this->Bound_y) / this->PieceSize;
    float dir2 = pow(pow(abs(x - (x2 * this->PieceSize+ this->Bound_x)), 2) + pow(abs(y - (y2 * this->PieceSize+ this->Bound_y)), 2), 1.0 / 2);
    
    
    //�ж����½�
    int x3 = (x - this->Bound_x) / this->PieceSize;
    int y3 = (y - this->Bound_y) / this->PieceSize +1 ;
    float dir3 = pow(pow(abs(x - (x3 * this->PieceSize+ this->Bound_x)), 2) + pow(abs(y - (y3 * this->PieceSize+ this->Bound_y)), 2), 1.0 / 2);
    
    //�ж����½�
    int x4 = (x - this->Bound_x) / this->PieceSize + 1;
    int y4 = (y - this->Bound_y) / this->PieceSize + 1;
    float dir4 = pow(pow(abs(x - (x4 * this->PieceSize+ this->Bound_x)), 2) + pow(abs(y - (y4 * this->PieceSize+ this->Bound_y)), 2), 1.0 / 2);
    
        if (dir1 < threshold&&x1>=0&&y1>=0)
        {
            p->x = x1; p->y = y1;
            if (Map[x1][y1] == 0)
            {
                ret = true;
            }
        }
        if (dir2 < threshold&&x2>=0&&y2>=0)
        {
            p->x = x2; p->y = y2;
            if (Map[x2][y2] == 0)
            {
                ret = true;
            }
        }
        if (dir3 < threshold&&x3>=0&&y3>=0)
        {
            p->x = x3; p->y = y3;
            if (Map[x3][y3] == 0)
            {
                ret = true;
            }
        }
        if (dir4 < threshold && x4>=0 && y4 >= 0)
        {
            p->x = x4; p->y = y4;
            if (Map[x4][y4] == 0)
            {
                ret = true;
            }
        }
    
    return ret;
}

void Chess::ChessPlace(ChessPos * s, ChessKind val)
{
    int Down_x = this->Bound_x + (s->x - 0.5) * this->PieceSize;
    int Down_y = this->Bound_y + (s->y - 0.5) * this->PieceSize;

    //��������


    if (val == CHESS_WHITE&&Map[s->x][s->y]==0)
    {
        putimage(Down_x, Down_y, &WhitePiece);
        Map[s->x][s->y] = -1;
    }
    if (val == CHESS_BLACK && Map[s->x][s->y] == 0)
    {
        putimage(Down_x, Down_y, &BlackPiece);
        Map[s->x][s->y] = 1;
    }

}

int Chess::GetSize()
{
    return this->MapSize;
}

int Chess::GetData(ChessPos* pos)
{
    return Map[pos->x][pos->y];
}

int Chess::GetData(int row, int col)
{
    return Map[row][col];
}

bool Chess::Judge(int x, int y)
{
    if (x >= 0 && x < this->GetSize() && y >= 0 && y < this->GetSize())return true;
    else return false;
}

bool Chess::OverCheck()
{
    //�����������е�λ
    int BLACKNUMBER = 0;
    int WHITENUMBER = 0;
    int index = 1;
    //int key = 0;
    for (int i = 0; i < this->MapSize; i++)
    {
        for (int j = 0; j < this->MapSize; j++)
        {

            if (this->GetData(i, j) == 0)continue;
            //����Player
            else if (this->GetData(i, j) == 1)
            {
                //���Ʒ���
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                        //��������
                        BLACKNUMBER = 0;
                        WHITENUMBER = 0;
                        index = 1;
                        if (this->Judge(i + x * index, j + y * index) && this->GetData(i + x * index, j + y * index) == 1)BLACKNUMBER++;
                        else if (this->Judge(i + x * index, j + y * index) && this->GetData(i + x * index, j + y * index) == -1)WHITENUMBER++;
                        if (BLACKNUMBER == 5)
                        {
                            i = this->MapSize; j = this->MapSize; return true;
                        }
                        if(WHITENUMBER==5)
                        {
                            i = this->MapSize; j = this->MapSize; return true;
                        }
                    }
                }

            }





        }
    }


    return false;
}
