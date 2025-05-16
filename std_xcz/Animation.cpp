#include "Animation.h"


/*
构造函数
@path 资源路径
@num 资源数量
@speed	播放速度
*/
Animation::Animation(Atlas* atl, double speed)
{
	ani_speed = speed;
	atlas = atl;
	frameNum = atlas->getFrameNum() / 2;
}

//Animation::~Animation()
//{
//}
/*
动画播放
@x	x坐标位置
@y	y坐标位置
*/
void Animation::play(int x, int y)
{
	int t = ani_fx ? idx_frame + frameNum : idx_frame;
	putimage_alpha(x, y, atlas->getFrameByIndex(t));
}

/*
* 设置播放数据 针对有停止帧
@isMove 是否移动
*/
void Animation::DrawPlayer(bool isMove)
{
	DWORD t_time = GetTickCount();

	if ((t_time - timer) >= 1000 / ani_speed)
	{
		timer = t_time;
		idx_frame++;
	}
	int t = frameNum - 1;
	idx_frame = isMove ? (idx_frame % t) : t;
}

/*
* 设置播放数据
*/
void Animation::DrawPlayer()
{
	DWORD t_time = GetTickCount();
	if ((t_time - timer) >= 1000 / ani_speed)
	{
		timer = t_time;
		idx_frame++;
	}
	idx_frame %= frameNum;
}

void Animation::setAniSpeed(double speed)
{
	ani_speed = speed;
}

void Animation::setFx(bool isLeft)
{
	ani_fx = isLeft;
}

/*
获取动画尺寸
@w	赋值变量w
@h	赋值变量h
*/
void Animation::getAniSize(int& w, int& h)
{
	atlas->getFrameSize(w, h);
}


/*
获取动画帧数
*/
unsigned int Animation::getAniFrameNum()
{
	return frameNum;
}