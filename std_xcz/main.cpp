#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
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
/*角色死亡*/
void playerDie();
/*绘制开始界面*/
void gameStartDraw();
/*加载次生资源*/
void loadSecondResous();
/*绘制ui文字*/
void textUIDraw();

// 背景图
IMAGE m_bg;
// 游戏地图
IMAGE m_map;
/*开始按钮*/
StartGameBut* BtnSta;
/*结束按钮*/
OverGameBut* BtnEnd;
/*消息*/
ExMessage msg;
/*图集数组*/
vector<Atlas*> atlList;
// 帧开始时间
DWORD stime;
// 帧结束时间
DWORD etime;
// 角色指针
Player* player = nullptr;
// 敌人数组
vector<Enemy*> enemyArr;
// 次生资源是否已加载
bool loadSec = false;
// 玩家积分
int playerIntegral = 0;

bool gamestart = false;
bool running = false;


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
	// mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat表示循环播放 from 0指从头开始播放
}

void gameInit()
{
	gamestart = false;
	running = true;
	player = Player::_getPlayer();
	player->Init(_XCZ_W_, _XCZ_H_, atlList[FRAME_TYPE_PLAYER]);
	playerIntegral = 0;
	enemyClear();
}

void gameRun()
{
	BeginBatchDraw();
	while (running)
	{
		stime = GetTickCount();
		loadSecondResous();
		if (gamestart)// 游戏界面
		{
			getOperation();
			dataProcessing();
			gameDraw();
		}
		else// 开始界面
		{
			// 绘制背景图和按钮
			gameStartDraw();
		}

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
	atlListClear();
}

void login()
{
	// 加载背景资源
	loadimage(&m_map, _T("resources/map/map_1.png"));
	loadimage(&m_bg, _T("resources/bg/bg_1.png"));
	// 加载角色/敌人资源
	for (int i = 0; i < FRAME_TYPE_COUNT;++i)
	{
		Atlas* atl = nullptr;
		switch (i)
		{
		case FRAME_TYPE_PLAYER:
			atl = new Atlas(_T("resources/hero/kdss_%d.png"), 7);
			atlList.push_back(atl);
			break;
		case FRAME_TYPE_ENEMY_1:
			atl = new Atlas(_T("resources/enemy/gw_%d_%d.png"), i, 6);
			atlList.push_back(atl);
			break;
		case FRAME_TYPE_ENEMY_2:
		case FRAME_TYPE_ENEMY_3:
		case FRAME_TYPE_ENEMY_4:
			atl = new Atlas(_T("resources/enemy/gw_%d_%d.png"), i, 4);
			atlList.push_back(atl);
		}
	}
	// 加载背景音乐
	mciSendString(_T("open music/bg_music_1.mp3 alias bgm"), nullptr, 0, nullptr);
	// 加载命中音效
	mciSendString(_T("open music/yx_1.mp3 alias hit"), nullptr, 0, nullptr);

	/*
	* open 路径 alias xx	加载音乐资源并取别名为xx,后续操作都直接用该别名即可。如果后续操作与别名不一致会报错
	*		【注意】如果文件路径包含空格，需用双引号包裹（如 "C:\\my music.mp3"）。
	* close xx				关闭xx音乐并释放资源，close过的音乐要播放必须重新open一下
	* play xx				播放xx音乐
	* stop xx				停止播放xx音乐，停止后可用play重新播放
	* pause	xx				暂停播放xx音乐
	* resume xx				从暂停处继续播放xx音乐
	* seek xx to start		xx音乐跳转到开头
	*/
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
	double w = m_map.getwidth();
	double h = m_map.getheight();
	putimage((_XCZ_W_ - w)/2, (_XCZ_H_-h)/2, &m_map);
	player->Draw();
	player->drawBullet();
	enemyDraw();
	textUIDraw();
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
			enemyRed(enemyArr[i]);
			player->playerInjured();
			if (player->get_HP() <= 0)
			{
				return playerDie();
			}
			break;
		case BULLET:
			mciSendString(_T("play hit from 0"), nullptr, 0, nullptr);
			enemyRed(enemyArr[i]);
			playerIntegral++;
			break;
		}
	}
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


/*角色死亡*/
void playerDie()
{
	gamestart = false;

	// 关闭背景音乐
	mciSendString(_T("stop bgm"), nullptr, 0, nullptr);

	gameInit();

}

/*绘制开始界面*/
void gameStartDraw()
{
	// 生成按钮
	if (nullptr == BtnSta)
	{
		BtnSta = new StartGameBut({ 600,600,870,678 },
			_T("resources/btn/btn_ksyx_2.png"),
			_T("resources/btn/btn_ksyx_1.png"),
			_T("resources/btn/btn_ksyx_3.png"));
	}
	if (nullptr == BtnEnd)
	{
		BtnEnd = new OverGameBut({ 830,600,1000,678 },
			_T("resources/btn/btn_tcyx_2.png"),
			_T("resources/btn/btn_tcyx_1.png"),
			_T("resources/btn/btn_tcyx_3.png"));
	}


	// 绘制背景
	double w = m_bg.getwidth();
	double h = m_bg.getheight();
	putimage((_XCZ_W_ - w) / 2, (_XCZ_H_ - h) / 2, &m_bg);
	// 绘制按钮
	BtnSta->Draw();
	BtnEnd->Draw();

	while (peekmessage(&msg, EX_MOUSE))
	{
		BtnSta->ProcessEvent(msg);
		BtnEnd->ProcessEvent(msg);
	}
}

/*加载次生资源*/
void loadSecondResous()
{
	if (loadSec)
		return;
	if (!loadSec && etime > 0 && etime < stime)
	{
		loadSec = true;
		for (int i = 0; i < atlList.size(); ++i)
		{
			atlList[i]->greatRightDirect();
			atlList[i]->greatWhitePix();
		}
	}
}

/*绘制ui文字*/
void textUIDraw()
{
	settextcolor(YELLOW);
	LPCTSTR path = _T("玩家当前生命值：%d      当前积分：%d");
	TCHAR path_file[256];
	_stprintf_s(path_file, path, player->get_HP(), playerIntegral);
	outtextxy(10, 10, path_file);

}
