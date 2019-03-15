#pragma once
#ifndef _2048_h_
#define _2048_h_
#include <string>
#include <vector>
using namespace std;
class Game
{

public:
	int Scroe = 0;//��ʼ���� 
	bool ADD = false;//�Ƿ��������
	int BoardList[4][4] = { 0 };
	string Tips;

	Game();
	void Print(); //��ӡ����
	bool Input();//��ȡ����
	bool AddBoard();//�������
	void Up();//�������Ұ����¼��������ƣ����󰴼�Ϊĸ��
	void Down();
	void Right();
	void Left();
	void Restart();//��λ
	void RUN();
	void Delay(int msec);
	bool WIN();//�ж��Ƿ�Ӯ��
	bool LOSE();//�ж��Ƿ�����
};

#endif