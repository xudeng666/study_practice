#include <iostream>
#include <graphics.h>
#include <string>
//  �Ҵ���С��Ϸ


#pragma comment(lib, "MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0,255,AC_SRC_ALPHA });
}

using namespace std;

#define FPS 60
#define _XCZ_W_ 1600
#define _XCZ_H_ 900
#define _HERO_W_ 57
#define _HERO_H_ 100
#define _H_ANI_NUM_ 6

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
/*
* ��ɫ�ƶ�
*/
void hero_Move();
/*��ȡ��ɫ�ƶ�״̬*/
bool get_heroIsMove();
/*��ȡ��ɫ����*/
bool get_heroFx();

// ����ͼ
IMAGE m_bg;
// ��ɫ����ͼ��
IMAGE* h_ani_arr[2][_H_ANI_NUM_+1];
/*��Ϣ*/
ExMessage msg;
// ��ѭ���Ƿ���
bool running = false;
// Ӣ������x
double m_x;
// Ӣ������y
double m_y;
// ֡��ʼʱ��
DWORD stime;
// ֡����ʱ��
DWORD etime;
// ֡����ʱ��
DWORD ani_time;
// �ٶȼ���ʱ��
DWORD speed_time;
// ��ɫ��������
bool h_fx[4];
// ��ɫ�ٶ�
double h_speed;
// ����֡����
int h_ani_id;
// ����2ֵ
const double SQRT2 = sqrt(2);



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
	ani_time = GetTickCount();
	speed_time = GetTickCount();

	// ����
	clearcliprgn();
}

void gameRun()
{
	BeginBatchDraw();
	while (running)
	{
		stime = GetTickCount();
		getOperation();
		gameDraw();
		dataProcessing();
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
	for (int i = 0; i <= _H_ANI_NUM_; ++i)
	{
		delete h_ani_arr[0][i];
		delete h_ani_arr[1][i];
		h_ani_arr[0][i] = nullptr;
		h_ani_arr[1][i] = nullptr;
	}
}

void login()
{
	loadimage(&m_bg, _T("resources/map_1.png"));

	for (int i = 0; i <= _H_ANI_NUM_; ++i)
	{
		h_ani_arr[0][i] = new IMAGE;
		std::wstring path = L"resources/kdss_1" + std::to_wstring(i) + L".png";
		loadimage(h_ani_arr[0][i], path.c_str());

		h_ani_arr[1][i] = new IMAGE;
		path = L"resources/kdss_2" + std::to_wstring(i) + L".png";
		loadimage(h_ani_arr[1][i], path.c_str());
	}
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
	DWORD t_time = GetTickCount();

	if ((t_time - ani_time) >= 1000 / h_speed)
	{
		ani_time = t_time;
		h_ani_id++;
	}
	h_ani_id = get_heroIsMove() ? (h_ani_id % _H_ANI_NUM_): _H_ANI_NUM_;
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

	int t = get_heroFx() ? 1 : 0;
	putimage_alpha(m_x - _HERO_W_ / 2, m_y - _HERO_H_ / 2, h_ani_arr[t][h_ani_id]);
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
	//cout << "�ٶȣ�" << c << endl;

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

bool get_heroFx()
{
	return h_fx[3];
}
