// C++ 控制台版本2048  
// 运行环境windows，因为包含了Windows.h 和Windows控制台API
// 所以linux下需要针对终端进行优化
// Email->lqkisme@163.com
// Author : lqkisme

#include "pch.h"
#include <iostream>
#include<cstdlib>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
#include <ctime>
#include "2048.h"
using namespace std;

Game::Game()
{
	this->Tips = { "提示：" };
}
void Game::Print()
{
	time_t tt = time(NULL);
	tm t;//时间结构体
	localtime_s(&t, &tt);//获取时间
	int hour, sec, min;
	hour = t.tm_hour;
	min = t.tm_min;
	sec =t.tm_sec;
	cout <<"         This time is  "<<hour<<"时"<<min<<"分"<<sec<<"秒"<<endl;
	cout << "            2048 made by lqkisme" << endl;
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		cout << "          |-----|-----|-----|-----|" << endl;
		cout << "          ";
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			
			if (this->BoardList[i][j] != 0)
			{
				cout <<"| "<<setw(3)<< setiosflags(ios::left)
					<<this->BoardList[i][j]<<" ";
				
			}
			else
			{
				cout<< "| "<<setw(3) << setiosflags(ios::left) << " "<<" ";
			}
		}
		cout << "|"<<endl;
	}
	cout << "          |-----|-----|-----|-----|" << endl<<endl;
	cout << "    分数:" << this->Scroe << endl;
	cout << "《--------------------请按照提示进行游戏----------------------》" << endl;
	cout << this->Tips << endl<<endl;;
	cout <<"     请按" << "↑" << "↓" << "←" << "→" << "移动"<<endl;
	cout <<"     按Q或者Esc退出" << endl;
	cout <<"     按R复位" << endl;
}

bool Game::Input()
{
	int ch;
	if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
		ch = _getch();//使用_getch()函数获取按下的键值
		switch (ch)
		{
		case 27:return true;
		case 113: &this->Tips.assign("退出！"); return true; 
		case 114: this->Restart(); break;//复位
		case 80:this->Down(); break;//xia
		case 75: this->Left(); break;//zuo
		case 72: this->Up(); break;//shang
		case 77: this->Right(); break;//右
		default:
			return false;

		}
	}
	return false;
}

bool Game::LOSE()
{
	bool lose=true;//标志位
	//出现0，表示还未结束
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			
			if (this->BoardList[i][j] == 0)
			{
				lose = false;
				return false;		
			}
		}
	}
	//横竖相邻元素相等未结束
	for (size_t i = 0; i < size(this->BoardList) - 1; i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]) - 1; j++)
		{
			if (this->BoardList[i][j]== this->BoardList[i][j+1]&& this->BoardList[i][j]!=0)
			{
				return false;
			}
			if (this->BoardList[j][i]== this->BoardList[j+1][i]&& this->BoardList[j][i]!=0)
			{
				lose = false;
				return false;
			}
		}
	}
	if (lose)
	{
		&this->Tips.assign(" YOU LOSE !!!");
		return true;
	}
	return false;
}
bool Game::WIN()
{
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			//出现2048，即为赢
			if (this->BoardList[i][j]==2048)
			{
				&this->Tips.assign("YOU WIN !!!");
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}
bool Game::AddBoard()
{
	int choice[] = { 4, 2, 4, 4, 2, 2, 2, 2 };//可以调节2和4出现的频率
	//srand(time(0));
	int temp = (rand() % (size(choice) - 0)) + 0;
	int p1 = rand() % 4;
	int p2 = rand() % 4;
	while (this->BoardList[p1][p2] != 0)//位置已有数字，重新选取
	{
		p1 = rand() % 4;
		p2 = rand() % 4;
	}
	this->BoardList[p1][p2] = choice[temp];
	this->ADD = false;
	return true;
}
void Game::Up()
{
	for (size_t i = 0; i < size(this->BoardList[0]); i++)
	{
		for (size_t t = 0; t < size(this->BoardList[0]); t++)
		{
			for (size_t j = 0; j < size(this->BoardList) - 1; j++)
			{
				if (this->BoardList[j][i] == 0)
				{
					if (this->BoardList[j + 1][i]!=0)
					{
						this->ADD = true;
					}
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j + 1][i];
					this->BoardList[j + 1][i] = temp;
				}
			}
		}
		// 2、合并同类项
		for (size_t j = 0; j < size(this->BoardList[i]) - 1; j++)
		{
			// 2 2 2 2 ->4 0 2 2 ->4 0 4 0 
			// 2 2 2 0 -> 4 0 2 0 
			if (this->BoardList[j][i] == this->BoardList[j + 1][i])
			{
				if (this->BoardList[j][i]!=0)
				{
					this->ADD = true;
				}
				this->BoardList[j][i] = this->BoardList[j][i] * 2;
				this->Scroe = this->BoardList[j][i] + this->Scroe;
				this->BoardList[j + 1][i] = 0;
			}
		}
		//3、 再次移动0元素
		for (size_t t = 0; t < size(this->BoardList[0]); t++)
		{
			for (size_t j = 0; j < size(this->BoardList[t]) - 1; j++)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[j][i] == 0)
				{
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j + 1][i];
					this->BoardList[j + 1][i] = temp;
				}
			}
		}
	}
	if (this->LOSE() || this->WIN())
	{}
	else
	{
		if (this->ADD)
		{
			Sleep(50);
			this->AddBoard();
			this->ADD = false;
		}
	}
}

