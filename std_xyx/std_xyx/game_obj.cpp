#include "game_obj.h"


void GameObj::on_input(const SDL_Event& event)
{
	if (!click_enabled)
	{
		return;
	}

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		{
			SDL_Point p = { event.motion.x,event.motion.y };
			on_cursor_hover(SDL_PointInRect(&p, &click_rect));
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.motion.x,event.motion.y };
			if (SDL_PointInRect(&p, &click_rect))
			{
				on_cursor_down();
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.motion.x,event.motion.y };
			if (SDL_PointInRect(&p, &click_rect))
			{
				on_cursor_up();
			}
		}
		break;
	}
}

void GameObj::set_position(const Vector2& pos)
{
	position = pos;
}

const Vector2& GameObj::get_position() const
{
	return position;
}

void GameObj::set_size(const SDL_Point& size)
{
	this->size = size;
}
const SDL_Point& GameObj::get_size() const
{
	return size;
}

void GameObj::set_center(const SDL_FPoint& pos)
{
	center = pos;
}

void GameObj::set_rotation(double val)
{
	angle = val;
}

void GameObj::set_enabled(bool enable)
{
	click_enabled = enable;
}

bool GameObj::get_enabled()
{
	return click_enabled;
}

void GameObj::set_rect(SDL_Rect* rect)
{
	if (!click_enabled) 
		return;

	if (rect != nullptr)
	{
		click_rect = *rect;
		return;
	}
	SDL_FRect rst = { position.x, position.y, (float)size.x, (float)size.y };
	SDL_FRect dst = get_dst_rect(rst, anchor_mode);
	// 默认为对象尺寸
	click_rect = { (int)dst.x,(int)dst.y,(int)dst.w,(int)dst.h };
}

void GameObj::set_anchor_mode(const AnchorMode mode)
{
	anchor_mode = mode;
}

const AnchorMode GameObj::get_anchor_mode() const
{
	return anchor_mode;
}