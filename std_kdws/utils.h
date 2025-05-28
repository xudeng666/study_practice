#pragma once
#include <graphics.h>
#include <random>
/*工具类文件*/

/*
* 设置图片剪影
* @src	原始图片
* @dst	新图片
* @rgb	设置剪影颜色（默认白色）
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
* 获取随机整数
* @min = 0	最小值
* @max = 1	最大值
*/
inline int getIntRand(int min = 0, int max = 1)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

/*
* 获取随机浮点数
* @min = 0.0	最小值
* @max = 1.0	最大值
*/
inline float getRealRand(float min = 0.0, float max = 1.0)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dist(min, max);
	return dist(gen);
}

/*
* 获取随机高斯分布数值
* @<T>			类型模板：int float double...
* @mean			均值
* @std_dev		标准差
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
* 判断点和矩形是否碰撞
*/
template <typename T>
inline bool checkPointToRect(const T x, const T y, 
	const T left, const T right, const T top, const T bottom)
{
	return x >= left && x <= right && y >= top && y <= bottom;
}

/*
* 判断矩形和矩形是否碰撞
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
* 判断矩形和水平线段
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