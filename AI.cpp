#include "AI.h"

void AI::init(Chess* c)
{
	this->chess = c;
	for (int i = 0; i < chess->GetSize(); i++)
	{
		vector<int>x;
		for (int j = 0; j < chess->GetSize(); j++)
		{
			x.push_back(0);
		}
		ValueMap.push_back(x);
	}
}

void AI::AI_go_newHand()//�����Ѷ�
{
	/*AI������������ƣ������������������ӵļ��ɣ�����AI�ѶȽ�Ϊ�����Ѷȣ�
	AI�Ļ����Ⱥ���Ļ���������
	���������Ҫ��AI������������
	�ۺ�:
	����		����		����
	��2			10			10
	��3			30			25
	��3			40			50
	��4			60			55
	��4			200			10000
	��5			20000		30000
	*/

	//this->CalculateScore();
	//ChessPos pos;

	//int MAX_X = 0, MAX_Y = 0;
	//for (int x = 0; x < this->chess->GetSize(); x++)
	//{
	//	for (int y = 0; y < this->chess->GetSize(); y++)
	//	{
	//		if (this->ValueMap[MAX_X][MAX_Y] < this->ValueMap[x][y])
	//		{
	//			MAX_X = x; MAX_Y = y;
	//		}
	//	}
	//}
	//pos.x = MAX_X; pos.y = MAX_Y;
	////����
	//chess->ChessPlace(&pos, CHESS_WHITE);
	ChessPos pos=think();
	Sleep(800);//����0.8�룬��װ˼��
	chess->ChessPlace(&pos, CHESS_WHITE);
}

void AI::AI_go_middleBrow()//�е��Ѷ�
{
}

void AI::AI_go_higherSkilled()//��ʦ�Ѷ�
{
}

