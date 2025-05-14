#pragma once
#include "Animation.h"

class Player
{
public:
	/*
	* 构造函数
	@w 角色宽度
	@h 角色高度
	@num 动画帧数
	@spd 角色初始速度
	*/
	Player(int w, int h, int num, double spd);
	/*析构*/
	~Player();

	/*
	数据初始化
	@w 窗口宽度
	@h 窗口高度
	*/
	void Init(int w, int h);

	/*
	角色移动
	@w 窗口宽度
	@h 窗口高度
	*/
	void Move(int w, int h);

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
	const int _W_;
	// 角色高度
	const int _H_;
	// 角色动画帧数
	const int aniNum;
	// 速度计算时间
	DWORD speed_time;
	// 角色方向数据
	bool h_fx[4];
	// 角色速度
	double speed;
	// 根号2值
	const double SQRT2 = sqrt(2);
	// 角色动画
	Animation* playerAni = nullptr;

};

