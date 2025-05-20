#pragma once
#include "Vector2.h"

/*�������*/
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
	/*�ص�ԭ��*/
	void reset_position()
	{
		position.x = 0, position.y = 0;
	}

	void on_update(int delta)
	{
		const Vector2 speed = { -0.35f, 0 };
		position += speed * (float)delta;
	}

private:
	Vector2 position;
};

