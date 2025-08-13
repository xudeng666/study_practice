#pragma once

#include "res_mgr.h"
#include "camera.h"

#include <vector>

/*动画类*/
class Animation
{
public:
	Animation(const std::string name, const int num) :name(name), num(num)
	{
		timer.set_one_shot(false);
		timer.set_on_timeout([&]()
			{
				++idx_frame;
				if (idx_frame > num)
				{
					idx_frame = is_loop ? 1 : num;
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

	/*设置锚点*/
	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
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

	/*获取当前帧索引*/
	int get_idx_frame()
	{
		return idx_frame;
	}
	/*获取当前帧纹理*/
	SDL_Texture* get_Texture()
	{
		return ResMgr::instance()->find_texture(name + std::to_string(idx_frame));
	}
	/*动画是否播放完毕*/
	bool check_finished()
	{
		if (is_loop)
		{
			return false;
		}
		return (idx_frame == num);
	}
	/*动画更新*/
	void on_update(float delta)
	{
		timer.on_update(delta);
	}
	/*绘制动画*/
	void on_render(const Camera& camera) //const
	{
		SDL_Texture* texture = get_Texture();

		int w, h;
		SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

		SDL_Rect src = { 0,0,w,h };

		float x, y;

		switch (anchor_mode)
		{
		case AnchorMode::TOPLEFT:
			x = position.x;
			y = position.y;
			break;
		case AnchorMode::TOPCENTER:
			x = position.x - w / 2;
			y = position.y;
			break;
		case AnchorMode::TOPRIGHT:
			x = position.x - w;
			y = position.y;
			break;
		case AnchorMode::LEFTCENTER:
			x = position.x;
			y = position.y - h / 2;
			break;
		case AnchorMode::CENTER:
			x = position.x - w / 2;
			y = position.y - h / 2;
			break;
		case AnchorMode::RIGHTCENTER:
			x = position.x - w;
			y = position.y - h / 2;
			break;
		case AnchorMode::BOTTOMLEFT:
			x = position.x;
			y = position.y - h;
			break;
		case AnchorMode::BOTTOMCENTER:
			x = position.x - w / 2;
			y = position.y - h;
			break;
		case AnchorMode::BOTTOMRIGHT:
			x = position.x - w;
			y = position.y - h;
			break;
		}

		SDL_FRect dst = { x, y, (float)w, (float)h };

		camera.render_texture(texture, &src, &dst, angle, &center);
	}
	/*设置回调函数*/
	void set_on_finished(std::function<void()> func)
	{
		on_finished = func;
	}

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
	// 动画播放完的回调函数
	std::function<void()> on_finished;
	// 资源名
	const std::string name;
	// 资源数量
	const int num;
	// 锚点类型
	AnchorMode anchor_mode = AnchorMode::CENTER;
};

