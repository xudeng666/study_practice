#include <iostream>
#include <graphics.h>
#include <string>
#include "Animation.h"
//  幸存者小游戏

using namespace std;
// 帧率
#define FPS 60
// 窗口宽度
#define _XCZ_W_ 1600
// 窗口高度
#define _XCZ_H_ 900
// 玩家宽度
#define _HERO_W_ 57
// 玩家高度
#define _HERO_H_ 100
#define _H_ANI_NUM_ 6

//打开游戏窗口
void openWindow();
//游戏初始化
void gameInit();
//游戏运行
void gameRun();
//游戏结束-释放资源
void gameOver();
//加载游戏资源
void login();
//初始化数据
void intData();
/*读取操作*/
void getOperation();
/*数据处理*/
void dataProcessing();
/*绘制画面*/
void gameDraw();
/*
* 角色移动
*/
void hero_Move();
/*获取角色移动状态*/
bool get_heroIsMove();

// 背景图
IMAGE m_bg;
/*消息*/
ExMessage msg;
// 主循环是否开启
bool running = false;
// 英雄坐标x
double m_x;
// 英雄坐标y
double m_y;
// 帧开始时间
DWORD stime;
// 帧结束时间
DWORD etime;
// 速度计算时间
DWORD speed_time;
// 角色方向数据
bool h_fx[4];
// 角色速度
double h_speed;
// 根号2值
const double SQRT2 = sqrt(2);
// 角色动画
Animation* playerAni = nullptr;



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
	m_x = _XCZ_W_ / 2;
	m_y = _XCZ_H_ / 2;
	h_speed = 10;
	for (int i = 0; i < 4; ++i)
	{
		h_fx[i] = false;
	}
	speed_time = GetTickCount();

	playerAni = new Animation(_T("resources/hero/kdss_%d.png"), _H_ANI_NUM_ * 2 + 2, h_speed);

	// 清屏
	//clearcliprgn();
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
	delete playerAni;
	playerAni = nullptr;
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
				h_fx[0] = m;
				break;
			case 'S':
			case 's':
			case VK_DOWN:
				h_fx[1] = m;
				break;
			case 'A':
			case 'a':
			case VK_LEFT:
				h_fx[2] = m;
				break;
			case 'D':
			case 'd':
			case VK_RIGHT:
				h_fx[3] = m;
				break;
			}

		}
	}
	playerAni->DrawPlayer(get_heroIsMove());
}

void dataProcessing()
{
	hero_Move();
}

void gameDraw()
{
	double w = m_bg.getwidth();
	double h = m_bg.getheight();
	putimage((_XCZ_W_ - w)/2, (_XCZ_H_-h)/2, &m_bg);
	playerAni->play(m_x - _HERO_W_ / 2, m_y - _HERO_H_ / 2);
}

void hero_Move()
{
	DWORD t_time = GetTickCount();

	double c = _HERO_W_ * 2 / _H_ANI_NUM_ * h_speed * (t_time - speed_time);

	if ((h_fx[0] || h_fx[1]) && (h_fx[2] || h_fx[3]))
	{
		c /= SQRT2;
	}

	c /= 1000;
	//cout << "速度：" << c << endl;
	double _x = m_x;

	if (h_fx[0])
	{
		m_y -= c;
	}
	if (h_fx[1])
	{
		m_y += c;
	}
	if (h_fx[2])
	{
		m_x -= c;
	}
	if (h_fx[3])
	{
		m_x += c;
	}

	if (_x > m_x)
	{
		playerAni->setFx(false);
	}
	else if (_x < m_x)
	{
		playerAni->setFx(true);
	}

	if (m_x < _HERO_W_ / 2)
	{
		m_x = _HERO_W_ / 2;
	}
	else if(m_x > _XCZ_W_ - _HERO_W_ / 2)
	{
		m_x = _XCZ_W_ - _HERO_W_ / 2;
	}
	if (m_y < _HERO_H_ / 2)
	{
		m_y = _HERO_H_ / 2;
	}
	else if(m_y > _XCZ_H_ - _HERO_H_ / 2)
	{
		m_y = _XCZ_H_ - _HERO_H_ / 2;
	}

	speed_time = t_time;
}

bool get_heroIsMove()
{
	return h_fx[0] || h_fx[1] || h_fx[2] || h_fx[3];
}
