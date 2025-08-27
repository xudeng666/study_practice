#pragma once
#include <random>
#include <cmath>
#include <stdexcept>
#include <string>

#define _PI_ acos(-1)
#define _WIN_W_ 1280
#define _WIN_H_ 720
#define _FPS_ 60
#define _DE_BUG_ true
//#define _DE_BUG_ false

/*�������ļ�*/

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

/// <summary>
/// �Ƕ�ת����
/// </summary>
/// <param name="angle">�Ƕ�ֵ</param>
/// <returns>����ֵ</returns>
inline double getRadiansByAngle(double angle)
{
	return angle * _PI_ / 180;
}

/// <summary>
/// ����ת�Ƕ�
/// </summary>
/// <param name="radians">����ֵ</param>
/// <returns>�Ƕ�ֵ</returns>
inline double getAngleByRadians(double radians)
{
	return radians * 180 / _PI_;
}

inline bool splitByLastChar(const std::string& str, const char delimiter, std::string& name, int& size ) {
	// ���ҵ�����һ���ָ�����λ��
	size_t lastPos = str.rfind(delimiter);

	if (lastPos == std::string::npos || lastPos == str.size() - 1) {
		// δ�ҵ��ָ�������û�����ֺ�׺
		return false;
	}
	name = str.substr(0, lastPos);
	std::string num = str.substr(lastPos + 1);
	try {
		size = std::stoi(str);
	}
	catch (const std::invalid_argument&) {
		//"���ֲ��ֺ��������ַ�: "
		return false;
	}
	catch (const std::out_of_range&) {
		//"���ֳ��� int ��Χ: "
		return false;
	}
	return true;
}