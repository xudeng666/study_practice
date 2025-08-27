#pragma once

#include "util.h"

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;
public:
	Vector2() = default;
	~Vector2() = default;

	Vector2(float x, float y) :x(x), y(y) {}

	Vector2 operator+(const Vector2& vec)const
	{
		return Vector2(x + vec.x, y + vec.y);
	}

	void operator+=(const Vector2& vec)
	{
		x += vec.x;
		y += vec.y;
	}

	Vector2 operator-(const Vector2& vec)const
	{
		return Vector2(x - vec.x, y - vec.y);
	}

	void operator-=(const Vector2& vec)
	{
		x -= vec.x;
		y -= vec.y;
	}

	float operator*(const Vector2& vec)const
	{
		return x * vec.x + y * vec.y;
	}

	Vector2 operator*(const float val)const
	{
		return Vector2(x * val, y * val);
	}

	void operator*=(const float val)
	{
		x *= val;
		y *= val;
	}

	Vector2 operator/(const float val)const
	{
		return Vector2(x / val, y / val);
	}

	void operator/=(const float val)
	{
		x /= val;
		y /= val;
	}
	/// <summary>
	/// 获取坐标的零点（0，0）长度
	/// </summary>
	/// <returns></returns>
	float length()
	{
		return sqrt(x * x + y * y);
	}
	/// <summary>
	/// 获取单位向量
	/// </summary>
	/// <returns></returns>
	Vector2 normalize()
	{
		float len = length();

		if (0 == len)
		{
			return Vector2(0, 0);
		}

		return Vector2(x / len, y / len);
	}
	/// <summary>
	/// 是否和目标坐标重合
	/// </summary>
	/// <param name="vec">目标坐标</param>
	/// <returns>true重合/false不重合</returns>
	bool approx(const Vector2& vec)
	{
		return (*this - vec).length() <= 0.0001f;
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
};