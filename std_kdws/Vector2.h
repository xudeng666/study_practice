#pragma once
#include "utils.h"
#include <cmath>

/*向量类*/
class Vector2
{
public:
	float x = 0;
	float y = 0;
public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y)
		:x(x), y(y) {}

	void operator+=(const Vector2& vec)
	{
		x += vec.x, y += vec.y;
	}

	Vector2 operator+(const Vector2& vec) const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x, y -= vec.y;
	}

	Vector2 operator-(const Vector2& vec) const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	void operator*=(const Vector2& vec)
	{
		x *= vec.x, y *= vec.y;
	}

	Vector2 operator*(const Vector2& vec) const
	{
		return Vector2(x * vec.x, y * vec.y);
	}

	void operator*=(float val)
	{
		x *= val, y *= val;
	}

	Vector2 operator*(float val) const
	{
		return Vector2(x * val, y * val);
	}

	/*计算坐标到原点的距离*/
	float lenth()
	{
		return sqrt(x * x + y * y);
	}

	/*计算单位长度下的坐标向量*/
	Vector2 normalize()
	{
		float len = lenth();
		if (0==len)
		{
			return Vector2(0, 0);
		}
		return Vector2(x / len, y / len);
	}

	/*
	* 随机圆形区域坐标
	* radius 	半径
	*/
	Vector2 getCircleRandVct(float radius)
	{
		if (0 == radius)
		{
			return Vector2(0, 0);
		}
		float x = getRealRand(-radius, radius);
		float m = sqrt(radius * radius - x * x);
		float y = getRealRand(-m, m);
		return Vector2(x, y);
	}

	/*
	* 随机方形区域坐标
	* radius 	半径
	*/
	Vector2 getSquareRandVct(float radius)
	{
		if (0 == radius)
		{
			return Vector2(0, 0);
		}
		float x = getRealRand(-radius, radius);
		float y = getRealRand(-radius, radius);
		return Vector2(x, y);
	}



};

