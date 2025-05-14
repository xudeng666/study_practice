#include "Player.h"


/*
* 构造函数
@w 角色宽度
@h 角色高度
@num 动画帧数
@spd 角色初始速度
*/
Player::Player(int w, int h, int num, double spd) :_W_(w), _H_(h), aniNum(num)
{
	speed = spd;
	speed_time = 0;
	m_x = 0;
	m_y = 0;
}
/*析构*/
Player::~Player()
{
	delete playerAni;
	playerAni = nullptr;
}

/*
数据初始化
@w 窗口宽度
@h 窗口高度
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
角色移动
@w 窗口宽度
@h 窗口高度
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

/*是否移动中*/
bool Player::isMove()
{
	return h_fx[0] || h_fx[1] || h_fx[2] || h_fx[3];
}

/*绘制角色*/
void Player::Draw()
{
	playerAni->play(m_x - _W_ / 2, m_y - _H_ / 2);
}

/*
设置方向数据
@n	下标 0123 上下左右
@m	是否移动
*/
void Player::setFx(int index, bool m)
{
	if (h_fx[index] != m)
	{
		h_fx[index] = m;
	}
}

/*刷新数据*/
void Player::upData()
{
	playerAni->DrawPlayer(isMove());
}