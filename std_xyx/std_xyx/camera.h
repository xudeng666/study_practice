#pragma once

#include "timer.h"
#include "vector2.h"
#include "game_type.h"

#include <SDL.h>

class Camera
{
public:
	Camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_on_timeout([&]()
			{
				is_shaking = false;
				reset();
			});
	}

	~Camera() = default;

	void reset()
	{
		position.x = 0;
		position.y = 0;
	}

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

	void on_update(float delta)
	{
		timer_shake.on_update(delta);
		if (is_shaking)
		{
			position = position.getCircleRandVct(shaking_strength);
		}
	}

	/// <summary>
	/// ִ�ж���
	/// </summary>
	/// <param name="strength">���ö������Ȱ뾶</param>
	/// <param name="timer">���ö���ʱ��</param>
	void shake(float strength, float timer)
	{
		shaking_strength = strength;
		is_shaking = true;
		timer_shake.set_wait_time(timer);
		timer_shake.restart();
	}
private:
	Vector2 position;					//�����λ��
	Timer timer_shake;					//������ʱ��
	bool is_shaking = false;			//�Ƿ񶶶�
	float shaking_strength = 0.0f;		//��������
};