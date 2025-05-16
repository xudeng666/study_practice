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
/*
* ���˼���
* @enemy	����ָ�����
*/
void enemyRed(Enemy*& enemy);
// ��յ���
void enemyClear();
// �����ƶ�
void enemyMove();
//���˻���
void enemyDraw();
/*
* ���˱�����
* @index �±�
*/
void enemyByHit(int index);
/*��ײ�ж�*/
void checkCollision();
/*��Դ���*/
void atlListClear();

// ����ͼ
IMAGE m_bg;
/*��Ϣ*/
ExMessage msg;
/*ͼ������*/
vector<Atlas*> atlList;
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
	// ���ɴ���
	initgraph(_XCZ_W_, _XCZ_H_, EX_SHOWCONSOLE);
	login();
	// ���ű�������
	mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat��ʾѭ������ from 0ָ��ͷ��ʼ����
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
	// ���ر�����Դ
	loadimage(&m_bg, _T("resources/map/map_1.png"));
	// ���ؽ�ɫ/������Դ
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
	// ���ر�������
	mciSendString(_T("open music/bg_music_1.mp3 alias bgm"), nullptr, 0, nullptr);
	// ����������Ч
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

// ��������
void enemyAdd()
{
	if (GetTickCount() % 10 > 8)
	{
		Enemy* p = new Enemy(atlList, _XCZ_W_, _XCZ_H_);
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

/*
* ���˼���
* @enemy	����ָ�����
*/
void enemyRed(Enemy*& enemy)
{
	// ����ڴ�ռ��
	delete enemy;
	enemy = nullptr;
	// ��Ŀ������ĩβ���󽻻�����ɾ��ĩβ�������Ż���
	std::swap(enemy, enemyArr[enemyArr.size()-1]);
	enemyArr.pop_back();
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
	for (Enemy* &enemy : enemyArr)
	{
		enemy->Move(player);
	}
}


//���˻���
void enemyDraw()
{
	for (Enemy* &enemy : enemyArr)
	{
		enemy->Draw();
	}
}

/*��ײ�ж�*/
void checkCollision()
{
	for (int i = 0;i < enemyArr.size();++i)
	{
		switch (enemyArr[i]->checkCollision(player))
		{
		case PLAYER:
			cout << "��Ϸ����" << endl;
			return;
			break;
		case BULLET:
			cout << "������ʧ" << endl;
			mciSendString(_T("play hit from 0"), nullptr, 0, nullptr);
			enemyRed(enemyArr[i]);
			break;
		}
	}

	/*
	* if (checkWin())
	{
		wstring path = board_data[m_x][m_y] == 'X' ? L"X ��һ�ʤ, ������Ϸ������\n�Ƿ��ؿ���Ϸ��":L"O ��һ�ʤ, ������Ϸ������\n�Ƿ��ؿ���Ϸ��";
		result = MessageBox(GetHWnd(), path.c_str(), _T("��ʾ"), MB_YESNO);
		running = false;
	}
	else if (checkDraw())
	{
		result = MessageBox(GetHWnd(), _T("ƽ��, ������Ϸ������\n�Ƿ��ؿ���Ϸ��"), _T("��ʾ"), MB_YESNO);
		running = false;
	}
	*/
}


/*
* ���˱�����
* @index �±�
*/
void enemyByHit(int index)
{

}


/*��Դ���*/
void atlListClear()
{
	for (int i = 0; i < atlList.size();++i)
	{
		delete atlList[i];
		atlList[i] = nullptr;
	}
	atlList.clear();
}
