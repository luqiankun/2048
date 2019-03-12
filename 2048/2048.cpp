// 2048.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;
class Game
{
	
public:
	int Scroe = 0;//初始分数 
	bool ADD = false;//是否添加棋子
	int BoardList[4][4] = { 0 };
	string Tips = { "nothing" };

	void Print(); //打印棋盘
	bool Input();//获取输入
	bool AddBoard();//添加棋子
	void Up();
	void Down();
	void Right();
	void Left();
	void Restart();
	void Delay(int msec);
	bool WIN();//判断是否赢了
	bool LOSE();//判断是否输了
};

void Game::Print()
{
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		cout << "I-----I-----I-----I-----I" << endl;
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			if (this->BoardList[i][j] != 0)
			{
				cout <<" "<<setw(4)<< setiosflags(ios::left) <<this->BoardList[i][j]<<" ";
				
			}
			else
			{
				cout<< " "<<setw(4) << setiosflags(ios::left) << " "<<" ";
			}
		}
		cout << endl;
	}
	cout << "I-----I-----I-----I-----I" << endl;
	cout << "Your Scroe is:" << this->Scroe << endl;
	for (size_t i = 0; i < this->Tips.size(); i++)
	{
		cout << this->Tips[i] ;
	}
	cout <<  endl;
}
bool Game::Input()
{
	int ch;
	if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
		ch = _getch();//使用_getch()函数获取按下的键值
		switch (ch)
		{
		case 27:return true;break;
		case 113:return true; break;
		case 114: this->Restart(); break;//复位
		case 80:this->Down(); break;//xia
		case 75: this->Left(); break;//zuo
		case 72: this->Up(); break;//shang
		case 77: this->Right(); break;//右
		default:
			return false;
			break;
		}
	
	}
	
	return false;
}
bool Game::LOSE()
{
	bool lose=true;
	//没有0出现
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			
			if (this->BoardList[i][j] == 0)
			{
				lose = false;
				return false;
				break;
				
			}
		}
	}
	//其次横竖相邻元素不相等
	for (size_t i = 0; i < size(this->BoardList) - 1; i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]) - 1; j++)
		{
			if (this->BoardList[i][j]== this->BoardList[i][j+1])
			{
				return false;
				break;
			}
			if (this->BoardList[j][i]== this->BoardList[j+1][i])
			{
				lose = false;
				return false;
				break;
			}
		}
	}
	if (lose)
	{
		return true;
	}
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
				return true;
				break;
				
			}
			else
			{
				return false;
			}
		}
	}
}
bool Game::AddBoard()
{
	int choice[] = { 4, 2, 2, 4, 2, 2, 2, 2 };//可以调节2和4出现的频率
	//srand(time(0));

	int temp = (rand() % (size(choice) - 0)) + 0;
	int p1 = rand() % 4;
	int p2 = rand() % 4;
	while (this->BoardList[p1][p2] != 0)
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
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{

		}
	}
	this->AddBoard();
}
void Game::Down()
{
		
	this->AddBoard();
}
void Game::Left()
{
	for (size_t j= 0; j < size(this->BoardList); j++)
	{
		//1、先移动每行0元素
		for (size_t t = 0; t < size(this->BoardList); t++)
		{
			
			for (size_t i = 0; i < size(this->BoardList[t]) - 1; i++)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[t][i] == 0)
				{
					auto temp = this->BoardList[t][i];
					this->BoardList[t][i] = this->BoardList[t][i + 1];
					this->BoardList[t][i + 1] = temp;

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
				this->BoardList[j][i] = this->BoardList[j][i] * 2;
				this->Scroe = this->BoardList[j][i] + this->Scroe;
				this->BoardList[j][i + 1] = 0;
			}

		}
		//3、 再次移动0元素
		for (size_t t = 0; t < size(this->BoardList); t++)
		{

			for (size_t i = 0; i < size(this->BoardList[t]) - 1; i++)
			{
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[t][i] == 0)
				{
					auto temp = this->BoardList[t][i];
					this->BoardList[t][i] = this->BoardList[t][i + 1];
					this->BoardList[t][i + 1] = temp;

				}
			}
		}
	}
	//赢了或者输了就不再添加
	if (this->LOSE()||this->WIN())
	{

	}
	else
	{
		this->AddBoard();
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
				// 0 2 0 2 -> 2 2 0 0
				if (this->BoardList[t][i] == 0)
				{
					auto temp = this->BoardList[t][i];
					this->BoardList[t][i] = this->BoardList[t][i - 1];
					this->BoardList[t][i - 1] = temp;

				}
			}
		}
		// 2、合并同类项
		for (size_t i = size(this->BoardList[j]) - 1; i >0; i--)
		{
			// 2 2 2 2 -> 0 4 0 4 
			// 0 2 2 2  -> 0 2 0 4
			if (this->BoardList[j][i] == this->BoardList[j][i - 1])
			{
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
				if (this->BoardList[t][i] == 0)
				{
					auto temp = this->BoardList[t][i];
					this->BoardList[t][i] = this->BoardList[t][i - 1];
					this->BoardList[t][i - 1] = temp;

				}
			}
		}
	}
	//赢了或者输了就不再添加
	if (this->LOSE() || this->WIN())
	{

	}
	else
	{
		this->AddBoard();
	}
	
}
void Game::Restart()
{
	this->Scroe = 0;//初始分数 
	this->ADD = false;//是否添加棋子
	for (size_t i = 0; i < size(this->BoardList); i++)
	{
		for (size_t j = 0; j < size(this->BoardList[0]); j++)
		{
			this->BoardList[i][j] =0;
		}
	}
	this->AddBoard();
	this->AddBoard();
}



void Game::Delay(int msec)
{
	clock_t now = clock();
	while (clock() - now < msec);
}

int main()
{
	Game a;
	a.Restart();
	while (1)
	{
		system("cls");
		if (a.LOSE())
		{
			a.Tips = { "YOU LOSE!!!" };
			break;
		}
		if (a.WIN())
		{
			a.Tips = { "YOU WIN!!!" };
			break;
		}
		if (a.Input())
		{
			break;
		}

		if (a.LOSE())
		{
			break;
		}
		if (a.WIN())
		{
			break;
		}
		a.Print();
		Sleep(260);
	}
	
	cout << a.Tips;
	
	//system("pause");

	
}

