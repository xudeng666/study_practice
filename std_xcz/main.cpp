#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
//  �Ҵ���С��Ϸ

// ֡��
#define FPS 60
// ���ڿ��
#define _XCZ_W_ 1600
// ���ڸ߶�
#define _XCZ_H_ 900

//����Ϸ����
void openWindow();
//��Ϸ��ʼ��
void gameInit();
//��Ϸ����
void gameRun();
//��Ϸ����-�ͷ���Դ
void gameOver();
//������Ϸ��Դ
void login();
//��ʼ������
void intData();
/*��ȡ����*/
void getOperation();
/*���ݴ���*/
void dataProcessing();
/*���ƻ���*/
void gameDraw();
// ��������
void enemyAdd();
/*
* ���˼���
* @index �±�
*/
void enemyRed(int index);
// ��յ���
void enemyClear();
// �����ƶ�
void enemyMove();
//���˻���
void enemyDraw();
/*��ײ�ж�*/
void checkCollision();

// ����ͼ
IMAGE m_bg;
/*��Ϣ*/
ExMessage msg;
// ��ѭ���Ƿ���
bool running = false;
// ֡��ʼʱ��
DWORD stime;
// ֡����ʱ��
DWORD etime;
// ��ɫָ��
Player* player = nullptr;
// ��������
vector<Enemy*> enemyArr;



int main()
{
	openWindow();
	gameInit();
	gameRun();
	gameOver();
}

void openWindow()
{
	initgraph(_XCZ_W_, _XCZ_H_, EX_SHOWCONSOLE);
	login();
}

void gameInit()
{
	running = true;
	player = new Player(6, 5);
	player->Init(_XCZ_W_, _XCZ_H_);
}

void gameRun()
{
	BeginBatchDraw();
	while (running)
	{
		stime = GetTickCount();
		getOperation();
		dataProcessing();
		gameDraw();
		FlushBatchDraw();
		etime = GetTickCount();
		DWORD dtime = etime - stime;
		if (dtime < 1000 / FPS)
		{
			Sleep(1000 / FPS - dtime);
		}
	}
	EndBatchDraw();
}

void gameOver()
{
	delete player;
	player = nullptr;
	enemyClear();
}

void login()
{
	loadimage(&m_bg, _T("resources/map/map_1.png"));
}

void intData()
{
}

void getOperation()
{
	while (peekmessage(&msg, EX_KEY | EX_MOUSE))
	{
		player->processEvent(msg);
	}
	checkCollision();
	enemyAdd();
}

void dataProcessing()
{
	player->upData();
	player->Move();
	player->flyBullet();
	enemyMove();
}

void gameDraw()
{
	double w = m_bg.getwidth();
	double h = m_bg.getheight();
	putimage((_XCZ_W_ - w)/2, (_XCZ_H_-h)/2, &m_bg);
	player->Draw();
	player->drawBullet();
	enemyDraw();
}

// ��������
void enemyAdd()
{
	if (GetTickCount() % 10 > 8)
	{
		Enemy* p = new Enemy(_XCZ_W_, _XCZ_H_);
		enemyArr.push_back(p);
	}
}

/*
* ���˼���
* @index �±�
*/
void enemyRed(int index)
{
	if (index >= 0 && index < enemyArr.size())
	{
		// ����ڴ�ռ��
		delete enemyArr[index];
		enemyArr[index] = nullptr;
		// ��Ŀ������ĩβ���󽻻�����ɾ��ĩβ�������Ż���
		std::swap(enemyArr[index], enemyArr[enemyArr.size()-1]);
		enemyArr.pop_back();
	}
}

// ��յ���
void enemyClear()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		delete enemyArr[i];
		enemyArr[i] = nullptr;
	}
	enemyArr.clear();
}

// �����ƶ�
void enemyMove()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		enemyArr[i]->Move(player);
	}
}


//���˻���
void enemyDraw()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		enemyArr[i]->Draw();
	}
}

/*��ײ�ж�*/
void checkCollision()
{
	for (int i = 0;i < enemyArr.size();)
	{
		switch (enemyArr[i]->checkCollision(player))
		{
		case PLAYER:
			cout << "��Ϸ����" << endl;
			return;
			break;
		case BULLET:
			cout << "������ʧ" << endl;
			enemyRed(i);
			break;
		case OTHER:
			++i;
			break;
		}
	}
}
