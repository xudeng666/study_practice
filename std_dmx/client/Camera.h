#pragma once

#include "Vector2.h"

class Camera
{
public:
	Camera() = default;
	~Camera() = default;

	const Vector2& get_position()const
	{
		return position;
	}

	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}

	void set_position(const Vector2& pos)
	{
		position = pos;
	}

	const Vector2& get_size()const
	{
		return size;
	}

	void set_size(float w, float h)
	{
		size.x = w, size.y = h;
	}

	void set_size(const Vector2& vec)
	{
		size = vec;
	}

	void look_at(const Vector2& vec)
	{
		position = vec - size / 2.0f;
	}

private:
	Vector2 position;			//ÉãÏñ»úÎ»ÖÃ
	Vector2 size;				//ÉãÏñ»ú³ß´ç
};