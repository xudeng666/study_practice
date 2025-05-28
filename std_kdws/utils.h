#pragma once
#include <graphics.h>
#include <random>
/*�������ļ�*/

/*
* ����ͼƬ��Ӱ
* @src	ԭʼͼƬ
* @dst	��ͼƬ
* @rgb	���ü�Ӱ��ɫ��Ĭ�ϰ�ɫ��
*/
inline void set_silh_img(IMAGE* src, IMAGE* dst, DWORD rgb = 0xFFFFFFFF)
{
	int w = src->getwidth();
	int h = src->getheight();
	dst->Resize(w, h);

	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	for (int i = 0; i < w * h; ++i)
	{
		if (src_buf[i] & 0xFF000000 >> 24)
		{
			dst_buf[i] = rgb;
		}
	}
}

/*
* ��ȡ�������
* @min = 0	��Сֵ
* @max = 1	���ֵ
*/
inline int getIntRand(int min = 0, int max = 1)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

/*
* ��ȡ���������
* @min = 0.0	��Сֵ
* @max = 1.0	���ֵ
*/
inline float getRealRand(float min = 0.0, float max = 1.0)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}

/*
* ��ȡ�����˹�ֲ���ֵ
* @<T>			����ģ�壺int float double...
* @mean			��ֵ
* @std_dev		��׼��
*/
template <typename T>
inline T getRormalDistributionRand(T mean, T std_dev)
{
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::normal_distribution<T> dist(mean, std_dev);
	return dist(gen);
}

/*
* �жϵ�;����Ƿ���ײ
*/
template <typename T>
inline bool checkPointToRect(const T x, const T y, 
	const T left, const T right, const T top, const T bottom)
{
	return x >= left && x <= right && y >= top && y <= bottom;
}

/*
* �жϾ��κ;����Ƿ���ײ
*/
template <typename T>
inline bool checkRectToRect(const T pleft, const T pright, const T ptop, const T pbottom, 
	const T left, const T right, const T top, const T bottom)
{
	return pleft <= right
		&& left <= pright
		&& ptop <= bottom
		&& top <= pbottom;
}

/*
* �жϾ��κ�ˮƽ�߶�
*/
template <typename T>
inline bool checkRectToHLine(const T pleft, const T pright, const T ptop, const T pbottom, 
	const T left, const T right, const T y)
{
	return pleft <= right
		&& left <= pright
		&& ptop <= y
		&& y <= pbottom;
}