void AI::CalculateScore()
{
	int BLACKNUMBER = 0;//�ڰ����ж��ٸ���������
	int WHITENUMBER = 0;
	int EMPTYNUMBER = 0;//�÷���Ŀհ�λ�ö��ٸ�

	//��������������
	for (int i = 0; i < ValueMap.size(); i++)
	{
		for (int j = 0; j < ValueMap.size(); j++)
		{
			ValueMap[i][j] = 0;
		}
	}
	int size = this->chess->GetSize();
	//����ÿ����ĵ÷����  �������Ǵ洢��ValueMap��
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{

			if (this->chess->GetData(x, y))continue;//continue ����ѭ��

			/*���Ʒ��� �ԣ�x��y��Ϊ���ĵľŹ��� rΪ�� ���������� rΪ�� ����������
              ����������������������������>(x��)
			 ح
			 ح        *
			 ح          *
			 ح            *
			 ح  
			 ح 
			 ح
			��y�ᣩ
			                       */			
			for (int r = -1; r <= 1; r++)
			{
				for (int c = -1;c <= 1; c++)
				{
					if (c == 0 && r == 0)continue;
					//����c��r��Ϊ���ӣ��жϴ˿�����
					//ÿ�μ���֮ǰ��������
					BLACKNUMBER = 0;
					WHITENUMBER = 0;
					EMPTYNUMBER = 0;

					for (int i = 1; i <= 4; i++)
					{
						int curY = y + i * r;
						int curX = x + i * c;
						if (this->chess->Judge(curY, curX) && this->chess->GetData(curY, curX) == 1)BLACKNUMBER++;
						else if (this->chess->Judge(curY, curX) && this->chess->GetData(curY, curX) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					for (int i = 1; i <= 4; i++)
					{
						int curY = y - i * r;
						int curX = x - i * c;
						if (this->chess->Judge( curY,curX) && this->chess->GetData(curY, curX) == 1)BLACKNUMBER++;
						else if (this->chess->Judge(curY, curX) && this->chess->GetData(curY, curX) == 0) { EMPTYNUMBER++; break; }
						else break;
					}

					if (BLACKNUMBER == 1)ValueMap[y][x] += 10;
					else if (BLACKNUMBER == 2)
					{
						if (EMPTYNUMBER == 1)ValueMap[y][x] += 30;
						else if (EMPTYNUMBER == 2)ValueMap[y][x] += 40;
					}
					else if (BLACKNUMBER == 3)
					{
						if (EMPTYNUMBER == 1)ValueMap[y][x] += 60;
						else if (EMPTYNUMBER == 2)ValueMap[y][x] += 200;
					}
					else if (BLACKNUMBER == 4)ValueMap[y][x] += 20000;

					////����c��r��Ϊ���ӣ��жϴ˿�����
					EMPTYNUMBER = 0;
					for (int i = 1; i <= 4; i++)
					{
						int curY = y + i * r;
						int curX = x + i * c;
						if (this->chess->Judge(curY, curX) && this->chess->GetData(curY, curX) == -1)WHITENUMBER++;
						else if (this->chess->Judge(curY, curX) && this->chess->GetData(curY, curX) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					for (int i = 1; i <= 4; i++)
					{
						int curY = y - i * r;
						int curX = x - i * c;
						if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == -1)WHITENUMBER++;
						else if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					
					if (WHITENUMBER == 0)ValueMap[y][x] += 5;
					else if (WHITENUMBER == 1)ValueMap[y][x] += 10;
					else if (WHITENUMBER == 2)
					{
						if (EMPTYNUMBER == 1)ValueMap[y][x] += 25;
						else if (EMPTYNUMBER == 2)ValueMap[y][x] += 50;
					}
					else if (WHITENUMBER == 3)
					{
						if (EMPTYNUMBER == 1)ValueMap[y][x] += 55;
						else if (EMPTYNUMBER == 2)ValueMap[y][x] += 10000;
					}
					else if (WHITENUMBER >= 4)ValueMap[y][x] += 30000;


				}
			}
		}
	}

}
//MyAlgorithm_newHand
void AI::Cal_go_newHand()
{
	/*�����Ѷȣ��ܹ�����һ����Player��������Ϊ �ڼ����ֵʱ������һ������
	  ��AI����ʵ��������Ϊ
								*/
	int BLACKNUMBER = 0;
	int WHITENUMBER = 0;
	int EMPTYNUMBER = 1;
	for (int i = 0; i < ValueMap.size(); i++)
	{
		for (int j = 0; j < ValueMap.size(); j++)
		{
			ValueMap[i][j] = 0;
		}
	}

	for (int i = 0; i < this->ValueMap.size(); i++)
	{
		for (int j = 0; j < ValueMap.size(); j++)
		{
			//�����������̵����е�
			//��ɨ��ĵ�Ϊ����ʱ�򣺼���ÿ����ļ�ֵ

		//ʵ���� ����i��j����Ϊ���ӻ���ӵ�ʱ�������������� ֻ������������Ϊ��ʱ�ܼ򻯼�����
				//���÷�������

			//������Χ�Ǻ��ӵ����
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					BLACKNUMBER = 0;
					WHITENUMBER = 0;
					EMPTYNUMBER = 1;
					if (x == 0 && y == 0)continue;
					for (int index = 1; index <= 4; index++)
					{
						int curX = i + x * index;
						int curY = j + y * index;
						if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 1)BLACKNUMBER++;
						else if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					for (int index = 1; index <= 4; index++)
					{
						int curX = i - x * index;
						int curY = j - y * index;
						if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 1)BLACKNUMBER++;
						else if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					if (BLACKNUMBER == 1)ValueMap[i][j] += 10;
					else if (BLACKNUMBER == 2)
					{
						if (EMPTYNUMBER == 2)ValueMap[i][j] += 30;
						else if (EMPTYNUMBER == 3)ValueMap[i][j] += 40;
					}
					else if (BLACKNUMBER == 3)
					{
						if (EMPTYNUMBER == 2)ValueMap[i][j] += 60;
						else if (EMPTYNUMBER == 3)ValueMap[i][j] += 2000;
					}
					else if (BLACKNUMBER == 4)ValueMap[i][j] += 80000;
				}
			}

			//������Χ�ǰ��� �ۼӸ���;
			for (int x = -1; x <= 1; x++)
			{
				for (int y = -1; y <= 1; y++)
				{
					BLACKNUMBER = 0;
					WHITENUMBER = 0;
					EMPTYNUMBER = 1;
					if (x == 0 && y == 0)continue;
					for (int index = 1; index <= 4; index++)
					{
						int curX = i + x * index;
						int curY = j + y * index;
						if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == -1)WHITENUMBER++;
						else if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					for (int index = 1; index <= 4; index++)
					{
						int curX = i - x * index;
						int curY = j - y * index;
						if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 1)BLACKNUMBER++;
						else if (this->chess->Judge(curX, curY) && this->chess->GetData(curX, curY) == 0) { EMPTYNUMBER++; break; }
						else break;
					}
					if (WHITENUMBER == 0)ValueMap[i][j] += 5;
					else if (WHITENUMBER == 1)ValueMap[i][j] += 10;
					else if (WHITENUMBER == 2)
					{
						if (EMPTYNUMBER == 2)ValueMap[i][j] += 25;
						else if (EMPTYNUMBER == 3)ValueMap[i][j] += 500;
					}
					else if (WHITENUMBER == 3)
					{
						if (EMPTYNUMBER == 2)ValueMap[i][j] += 1000;
						else if (EMPTYNUMBER == 3)ValueMap[i][j] += 10000;
					}
					else if (WHITENUMBER >= 4)ValueMap[i][j] += 100000;
				}
			}
		}
	}
}