void Game::Down()
{
	for (size_t i = 0; i < size(this->BoardList[0]); i++)
	{
		for (size_t t = size(this->BoardList[0]); t>0; t--)
		{
			for (size_t j = size(this->BoardList) - 1; j >0; j--)
			{
				if (this->BoardList[j][i] == 0)
				{
					if (this->BoardList[j - 1][i] != 0)
					{
						this->ADD = true;
					}
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j - 1][i];
					this->BoardList[j - 1][i] = temp;
				}
			}
		}
		// 2、合并同类项
		for (size_t j = size(this->BoardList[i]) - 1; j>0; j--)
		{
			// 2 2 2 2 ->4 0 2 2 ->4 0 4 0 
			// 2 2 2 0 -> 4 0 2 0 
			if (this->BoardList[j][i] == this->BoardList[j - 1][i])
			{
				if (this->BoardList[j][i] != 0)
				{
					this->ADD = true;
				}
				this->BoardList[j][i] = this->BoardList[j][i] * 2;
				this->Scroe = this->BoardList[j][i] + this->Scroe;
				this->BoardList[j - 1][i] = 0;
			}
		}
		//3、 再次移动0元素
		for (size_t t = size(this->BoardList[0]); t >0; t--)
		{
			for (size_t j = size(this->BoardList[t]) - 1; j >0; j--)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[j][i] == 0)
				{
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j - 1][i];
					this->BoardList[j - 1][i] = temp;
				}
			}
		}
	}
	if (this->LOSE() || this->WIN())
	{}
	else
	{
		if (this->ADD)
		{
			Sleep(50);
			this->AddBoard();
			this->ADD = false;
		}
	}
}

void Game::Left()
{
	for (size_t j= 0; j < size(this->BoardList); j++)
	{
		//1、先移动每行0元素（出现0就交换）,最多交换size(this->BoardList)次
		for (size_t t = 0; t < size(this->BoardList); t++)
		{
			for (size_t i = 0; i < size(this->BoardList[t]) - 1; i++)
			{
				// 0 2 0 2 ->2 0 2 0
				if (this->BoardList[j][i] == 0)
				{
					// 发生了移动，添加棋子标志位置真
					if (this->BoardList[j][i + 1]!=0)
					{
						this->ADD = true;
					}
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j][i + 1];
					this->BoardList[j][i + 1] = temp;
				}
			}
		}
		// 2、合并同类项
		for (size_t i = 0; i < size(this->BoardList[j]) - 1; i++)
		{
			// 2 2 2 2 ->4 0 2 2 ->4 0 4 0 
			// 2 2 2 0 -> 4 0 2 0 
			if (this->BoardList[j][i]== this->BoardList[j][i+1])
			{
				// 发生了合并，添加棋子标志位置真
				if (this->BoardList[j][i]!=0)
				{
					this->ADD = true;
				}
				this->BoardList[j][i] = this->BoardList[j][i] * 2;
				this->Scroe = this->BoardList[j][i] + this->Scroe;
				this->BoardList[j][i + 1] = 0;
			}
		}
		//3、 再次移动0元素 4 0 2 0 -> 4 2 0 0 
		for (size_t t = 0; t < size(this->BoardList); t++)
		{
			for (size_t i = 0; i < size(this->BoardList[t]) - 1; i++)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[j][i] == 0)
				{
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j][i + 1];
					this->BoardList[j][i + 1] = temp;
				}
			}
		}
	}
	//赢了或者输了就不再添加
	if (this->LOSE()||this->WIN())
	{}
	else
	{
		if (this->ADD)
		{
			Sleep(50);
			this->AddBoard();
			this->ADD = false;
		}
	}
}

