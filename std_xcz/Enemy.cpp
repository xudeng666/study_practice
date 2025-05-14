#include "Enemy.h"


/*
* ���캯��
@num ����֡��
@spd ��ɫ��ʼ�ٶ�
*/
Enemy::Enemy(int num, double spd) :aniNum(num)
{
	speed = spd;
	speed_time = 0;
	m_x = 0;
	m_y = 0;
	InitRandom();
	playerAni = new Animation(_T("resources/hero/kdss_%d.png"), aniNum * 2 + 2, speed);
}
/*����*/
Enemy::~Enemy()
{
	delete playerAni;
	playerAni = nullptr;
}

/*
���ݳ�ʼ��
*/
void Enemy::Init()
{
	for (int i = 0; i < 4; ++i)
	{
		h_fx[i] = false;
	}
	speed_time = GetTickCount();
	playerAni->getAniSize(_W_, _H_);
}


/*������ݳ�ʼ��*/
void Enemy::InitRandom()
{
	// �����������
	// �������λ��
}

/*
�ƶ� ׷�����
* @player	�������
*/
void Enemy::Move(const Player & player)
{
	double x, y;
	player.getPosition(x, y);

	setFx(0, y < m_y);
	setFx(1, y > m_y);
	setFx(2, x < m_x);
	setFx(3, x > m_x);

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
	speed_time = t_time;
}

/*�Ƿ��ƶ���*/
bool Enemy::isMove()
{
	return h_fx[0] || h_fx[1] || h_fx[2] || h_fx[3];
}

/*���ƽ�ɫ*/
void Enemy::Draw()
{
	playerAni->play(m_x - _W_ / 2, m_y - _H_ / 2);
}

/*
���÷�������
@n	�±� 0123 ��������
@m	�Ƿ��ƶ�
*/
void Enemy::setFx(int index, bool m)
{
	if (h_fx[index] != m)
	{
		h_fx[index] = m;
	}
}

/*ˢ������*/
void Enemy::upData()
{
	playerAni->DrawPlayer();
}