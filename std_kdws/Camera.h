#pragma once
#include "Timer.h"
#include "Vector2.h"

/*摄像机类*/
class Camera
{
public:
	Camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_call_back([&]()
			{
				is_shaking = false;
				reset_position();
			}
		);
	}
	~Camera() = default;

	const Vector2& get_position()const
	{
		return position;
	}

	void set_position(float x, float y)
	{
		position.x = x, position.y = y;
	}
	/*回到原点*/
	void reset_position()
	{
		position.x = 0, position.y = 0;
	}

	void on_update(int delta)
	{
		shake_update(delta);
	}

	/*
	* 抖动
	* @strength	抖动幅度
	* @timer	抖动时长(毫秒)
	*/
	void shake(float strength, int timer)
	{
		timer_shake.set_wait_time(timer);
		timer_shake.restart();
		shaking_strength = strength;
		is_shaking = true;
	}

	void shake_update(int delta)
	{
		timer_shake.on_update(delta);
		if (is_shaking)
		{
			position = position.getCircleRandVct(1.0f * shaking_strength);
		}
	}


private:
	Vector2 position;			//摄像机位置
	Timer timer_shake;			//抖动计时器
	bool is_shaking = false;	//是否抖动
	float shaking_strength = 0;	//抖动幅度
};

