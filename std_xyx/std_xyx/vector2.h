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
	/// ��ȡ�������㣨0��0������
	/// </summary>
	/// <returns></returns>
	float length()
	{
		return sqrt(x * x + y * y);
	}
	/// <summary>
	/// ��ȡ��λ����
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
	/// �Ƿ��Ŀ�������غ�
	/// </summary>
	/// <param name="vec">Ŀ������</param>
	/// <returns>true�غ�/false���غ�</returns>
	bool approx(const Vector2& vec)
	{
		return (*this - vec).length() <= 0.0001f;
	}

	/*
	* ���Բ����������
	* radius 	�뾶
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