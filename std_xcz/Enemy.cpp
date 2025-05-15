#include "Enemy.h"


/*
* ���캯��
@num ����֡��
@w	���ڿ��
@h	���ڸ߶�
*/
Enemy::Enemy(int w, int h)
{
	_mapw_ = w;
	_maph_ = h;
	Init();
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
	speed = 5;
	speed_time = GetTickCount();
	for (int i = 0; i < 4; ++i)
	{
		h_fx[i] = false;
	}
	InitRandom();
}


/*������ݳ�ʼ��*/
void Enemy::InitRandom()
{
	std::random_device rd;
	std::uniform_int_distribution<int> dist(1, 4);
	// ����������� �����������
	_type = dist(rd);
	aniNum = _type == 1 ? 6 : 4;
	playerAni = new Animation(_T("resources/enemy/gw_%d_%d.png"), _type, aniNum * 2, speed);
	// ��������1234 ��������
	int fx = dist(rd);
	playerAni->getAniSize(_W_, _H_);
	std::uniform_int_distribution<int> mw(0, _mapw_ - 1);
	std::uniform_int_distribution<int> mh(0, _maph_ - 1);
	// �������λ��
	switch (fx)
	{
	case 1:
		position.x = mw(rd);
		position.y = 0 - _H_ / 2;
		break;
	case 2:
		position.x = mw(rd);
		position.y = _maph_ + _H_ / 2;
		break;
	case 3:
		position.x = 0 - _W_ / 2;
		position.y = mh(rd);
		break;
	case 4:
		position.x = _mapw_ + _W_ / 2;
		position.y = mh(rd);
		break;
	}
}

/*
�ƶ� ׷�����
* @player*	�������
*/
void Enemy::Move(const Player* player)
{
	playerAni->DrawPlayer();

	POINT p = player->getPosition();

	setFx(0, p.y < position.y);
	setFx(1, p.y > position.y);
	setFx(2, p.x < position.x);
	setFx(3, p.x > position.x);

	DWORD t_time = GetTickCount();

	double c = _W_ * 2 / aniNum * speed * (t_time - speed_time);

	if ((h_fx[0] || h_fx[1]) && (h_fx[2] || h_fx[3]))
	{
		c /= SQRT2;
	}
	c /= 1000;
	double _x = position.x;
	if (h_fx[0])
	{
		position.y -= c;
	}
	if (h_fx[1])
	{
		position.y += c;
	}
	if (h_fx[2])
	{
		position.x -= c;
	}
	if (h_fx[3])
	{
		position.x += c;
	}

	if (_x > position.x)
	{
		playerAni->setFx(false);
	}
	else if (_x < position.x)
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
	playerAni->play(position.x - _W_ / 2, position.y - _H_ / 2);
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

/*
* �ж��Ƿ��ĳ���������ײ
* @p ����
*/
bool Enemy::checkOfPoint(const POINT& p)
{
	return p.x < position.x + _W_ / 2 &&
		p.x > position.x - _W_ / 2 &&
		p.y < position.y + _H_ / 2 &&
		p.y > position.y - _H_ / 2;
}

/*
* �������ײ���
* @plyer
*/
bool Enemy::checkPlayer(Player* player)
{
	//���������ĵ��Ƿ����������
	return player->checkOfPoint(position);
}

/*
* ���ӵ���ײ���
* @bullet
*/
bool Enemy::checkBullet(Bullet* bullet)
{
	//����ӵ����ĵ��Ƿ��ڹ�������
	return checkOfPoint(bullet->position);
}

/*
* �������ײ���
* @plyer
*/
COllISION Enemy::checkCollision(Player* player)
{
	if (checkPlayer(player))
	{
		return PLAYER;
	}

	unsigned int n = player->getBulletNum();

	for (int i = 0;i < n;++i)
	{
		if (checkBullet(player->getBulletOfIndex(i)))
		{
			return BULLET;
		}
	}
	return OTHER;
}