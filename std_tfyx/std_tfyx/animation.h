#pragma once
#include "atlas.h"
#include "camera.h"

#include <vector>

/*动画类*/
class Animation
{
public:
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout([&]()
			{
				++idx_frame;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
					if (!is_loop && on_finished)
					{
						on_finished();
					}
				}
			}
		);
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
	/*设置中心*/
	void set_center(const SDL_FPoint& pos)
	{
		center = pos;
	}
	/*设置角度*/
	void set_rotation(double val)
	{
		angle = val;
	}

	/**
	* 添加帧动画
	* @param texture 图集资源
	* @param num 数量
	*/
	void add_frame(SDL_Texture* texture, int num)
	{
		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		int wf = w / num;

		for (int i = 0; i < num; i++)
		{
			SDL_Rect src = { i * wf, 0, wf, h };
			frame_list.emplace_back(texture, src);
		}
	}
	/*
	* 添加帧动画
	* @param atl 图集资源
	*/
	void add_frame(Atlas* atl)
	{
		for (int i = 0; i < atl->get_size(); i++)
		{
			SDL_Texture* texture = atl->get_texture(i);

			int w, h;
			SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

			SDL_Rect src = { 0,0,w,h };
			frame_list.emplace_back(texture, src);
		}
	}

	/*获取当前帧索引*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*获取当前帧纹理*/
	SDL_Texture* get_frame()
	{
		return frame_list[idx_frame].texture;
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
	void on_render(const Camera& camera) const
	{
		const Frame& frame = frame_list[idx_frame];

		SDL_FRect dst = { position.x - frame.rect_src.w / 2, position.y - frame.rect_src.h / 2, (float)frame.rect_src.w, (float)frame.rect_src.h };
		camera.render_texture(frame.texture, &frame.rect_src, &dst, angle, &center);
	}
	/*设置回调函数*/
	void set_on_finished(std::function<void()> func)
	{
		on_finished = func;
	}

private:
	struct Frame
	{
		/*裁剪区域*/
		SDL_Rect rect_src;
		/*纹理*/
		SDL_Texture* texture = nullptr;
		Frame() = default;
		Frame(SDL_Texture* texture, const SDL_Rect& src) :texture(texture), rect_src(src) {}
		~Frame() = default;
	};
private:
	/*定时器*/
	Timer timer;
	/*位置*/
	Vector2 position;
	// 旋转
	double angle = 0;
	// 中心点
	SDL_FPoint center = { 0 };
	// 帧索引
	size_t idx_frame = 0;
	// 是否循环
	bool is_loop = true;
	/*资源列表*/
	std::vector<Frame> frame_list;
	// 动画播放完的回调函数
	std::function<void()> on_finished;
};

