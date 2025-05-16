#pragma once
#include <graphics.h>
#include <stdlib.h>
#include "Atlas.h"

/*
* 帧动画基类
*/
class Animation
{
public:
	/*
	构造函数
	@path 资源路径
	@speed	播放速度
	*/
	Animation(Atlas* atl, double speed);

	~Animation() = default;
	/*
	动画播放
	@x	x坐标位置
	@y	y坐标位置
	*/
	void play(int x, int y);

	/*
	* 设置播放数据 针对有停止帧
	@isMove 是否移动
	*/
	void DrawPlayer(bool isMove);
	/*
	* 设置播放数据
	*/
	void DrawPlayer();
	/*
	* 设置速度
	*/
	void setAniSpeed(double speed);
	/*
	* 设置方向
	*/
	void setFx(bool isLeft);

	/*
	获取动画尺寸
	@w	赋值变量w
	@h	赋值变量h
	*/
	void getAniSize(int& w, int& h);
	/*
	获取动画帧数
	*/
	unsigned int getAniFrameNum();
private:
	// 图集指针
	Atlas* atlas;
	// 动画播放速度
	double ani_speed = 0;
	// 动画计时器
	int timer = 0;
	// 动画帧索引
	int idx_frame = 0;
	// 朝向 true 向左 false 向右
	bool ani_fx = false;
	// 动画帧数
	unsigned int frameNum = 0;
};

