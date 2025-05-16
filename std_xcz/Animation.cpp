#include "Animation.h"


/*
���캯��
@path ��Դ·��
@num ��Դ����
@speed	�����ٶ�
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
��������
@x	x����λ��
@y	y����λ��
*/
void Animation::play(int x, int y)
{
	int t = ani_fx ? idx_frame + frameNum : idx_frame;
	putimage_alpha(x, y, atlas->getFrameByIndex(t));
}

/*
* ���ò������� �����ֹͣ֡
@isMove �Ƿ��ƶ�
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
* ���ò�������
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
��ȡ�����ߴ�
@w	��ֵ����w
@h	��ֵ����h
*/
void Animation::getAniSize(int& w, int& h)
{
	atlas->getFrameSize(w, h);
}


/*
��ȡ����֡��
*/
unsigned int Animation::getAniFrameNum()
{
	return frameNum;
}