#pragma once
#include "utils.h"
#include <cmath>

/*������*/
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

	/*�������굽ԭ��ľ���*/
	float lenth()
	{
		return sqrt(x * x + y * y);
	}

	/*���㵥λ�����µ���������*/
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

	/*
	* ���������������
	* radius 	�뾶
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

