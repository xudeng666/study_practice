#include "Player.h"
#include <cmath>
#include <iostream>

#define PI acos(-1)


/*
* ���캯��
@num ����֡��
*/
Player::Player()
{
}
/*����*/
Player::~Player()
{
	delete playerAni;
	playerAni = nullptr;
	clearBullet();
}

/*
���ݳ�ʼ��
@w ���ڿ��
@h ���ڸ߶�
*/
void Player::Init(int w, int h, Atlas* atl)
{
	playerAni = new Animation(atl, speed);
	_mapw_ = w;
	_maph_ = h;
	bul_radBf = 0;
	bul_radType = true;
	bul_degrees = 0;
	position.x = _mapw_ / 2;
	position.y = _maph_ / 2;
	for (int i = 0; i < 4; ++i)
	{
		h_fx[i] = false;
	}
	bul_time = speed_time = GetTickCount();
	playerAni->getAniSize(_W_,_H_);
	addBullet(0);
}

/*
��ɫ�ƶ�
@w ���ڿ��
@h ���ڸ߶�
*/
void Player::Move()
{
	DWORD t_time = GetTickCount();

	double c = _W_ * 2 / (playerAni->getAniFrameNum() - 1) * speed * (t_time - speed_time);

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

	if (position.x < _W_ / 2)
	{
		position.x = _W_ / 2;
	}
	else if (position.x > _mapw_ - _W_ / 2)
	{
		position.x = _mapw_ - _W_ / 2;
	}
	if (position.y < _H_ / 2)
	{
		position.y = _H_ / 2;
	}
	else if (position.y > _maph_ - _H_ / 2)
	{
		position.y = _maph_ - _H_ / 2;
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
	playerAni->play(position.x - _W_ / 2, position.y - _H_ / 2);
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


/*
* ��Ҳ���
* @msg	������Ϣ
*/
void Player::processEvent(const ExMessage& msg)
{
	if (msg.message == WM_KEYDOWN || msg.message == WM_KEYUP)
	{
		bool m = msg.message == WM_KEYDOWN;
		switch (msg.vkcode)
		{
		case 'W':
		case 'w':
		case VK_UP:
			setFx(0, m);
			break;
		case 'S':
		case 's':
		case VK_DOWN:
			setFx(1, m);
			break;
		case 'A':
		case 'a':
		case VK_LEFT:
			setFx(2, m);
			break;
		case 'D':
		case 'd':
		case VK_RIGHT:
			setFx(3, m);
			break;
		case 'M':
		case 'm':
			addBullet(m ? 1 : 0);
			break;
		case 'N':
		case 'n':
			redBullet(m ? 1 : 0);
			break;
		}
	}
}

/*
�����ӵ�����
@num	��������
*/
void Player::addBullet(unsigned int num)
{
	bul_num += num;
	while (bul_num > bullet_list.size())
	{
		Bullet* p = new Bullet();
		bullet_list.push_back(p);
	}
}


/*��ȡ�ӵ�����*/
unsigned int Player::getBulletNum()
{
	return bul_num;
}



/*
* ��ȡ�ӵ�
* @index �ӵ��±�
*/
Bullet* Player::getBulletOfIndex(int index)
{
	return bullet_list[index];
}

/*
* ��ȡ�ӵ��б�
*/
vector<Bullet*>& Player::getBulletList()
{
	return bullet_list;
}

/*
�����ӵ�����
@num	��������
*/
void Player::redBullet(unsigned int num)
{
	bul_num -= num;
	if (bul_num < 1)
	{
		bul_num = 1;
	}
}

/*�ӵ�����*/
void Player::flyBullet()
{
	DWORD t_time = GetTickCount();
	DWORD t = t_time - bul_time;
	bul_time = t_time;

	if (bul_radBf < 0)
	{
		bul_radType = true;
	}
	else if (bul_radBf > bul_radBfValue)
	{
		bul_radType = false;
	}

	bul_radType ? bul_radBf += bul_radBfValue * bul_speed * t / 500 : bul_radBf -= bul_radBfValue * bul_speed * t / 500;

	int radius = bul_radBf + bul_radius;

	// ��λʱ��*���ٶ� = �ǶȲ�
	bul_degrees += t * bul_speed * bul_radius * 360 / 1000 / radius;

	for (int i = 0; i < bul_num;++i)
	{
		int dre = bul_degrees + 360 / bul_num * i;
		dre %= 360;
		bullet_list[i]->setPosition(position.x + cos(dre * PI / 180) * radius, position.y - sin(dre * PI / 180) * radius);
	}
}

/*�����ӵ�*/
void Player::drawBullet()
{
	for (int i = 0; i < bul_num;++i)
	{
		bullet_list[i]->Draw();
	}
}

/*����ӵ�*/
void Player::clearBullet()
{
	for (int i = 0; i < bullet_list.size();++i)
	{
		delete bullet_list[i];
		bullet_list[i] = nullptr;
	}
}

/*��ȡ��ɫ����*/
const POINT& Player::getPosition() const
{
	return position;
}

/*
* �ж��Ƿ��ĳ���������ײ
* @p ����
*/
bool Player::checkOfPoint(const POINT& p)
{
	return p.x < position.x + _W_ / 2 &&
		p.x > position.x - _W_ / 2 &&
		p.y < position.y + _H_ / 2 &&
		p.y > position.y - _H_ / 2;
}

/*��ȡ����ָ��*/
Player* Player::_getPlayer()
{
	if (nullptr == _THIS_)
	{
		_THIS_ = new Player();
	}
	return _THIS_;
}