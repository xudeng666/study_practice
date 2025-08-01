#pragma once

#include <random>

#define PI 3.14159265

/*工具类文件*/

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

/// <summary>
/// 角度转弧度
/// </summary>
/// <param name="angle">角度值</param>
/// <returns>弧度值</returns>
inline double getRadiansByAngle(double angle)
{
	return angle * PI / 180;
}

/// <summary>
/// 弧度转角度
/// </summary>
/// <param name="radians">弧度值</param>
/// <returns>角度值</returns>
inline double getAngleByRadians(double radians)
{
	return radians * 180 / PI;
}