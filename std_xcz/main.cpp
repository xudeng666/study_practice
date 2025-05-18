#include <iostream>
#include <string>
#include "Player.h"
#include "Enemy.h"
#include "Button.h"
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
/*��ɫ����*/
void playerDie();
/*���ƿ�ʼ����*/
void gameStartDraw();
/*���ش�����Դ*/
void loadSecondResous();
/*����ui����*/
void textUIDraw();

// ����ͼ
IMAGE m_bg;
// ��Ϸ��ͼ
IMAGE m_map;
/*��ʼ��ť*/
StartGameBut* BtnSta;
/*������ť*/
OverGameBut* BtnEnd;
/*��Ϣ*/
ExMessage msg;
/*ͼ������*/
vector<Atlas*> atlList;
// ֡��ʼʱ��
DWORD stime;
// ֡����ʱ��
DWORD etime;
// ��ɫָ��
Player* player = nullptr;
// ��������
vector<Enemy*> enemyArr;
// ������Դ�Ƿ��Ѽ���
bool loadSec = false;
// ��һ���
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
	// ���ɴ���
	initgraph(_XCZ_W_, _XCZ_H_, EX_SHOWCONSOLE);
	login();
	// ���ű�������
	// mciSendString(_T("play bgm repeat from 0"), nullptr, 0, nullptr);// repeat��ʾѭ������ from 0ָ��ͷ��ʼ����
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
		if (gamestart)// ��Ϸ����
		{
			getOperation();
			dataProcessing();
			gameDraw();
		}
		else// ��ʼ����
		{
			// ���Ʊ���ͼ�Ͱ�ť
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
	// ���ر�����Դ
	loadimage(&m_map, _T("resources/map/map_1.png"));
	loadimage(&m_bg, _T("resources/bg/bg_1.png"));
	// ���ؽ�ɫ/������Դ
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
	// ���ر�������
	mciSendString(_T("open music/bg_music_1.mp3 alias bgm"), nullptr, 0, nullptr);
	// ����������Ч
	mciSendString(_T("open music/yx_1.mp3 alias hit"), nullptr, 0, nullptr);

	/*
	* open ·�� alias xx	����������Դ��ȡ����Ϊxx,����������ֱ���øñ������ɡ�������������������һ�»ᱨ��
	*		��ע�⡿����ļ�·�������ո�����˫���Ű������� "C:\\my music.mp3"����
	* close xx				�ر�xx���ֲ��ͷ���Դ��close��������Ҫ���ű�������openһ��
	* play xx				����xx����
	* stop xx				ֹͣ����xx���֣�ֹͣ�����play���²���
	* pause	xx				��ͣ����xx����
	* resume xx				����ͣ����������xx����
	* seek xx to start		xx������ת����ͷ
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


/*��ɫ����*/
void playerDie()
{
	gamestart = false;

	// �رձ�������
	mciSendString(_T("stop bgm"), nullptr, 0, nullptr);

	gameInit();

}

/*���ƿ�ʼ����*/
void gameStartDraw()
{
	// ���ɰ�ť
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


	// ���Ʊ���
	double w = m_bg.getwidth();
	double h = m_bg.getheight();
	putimage((_XCZ_W_ - w) / 2, (_XCZ_H_ - h) / 2, &m_bg);
	// ���ư�ť
	BtnSta->Draw();
	BtnEnd->Draw();

	while (peekmessage(&msg, EX_MOUSE))
	{
		BtnSta->ProcessEvent(msg);
		BtnEnd->ProcessEvent(msg);
	}
}

/*���ش�����Դ*/
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

/*����ui����*/
void textUIDraw()
{
	settextcolor(YELLOW);
	LPCTSTR path = _T("��ҵ�ǰ����ֵ��%d      ��ǰ���֣�%d");
	TCHAR path_file[256];
	_stprintf_s(path_file, path, player->get_HP(), playerIntegral);
	outtextxy(10, 10, path_file);

}
