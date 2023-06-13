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

void AI::AI_go_newHand()//新手难度
{
	/*AI走棋采用评分制，经分析（不考虑跳子的技巧，即本AI难度仅为新手难度）
	AI的活三比黑棋的活三分数高
	黑棋的死三要比AI的死三分数高
	综合:
	棋形		黑棋		白棋
	连2			10			10
	死3			30			25
	活3			40			50
	死4			60			55
	活4			200			10000
	连5			20000		30000
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
	////落子
	//chess->ChessPlace(&pos, CHESS_WHITE);
	ChessPos pos=think();
	Sleep(800);//休眠0.8秒，假装思考
	chess->ChessPlace(&pos, CHESS_WHITE);
}

void AI::AI_go_middleBrow()//中等难度
{
}

void AI::AI_go_higherSkilled()//大师难度
{
}

void AI::CalculateScore()
{
	int BLACKNUMBER = 0;//黑白棋有多少个连续棋子
	int WHITENUMBER = 0;
	int EMPTYNUMBER = 0;//该方向的空白位置多少个

	//评分向量组置零
	for (int i = 0; i < ValueMap.size(); i++)
	{
		for (int j = 0; j < ValueMap.size(); j++)
		{
			ValueMap[i][j] = 0;
		}
	}
	int size = this->chess->GetSize();
	//计算每个点的得分情况  并把它们存储在ValueMap中
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{

			if (this->chess->GetData(x, y))continue;//continue 跳出循环

			/*控制方向 以（x，y）为中心的九宫格 r为负 代表向上数 r为正 代表向下数
              ——————————————>(x轴)
			 丨
			 丨        *
			 丨          *
			 丨            *
			 丨  
			 丨 
			 丨
			（y轴）
			                       */			
			for (int r = -1; r <= 1; r++)
			{
				for (int c = -1;c <= 1; c++)
				{
					if (c == 0 && r == 0)continue;
					//若（c，r）为黑子，判断此刻棋形
					//每次计算之前重置数据
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

					////若（c，r）为白子，判断此刻棋形
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
	/*新手难度，能够考虑一部分Player的跳子行为 在计算点值时仅计算一个方向
	  但AI不能实现跳子行为
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
			//遍历所有棋盘的所有点
			//当扫描的点为黑棋时候：计算每个点的价值

		//实际上 当（i，j）处为黑子或白子的时候计算分数无意义 只计算中心棋子为空时能简化计算量
				//设置方向向量

			//考虑周围是黑子的情况
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

			//考虑周围是白子 累加赋分;
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
	//总体上仍然采取积分制 不过在AI在计算一次分数后 再进行一次模拟 模拟出棋手可能下的位置
	
	//模拟一次Player落子位置 再次计算分数，之后再让AI落子，以达到AI能够跳子的技术。

	/* 以Player角度第一次计算分数  */
	int BLACKNUMBER = 0,WHITENUMBER=0,EMPTYNUMBER=0;
	/* 遍历棋盘 */
	for (int x = 0; x < this->chess->GetSize(); x++)
	{
		for (int y = 0; y < this->chess->GetSize(); y++)
		{
			if (this->chess->GetData(x, y) == 0)//仅计算空白棋子位置
			{

			}
		}
	}
	/* 模拟Player落子位置 */
	int tempX, tempY;//记录模拟的Player落子位置

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

	/* 下面是一个菜鸟级别的AI接口 */
	CalculateScore();

	/* 下面是一个新手级别的AI接口 */
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
