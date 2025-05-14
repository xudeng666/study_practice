#include "Enemy.h"


/*
* 构造函数
@num 动画帧数
@spd 角色初始速度
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
/*析构*/
Enemy::~Enemy()
{
	delete playerAni;
	playerAni = nullptr;
}

/*
数据初始化
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


/*随机数据初始化*/
void Enemy::InitRandom()
{
	// 随机敌人类型
	// 随机出生位置
}

/*
移动 追逐玩家
* @player	玩家数据
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

/*是否移动中*/
bool Enemy::isMove()
{
	return h_fx[0] || h_fx[1] || h_fx[2] || h_fx[3];
}

/*绘制角色*/
void Enemy::Draw()
{
	playerAni->play(m_x - _W_ / 2, m_y - _H_ / 2);
}

/*
设置方向数据
@n	下标 0123 上下左右
@m	是否移动
*/
void Enemy::setFx(int index, bool m)
{
	if (h_fx[index] != m)
	{
		h_fx[index] = m;
	}
}

/*刷新数据*/
void Enemy::upData()
{
	playerAni->DrawPlayer();
}