void AI::Cal_go_middleBrow()
{
	//��������Ȼ��ȡ������ ������AI�ڼ���һ�η����� �ٽ���һ��ģ�� ģ������ֿ����µ�λ��
	
	//ģ��һ��Player����λ�� �ٴμ��������֮������AI���ӣ��ԴﵽAI�ܹ����ӵļ�����

	/* ��Player�Ƕȵ�һ�μ������  */
	int BLACKNUMBER = 0,WHITENUMBER=0,EMPTYNUMBER=0;
	/* �������� */
	for (int x = 0; x < this->chess->GetSize(); x++)
	{
		for (int y = 0; y < this->chess->GetSize(); y++)
		{
			if (this->chess->GetData(x, y) == 0)//������հ�����λ��
			{

			}
		}
	}
	/* ģ��Player����λ�� */
	int tempX, tempY;//��¼ģ���Player����λ��

}

ChessPos AI::think()
{

	/*for (int i = 0; i < this->ValueMap.size(); i++)
	{
		for (int j = 0; j < this->ValueMap.size(); j++)
		{
			ValueMap[i][j] = 0;
		}
	}*/

	/* ������һ�����񼶱��AI�ӿ� */
	CalculateScore();

	/* ������һ�����ּ����AI�ӿ� */
	Cal_go_newHand();
	//ValueMap[6][6] = 100;
	vector<ChessPos> maxPoints;

	int MAXSCORE = 0;
	
	for (int x = 0; x < this->chess->GetSize(); x++)
	{
		for (int y = 0; y < this->chess->GetSize(); y++)
		{
			if (this->chess->Judge(x, y) && this->chess->GetData(x, y) == 0)
			{
				if (this->chess->GetData(x, y) == 0)
				{
					if (ValueMap[x][y] > MAXSCORE)
					{
						MAXSCORE = ValueMap[x][y];
						maxPoints.clear();
						maxPoints.push_back(ChessPos(x, y));
					}
					else if (ValueMap[x][y] == MAXSCORE)
					{
						maxPoints.push_back(ChessPos(x, y));
					}
				}
			}
		}
	}

	int index = rand() % maxPoints.size();


	return maxPoints[index];
}
