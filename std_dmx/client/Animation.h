#pragma once

#include "util.h"
#include "Timer.h"
#include "Atlas.h"
#include "Vector2.h"

#include <vector>
#include <functional>

class Animation
{
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_callback([&]()
			{
				++idx_frame;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && callback)
					{
						callback();
					}
				}
			});
	}
	~Animation() = default;


	/*重置动画状态*/
	void reset()
	{
		timer.restart();
		idx_frame = 0;
	}

	/*设置循环*/
	void set_loop(bool loop)
	{
		is_loop = loop;
	}

	/*设置帧间隔*/
	void set_interval(float val)
	{
		timer.set_wait_time(val);
	}

	/*设置位置*/
	void set_position(const Vector2& pos)
	{
		position = pos;
	}

	/**
	* 添加帧动画
	* @param img 图集资源
	* @param num 数量
	*/
	void add_frame(IMAGE* img, int num)
	{
		int w = img->getwidth();
		int h = img->getheight();
		int wf = w / num;
		for (int i = 0; i < num; i++)
		{
			Rect src = { i * wf, 0, wf, h };
			frame_list.emplace_back(img, src);
		}
	}

	/*
	* 添加帧动画
	* @param atl 图集资源
	*/
	void add_frame(Atlas* atl)
	{
		for (int i = 0; i < atl->get_imglist_size(); i++)
		{
			IMAGE* img = atl->getImage(i);
			Rect src = { 0, 0, img->getwidth(), img->getheight() };
			frame_list.emplace_back(img, src);
		}
	}

	/*获取当前帧索引*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*获取当前帧图片*/
	IMAGE* get_frame()
	{
		return frame_list[idx_frame].img;
	}
	/*动画是否播放完毕*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == frame_list.size() - 1);
	}
	/*动画更新*/
	void on_update(float delta)
	{
		timer.on_update(delta);
	}
	/*绘制动画*/
	void on_draw(const Camera& camera)
	{
		const Frame& fm = frame_list[idx_frame];
		Rect dst = { (int)position.x - fm.rect_src.w / 2,(int)position.y - fm.rect_src.h / 2,fm.rect_src.w, fm.rect_src.h };
		putimage_ex(camera, fm.img, &dst, &fm.rect_src);
	}
	/*设置回调函数*/
	void set_call_back(std::function<void()> callback)
	{
		this->callback = callback;
	}

private:
	struct Frame
	{
		/*裁剪区域*/
		Rect rect_src;
		/*图集资源*/
		IMAGE* img = nullptr;
		Frame() = default;
		Frame(IMAGE* image, const Rect& src) :img(image), rect_src(src) {}
		~Frame() = default;
	};
private:
	/*定时器*/
	Timer timer;
	/*位置*/
	Vector2 position;
	// 帧索引
	size_t idx_frame = 0;
	// 是否循环
	bool is_loop = true;
	/*资源列表*/
	std::vector<Frame> frame_list;
	// 动画播放完的回调函数
	std::function<void()> callback;
};