void Game::Right()
{
	for (size_t j = 0; j < size(this->BoardList); j++)
	{
		//1、先移动每行0元素
		for (size_t t = size(this->BoardList); t >0;t--)
		{
			for (size_t i = size(this->BoardList[t]) - 1; i>0; i--)
			{
				if (this->BoardList[j][i] == 0)
				{
					if (this->BoardList[j][i - 1]!=0)
					{
						this->ADD = true;
					}
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j][i - 1];
					this->BoardList[j][i - 1] = temp;
				}
			}
		}
		// 2、合并同类项
		for (size_t i = size(this->BoardList[j]) - 1; i >0; i--)
		{	
			if (this->BoardList[j][i] == this->BoardList[j][i - 1])
			{
				if (this->BoardList[j][i] != 0)
				{
					this->ADD = true;
				}
				this->BoardList[j][i] = this->BoardList[j][i] * 2;
				this->Scroe = this->BoardList[j][i] + this->Scroe;
				this->BoardList[j][i - 1] = 0;
			}
		}
		//3、 再次移动0元素
		for (size_t t = size(this->BoardList); t > 0; t--)
		{
			for (size_t i = size(this->BoardList[t]) - 1; i > 0; i--)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[j][i] == 0)
				{
					auto temp = this->BoardList[j][i];
					this->BoardList[j][i] = this->BoardList[j][i - 1];
					this->BoardList[j][i - 1] = temp;
				}
			}
		}
	}
	//赢了或者输了就不再添加
	if (this->LOSE() || this->WIN())
	{}
	else
	{
		if (this->ADD)
		{
			Sleep(50);
			this->AddBoard();
			this->ADD = false;
		}
	}	
}

void Game::Restart()
{
	this->Scroe = 0;//初始分数 
	this->ADD = false;//是否添加棋子
	this->Tips.assign("提示：");
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			this->BoardList[i][j] =0;
		}
	}
	Sleep(50);
	this->AddBoard();
	this->AddBoard();
}

void Game::RUN()
{
	system("color 70");//背景颜色 白底黑字
	HANDLE hOutput;
	COORD coord = { 0,0 };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	//创建新的缓冲区
	HANDLE hOutBuf = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		CONSOLE_TEXTMODE_BUFFER,
		NULL
	);

	//设置新的缓冲区为活动显示缓冲
	SetConsoleActiveScreenBuffer(hOutBuf);

	//隐藏两个缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize = 1;
	SetConsoleCursorInfo(hOutput, &cci);
	SetConsoleCursorInfo(hOutBuf, &cci);

	//双缓冲处理显示
	DWORD bytes = 0;
	char data[1600];
	system("color 70");
	SetConsoleTitleA("游戏：2048");
	this->Restart();
	while (1)
	{
		system("color 70");
		system("cls");
		if (this->LOSE())
		{
			break;
		}
		if (this->WIN())
		{
			break;
		}
		if (this->Input())
		{
			break;
		}
		if (this->LOSE())
		{
			string S;
			cout << this->Tips<<endl;
			cout << "输入yes并按回车继续，输入其他指令并按回车退出！";
			getline(cin,S);
			if (S =="yes")
			{
				this->Restart();
			}
			else
			{
					break;
			}
		}
		if (this->WIN())
		{
			string S;
			cout << this->Tips << endl;
			cout << "输入yes并按回车继续，输入其他指令并按回车退出！" << endl;
			cout << "输入指令：";
			getline(cin, S);
			if (S == "yes")
			{
				this->Restart();
			}
			else
			{
				break;
			}
		}
		this->Print();
		ReadConsoleOutputCharacterA(hOutput, data, 1600, coord, &bytes);//读取缓冲区
		WriteConsoleOutputCharacterA(hOutBuf, data, 1600, coord, &bytes);//显示缓冲区
	}
	cout << this->Tips;
	//system("pause");
}
void Game::Delay(int msec)
{
	clock_t now = clock();
	while (clock() - now < msec);
}

int main()
{
	Game a;
	a.RUN();
}

