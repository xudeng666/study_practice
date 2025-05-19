#pragma once
#include "util.h"
#include "Atlas.h"
#include <functional>

/*动画类*/
class Animation :
    public Atlas
{
public:
	Animation() = default;
	~Animation() = default;

	/*重置动画状态*/
	void reset()
	{
		timer = 0;
		idx_frame = 0;
	}
	/*设置图集*/
	void set_atlas(Atlas* atl)
	{
		reset();
		atlas = atl;
	}
	/*设置循环*/
	void set_loop(bool loop)
	{
		is_loop = loop;
	}
	/*设置帧间隔*/
	void set_interval(int val)
	{
		interval = val;
	}
	/*获取当前帧索引*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*获取当前帧图片*/
	IMAGE* get_frame()
	{
		return atlas->getImageByIndex(idx_frame);
	}
	/*动画是否播放完毕*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == atlas->get_imglist_size() - 1);
	}
	/*动画更新*/
	void on_updata(int delta)
	{
		timer += delta;
		if (timer >= interval)
		{
			timer = 0;
			if (++idx_frame >= atlas->get_imglist_size())
			{
				idx_frame = is_loop ? 0 : atlas->get_imglist_size() - 1;
				if (!is_loop && callback)
				{
					callback();
				}
			}
		}
	}
	/*绘制动画*/
	void on_draw(int x, int y) const
	{
		putimage_alpha(x, y, atlas->getImageByIndex(idx_frame));
		//putimage_alpha(x, y, get_frame());
	}
	/*设置回调函数*/
	void set_callback(std::function<void()> callback)
	{
		this->callback = callback;
	}

private:
	/*计时器*/
	int timer = 0;
	// 帧间隔
	int interval = 0;
	// 帧索引
	int idx_frame = 0;
	// 是否循环
	bool is_loop = true;
	// 图集
	Atlas* atlas = nullptr;
	// 回调函数
	std::function<void()> callback;
};

