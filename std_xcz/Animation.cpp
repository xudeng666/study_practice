#include "Animation.h"


/*
���캯��
@path ��Դ·��
@num ��Դ����
@speed	�����ٶ�
*/
Animation::Animation(LPCTSTR path, int num, double speed)
{
	ani_speed = speed;
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

/*
���캯��
@path ��Դ·��
@type ����
@num ��Դ����
@speed	�����ٶ�
*/
Animation::Animation(LPCTSTR path, unsigned int type, int num, double speed)
{
	ani_speed = speed;
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, type, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

Animation::~Animation()
{
	for (size_t i = 0; i < frame_list.size(); ++i)
	{
		delete frame_list[i];
		frame_list[i] = nullptr;
	}
}
/*
��������
@x	x����λ��
@y	y����λ��
*/
void Animation::play(int x, int y)
{
	int t = ani_fx ? idx_frame + frame_list.size() / 2 : idx_frame;
	putimage_alpha(x, y, frame_list[t]);
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
	int t = frame_list.size() / 2 - 1;
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
	idx_frame %= (frame_list.size() / 2);
}

void Animation::setAniSpeed(double speed)
{
	ani_speed = speed;
}

void Animation::setFx(bool isLeft)
{
	ani_fx = isLeft;
}