#pragma once
#include <functional>

/*定时器类*/
class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}
	void set_wait_time(float val)
	{
		wait_time = val;
	}
	//是否单次触发
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}
	void set_call_back(std::function<void()> callback)
	{
		this->callback = callback;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void on_update(float delta)
	{
		if (paused)
		{
			return;
		}
		pass_time += delta;
		if (pass_time >= wait_time)
		{
			if ((!one_shot || (one_shot && !shotted)) && callback)
			{
				callback();
			}
			shotted = true;
			pass_time -= wait_time;
		}
	}

private:
	float pass_time = 0;				//已过时间
	float wait_time = 0;				//等待时间
	bool paused = false;			//是否暂停
	bool shotted = false;			//是否触发
	bool one_shot = false;			//是否单次触发
	std::function<void()> callback;	//触发回调

};

