#pragma once

#include "timer.h"
#include "vector2.h"
#include "game_type.h"

#include <SDL.h>

class Camera
{
public:
	Camera(SDL_Renderer* rend)
	{
		renderer = rend;

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
	/// 执行抖动
	/// </summary>
	/// <param name="strength">设置抖动幅度半径</param>
	/// <param name="timer">设置抖动时长</param>
	void shake(float strength, float timer)
	{
		shaking_strength = strength;
		is_shaking = true;
		timer_shake.set_wait_time(timer);
		timer_shake.restart();
	}
	/// <summary>
	/// 获取dst_rect
	/// </summary>
	/// <param name="pos">位置</param>
	/// <param name="size">尺寸</param>
	/// <param name="mode">锚点</param>
	/// <returns>SDL_FRect</returns>
	SDL_FRect get_dst_rect(Vector2& pos, SDL_Point& size, AnchorMode mode)
	{
		float x = 0;
		float y = 0;

		switch (mode)
		{
		case AnchorMode::TOPLEFT:
			x = pos.x;
			y = pos.y;
			break;
		case AnchorMode::TOPCENTER:
			x = pos.x - size.x / 2;
			y = pos.y;
			break;
		case AnchorMode::TOPRIGHT:
			x = pos.x - size.x;
			y = pos.y;
			break;
		case AnchorMode::LEFTCENTER:
			x = pos.x;
			y = pos.y - size.y / 2;
			break;
		case AnchorMode::CENTER:
			x = pos.x - size.x / 2;
			y = pos.y - size.y / 2;
			break;
		case AnchorMode::RIGHTCENTER:
			x = pos.x - size.x;
			y = pos.y - size.y / 2;
			break;
		case AnchorMode::BOTTOMLEFT:
			x = pos.x;
			y = pos.y - size.y;
			break;
		case AnchorMode::BOTTOMCENTER:
			x = pos.x - size.x / 2;
			y = pos.y - size.y;
			break;
		case AnchorMode::BOTTOMRIGHT:
			x = pos.x - size.x;
			y = pos.y - size.y;
			break;
		}

		return { x, y, (float)size.x, (float)size.y };
	}

	SDL_Rect get_rect_of_frect(SDL_FRect& rect)
	{
		return { (int)rect.x,(int)rect.y,(int)rect.w,(int)rect.h };
	}

	/// <summary>
	/// 渲染纹理
	/// </summary>
	/// <param name="texture">纹理资源指针</param>
	/// <param name="rect_src">纹理rect</param>
	/// <param name="rect_dst">绘制区域Frect</param>
	/// <param name="angle">角度</param>
	/// <param name="center">旋转中心点</param>
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src,
		const SDL_FRect* rect_dst, double angle, const SDL_FPoint* center)const
	{
		SDL_FRect dst = *rect_dst;
		dst.x -= position.x;
		dst.y -= position.y;

		SDL_RenderCopyExF(renderer, texture, rect_src, &dst, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
	}

	//	SDL_RenderCopyExF(renderer, texture, &src, &dst, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
	//}
	/// <summary>
	/// 绘制矩形边框
	/// </summary>
	/// <param name="rect">范围</param>
	void render_line_rect(SDL_Rect* rect)
	{
		SDL_RenderDrawRect(renderer, rect);
	}

private:
	SDL_Renderer* renderer = nullptr;	//渲染器
	Vector2 position;					//摄像机位置
	Timer timer_shake;					//抖动计时器
	bool is_shaking = false;			//是否抖动
	float shaking_strength = 0.0f;		//抖动幅度
};