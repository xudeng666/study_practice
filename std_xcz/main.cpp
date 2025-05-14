#include <iostream>
#include <graphics.h>
#include <string>
#include "Player.h"
//  �Ҵ���С��Ϸ

using namespace std;
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
Player* player = nullptr;



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
	player = new Player(57, 100, 6, 5);
	// ����
	//clearcliprgn();
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
		if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
		{
			bool m = msg.message == WM_KEYDOWN;
			switch (msg.vkcode)
			{
			case 'W':
			case 'w':
			case VK_UP:
				player->setFx(0, m);
				break;
			case 'S':
			case 's':
			case VK_DOWN:
				player->setFx(1, m);
				break;
			case 'A':
			case 'a':
			case VK_LEFT:
				player->setFx(2, m);
				break;
			case 'D':
			case 'd':
			case VK_RIGHT:
				player->setFx(3, m);
				break;
			}
		}
	}
}

void dataProcessing()
{
	player->upData();
	player->Move(_XCZ_W_, _XCZ_W_);
}

void gameDraw()
{
	double w = m_bg.getwidth();
	double h = m_bg.getheight();
	putimage((_XCZ_W_ - w)/2, (_XCZ_H_-h)/2, &m_bg);
	player->Draw();
}