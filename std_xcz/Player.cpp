#include "Player.h"


/*
* ���캯��
@w ��ɫ���
@h ��ɫ�߶�
@num ����֡��
@spd ��ɫ��ʼ�ٶ�
*/
Player::Player(int w, int h, int num, double spd) :_W_(w), _H_(h), aniNum(num)
{
	speed = spd;
	speed_time = 0;
	m_x = 0;
	m_y = 0;
}
/*����*/
Player::~Player()
{
	delete playerAni;
	playerAni = nullptr;
}

/*
���ݳ�ʼ��
@w ���ڿ��
@h ���ڸ߶�
*/
void Player::Init(int w, int h)
{
	m_x = w / 2;
	m_y = h / 2;
	for (int i = 0; i < 4; ++i)
	{
		h_fx[i] = false;
	}
	speed_time = GetTickCount();
	playerAni = new Animation(_T("resources/hero/kdss_%d.png"), aniNum * 2 + 2, speed);
}

/*
��ɫ�ƶ�
@w ���ڿ��
@h ���ڸ߶�
*/
void Player::Move(int w, int h)
{
	DWORD t_time = GetTickCount();

	double c = _W_ * 2 / aniNum * speed * (t_time - speed_time);

	if ((h_fx[0] || h_fx[1]) && (h_fx[2] || h_fx[3]))
	{
		c /= SQRT2;
	}
	c /= 1000;
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

	if (m_x < _W_ / 2)
	{
		m_x = _W_ / 2;
	}
	else if (m_x > w - _W_ / 2)
	{
		m_x = w - _W_ / 2;
	}
	if (m_y < _H_ / 2)
	{
		m_y = _H_ / 2;
	}
	else if (m_y > h - _H_ / 2)
	{
		m_y = h - _H_ / 2;
	}
	speed_time = t_time;
}

/*�Ƿ��ƶ���*/
bool Player::isMove()
{
	return h_fx[0] || h_fx[1] || h_fx[2] || h_fx[3];
}

/*���ƽ�ɫ*/
void Player::Draw()
{
	playerAni->play(m_x - _W_ / 2, m_y - _H_ / 2);
}

/*
���÷�������
@n	�±� 0123 ��������
@m	�Ƿ��ƶ�
*/
void Player::setFx(int index, bool m)
{
	if (h_fx[index] != m)
	{
		h_fx[index] = m;
	}
}

/*ˢ������*/
void Player::upData()
{
	playerAni->DrawPlayer(isMove());
}