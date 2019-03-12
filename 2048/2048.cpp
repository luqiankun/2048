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


	Game(); //构造函数，初始化
	~Game();

	void Delay(int msec);

private:

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
bool Game::AddBoard()
{
	int choice[] = { 4, 2, 2, 4, 2, 2, 2, 2 };
	//srand(time(0));

	int temp = (rand() % (size(choice) - 0)) + 0;
	int p1 = rand() % 4;
	int p2 = rand() % 4;
	if (this->BoardList[p1][p2]==0)
	{
		this->BoardList[p1][p2] = choice[temp];
	}
	else
	{
		 Game::AddBoard();
	}
	this->ADD = false;
	return true;
}
void Game::Up()
{
	this->AddBoard();
}
void Game::Down()
{
	this->AddBoard();
}
void Game::Left()
{
	this->AddBoard();
}

void Game::Right()
{
	this->AddBoard();
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

Game::Game()
{
}

Game::~Game()
{
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
		if (a.Input())
		{
			break;
		}
		a.Print();
		Sleep(260);
	}
	cout << "jieshu" << endl;
	//system("pause");
}

