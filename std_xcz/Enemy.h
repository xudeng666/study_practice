#pragma once
#include "Player.h"
#include "Bullet.h"
#include <iostream>
#include <random>

enum COllISION
{
	PLAYER = 0,
	BULLET,
	OTHER
};

/*敌人类*/
class Enemy
{
public:
	/*
	* 构造函数
	@w	窗口宽度
	@h	窗口高度
	*/
	Enemy(int w, int h);
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
	void Move(const Player* player);

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

	/*
	* 判断是否和某个坐标点碰撞
	* @p 坐标
	*/
	bool checkOfPoint(const POINT& p);

	/*
	* 与玩家碰撞检测
	* @plyer
	*/
	bool checkPlayer(Player* player);

	/*
	* 与子弹碰撞检测
	* @bullet
	*/
	bool checkBullet(Bullet* bullet);

	/*
	* 与玩家碰撞检测
	* @plyer
	*/
	COllISION checkCollision(Player* player);

private:
	// 坐标
	POINT position;
	// 角色宽度
	int _W_;
	// 角色高度
	int _H_;
	// 角色动画帧数
	int aniNum;
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
	// 地图宽度
	int _mapw_;
	// 地图高度
	int _maph_;
};


