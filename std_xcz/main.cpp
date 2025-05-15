#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
//  幸存者小游戏

// 帧率
#define FPS 60
// 窗口宽度
#define _XCZ_W_ 1600
// 窗口高度
#define _XCZ_H_ 900

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
// 敌人增加
void enemyAdd();
/*
* 敌人减少
* @index 下标
*/
void enemyRed(int index);
// 清空敌人
void enemyClear();
// 敌人移动
void enemyMove();
//敌人绘制
void enemyDraw();
/*碰撞判断*/
void checkCollision();

// 背景图
IMAGE m_bg;
/*消息*/
ExMessage msg;
// 主循环是否开启
bool running = false;
// 帧开始时间
DWORD stime;
// 帧结束时间
DWORD etime;
// 角色指针
Player* player = nullptr;
// 敌人数组
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

// 敌人增加
void enemyAdd()
{
	if (GetTickCount() % 10 > 8)
	{
		Enemy* p = new Enemy(_XCZ_W_, _XCZ_H_);
		enemyArr.push_back(p);
	}
}

/*
* 敌人减少
* @index 下标
*/
void enemyRed(int index)
{
	if (index >= 0 && index < enemyArr.size())
	{
		// 解除内存占用
		delete enemyArr[index];
		enemyArr[index] = nullptr;
		// 将目标对象和末尾对象交换后在删除末尾（性能优化）
		std::swap(enemyArr[index], enemyArr[enemyArr.size()-1]);
		enemyArr.pop_back();
	}
}

// 清空敌人
void enemyClear()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		delete enemyArr[i];
		enemyArr[i] = nullptr;
	}
	enemyArr.clear();
}

// 敌人移动
void enemyMove()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		enemyArr[i]->Move(player);
	}
}


//敌人绘制
void enemyDraw()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		enemyArr[i]->Draw();
	}
}

/*碰撞判断*/
void checkCollision()
{
	for (int i = 0;i < enemyArr.size();)
	{
		switch (enemyArr[i]->checkCollision(player))
		{
		case PLAYER:
			cout << "游戏结束" << endl;
			return;
			break;
		case BULLET:
			cout << "敌人消失" << endl;
			enemyRed(i);
			break;
		case OTHER:
			++i;
			break;
		}
	}
}
