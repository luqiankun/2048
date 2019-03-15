#pragma once
#ifndef _2048_h_
#define _2048_h_
#include <string>
#include <vector>
using namespace std;
class Game
{

public:
	int Scroe = 0;//初始分数 
	bool ADD = false;//是否添加棋子
	int BoardList[4][4] = { 0 };
	string Tips;

	Game();
	void Print(); //打印棋盘
	bool Input();//获取输入
	bool AddBoard();//添加棋子
	void Up();//上下左右按键事件，都类似，以左按键为母版
	void Down();
	void Right();
	void Left();
	void Restart();//复位
	void RUN();
	void Delay(int msec);
	bool WIN();//判断是否赢了
	bool LOSE();//判断是否输了
};

#endif