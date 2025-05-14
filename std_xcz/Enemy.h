#pragma once
#include "Player.h"

/*敌人类*/

class Enemy
{
public:
	/*
	* 构造函数
	@num 动画帧数
	@spd 角色初始速度
	*/
	Enemy(int num, double spd);
	/*析构*/
	~Enemy();

	/*
	数据初始化
	*/
	void Init();

	/*随机数据初始化*/
	void InitRandom();

	/*
	移动 追逐玩家
	* @player	玩家数据
	*/
	void Move(const Player& player);

	/*是否移动中*/
	bool isMove();

	/*绘制角色*/
	void Draw();

	/*
	设置方向数据
	@n	下标 0123 上下左右
	@m	是否移动
	*/
	void setFx(int index, bool m);

	/*刷新数据*/
	void upData();


private:
	// 角色坐标x
	double m_x;
	// 角色坐标y
	double m_y;
	// 角色宽度
	int _W_;
	// 角色高度
	int _H_;
	// 角色动画帧数
	const int aniNum;
	// 速度计算时间
	DWORD speed_time = 0;
	// 角色方向数据
	bool h_fx[4];
	// 角色速度
	double speed = 10;
	// 根号2值
	const double SQRT2 = sqrt(2);
	// 角色动画
	Animation* playerAni = nullptr;
	// 敌人类型
	unsigned int _type = 1;
};


