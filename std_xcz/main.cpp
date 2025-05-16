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
/*
* 敌人减少
* @enemy	对象指针别名
*/
void enemyRed(Enemy*& enemy);
// 清空敌人
void enemyClear();
// 敌人移动
void enemyMove();
//敌人绘制
void enemyDraw();
/*
* 敌人被击中
* @index 下标
*/
void enemyByHit(int index);
/*碰撞判断*/
void checkCollision();
/*资源清空*/
void atlListClear();

// 背景图
IMAGE m_bg;
/*消息*/
ExMessage msg;
/*图集数组*/
vector<Atlas*> atlList;
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
	// 生成窗口
	initgraph(_XCZ_W_, _XCZ_H_, EX_SHOWCONSOLE);
	login();
	// 播放背景音乐
	mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat表示循环播放 from 0指从头开始播放
}

void gameInit()
{
	running = true;
	player = new Player(atlList[FRAME_TYPE_PLAYER]);
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
	// 加载背景资源
	loadimage(&m_bg, _T("resources/map/map_1.png"));
	// 加载角色/敌人资源
	for (int i = 0; i < FRAME_TYPE_COUNT;++i)
	{
		Atlas* atl = nullptr;
		switch (i)
		{
		case FRAME_TYPE_PLAYER:
			atl = new Atlas(_T("resources/hero/kdss_%d.png"), 14);
			atlList.push_back(atl);
			break;
		case FRAME_TYPE_ENEMY_1:
			atl = new Atlas(_T("resources/enemy/gw_%d_%d.png"), i, 12);
			atlList.push_back(atl);
			break;
		case FRAME_TYPE_ENEMY_2:
		case FRAME_TYPE_ENEMY_3:
		case FRAME_TYPE_ENEMY_4:
			atl = new Atlas(_T("resources/enemy/gw_%d_%d.png"), i, 8);
			atlList.push_back(atl);
		}
	}
	// 加载背景音乐
	mciSendString(_T("open music/bg_music_1.mp3 alias bgm"), nullptr, 0, nullptr);
	// 加载命中音效
	mciSendString(_T("open music/yx_1.mp3 alias hit"), nullptr, 0, nullptr);
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
		Enemy* p = new Enemy(atlList, _XCZ_W_, _XCZ_H_);
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

/*
* 敌人减少
* @enemy	对象指针别名
*/
void enemyRed(Enemy*& enemy)
{
	// 解除内存占用
	delete enemy;
	enemy = nullptr;
	// 将目标对象和末尾对象交换后在删除末尾（性能优化）
	std::swap(enemy, enemyArr[enemyArr.size()-1]);
	enemyArr.pop_back();
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
	for (Enemy* &enemy : enemyArr)
	{
		enemy->Move(player);
	}
}


//敌人绘制
void enemyDraw()
{
	for (Enemy* &enemy : enemyArr)
	{
		enemy->Draw();
	}
}

/*碰撞判断*/
void checkCollision()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		switch (enemyArr[i]->checkCollision(player))
		{
		case PLAYER:
			cout << "游戏结束" << endl;
			return;
			break;
		case BULLET:
			cout << "敌人消失" << endl;
			mciSendString(_T("play hit from 0"), nullptr, 0, nullptr);
			enemyRed(enemyArr[i]);
			break;
		}
	}

	/*
	* if (checkWin())
	{
		wstring path = board_data[m_x][m_y] == 'X' ? L"X 玩家获胜, 本轮游戏结束！\n是否重开游戏？":L"O 玩家获胜, 本轮游戏结束！\n是否重开游戏？";
		result = MessageBox(GetHWnd(), path.c_str(), _T("提示"), MB_YESNO);
		running = false;
	}
	else if (checkDraw())
	{
		result = MessageBox(GetHWnd(), _T("平局, 本轮游戏结束！\n是否重开游戏？"), _T("提示"), MB_YESNO);
		running = false;
	}
	*/
}


/*
* 敌人被击中
* @index 下标
*/
void enemyByHit(int index)
{

}


/*资源清空*/
void atlListClear()
{
	for (int i = 0; i < atlList.size();++i)
	{
		delete atlList[i];
		atlList[i] = nullptr;
	}
	atlList.clear();
}
