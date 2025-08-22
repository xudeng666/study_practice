#include "game_obj.h"
#include "game_mgr.h"


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
			SDL_Rect t = get_Rect();
			on_cursor_hover(SDL_PointInRect(&p, &t));
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.motion.x,event.motion.y };
			SDL_Rect t = get_Rect();
			if (SDL_PointInRect(&p, &t))
			{
				on_cursor_down();
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.motion.x,event.motion.y };
			SDL_Rect t = get_Rect();
			if (SDL_PointInRect(&p, &t))
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

void GameObj::set_click_enabled(bool enable)
{
	click_enabled = enable;
}

bool GameObj::get_click_enabled()
{
	return click_enabled;
}

void GameObj::set_anchor_mode(const AnchorMode mode)
{
	anchor_mode = mode;
}

const AnchorMode GameObj::get_anchor_mode() const
{
	return anchor_mode;
}

SDL_FRect GameObj::get_FRect()
{
	Vector2 p = get_anchor_position(anchor_mode);
	return { p.x, p.y, (float)size.x, (float)size.y };
}

SDL_Rect GameObj::get_Rect()
{
	Vector2 p = get_anchor_position(anchor_mode);
	return { (int)p.x, (int)p.y, size.x, size.y };
}

Vector2 GameObj::get_anchor_position(const AnchorMode mode)
{
	float x = 0;
	float y = 0;

	switch (mode)
	{
	case AnchorMode::TOPLEFT:
		x = position.x;
		y = position.y;
		break;
	case AnchorMode::TOPCENTER:
		x = position.x - size.x / 2;
		y = position.y;
		break;
	case AnchorMode::TOPRIGHT:
		x = position.x - size.x;
		y = position.y;
		break;
	case AnchorMode::LEFTCENTER:
		x = position.x;
		y = position.y - size.y / 2;
		break;
	case AnchorMode::CENTER:
		x = position.x - size.x / 2;
		y = position.y - size.y / 2;
		break;
	case AnchorMode::RIGHTCENTER:
		x = position.x - size.x;
		y = position.y - size.y / 2;
		break;
	case AnchorMode::BOTTOMLEFT:
		x = position.x;
		y = position.y - size.y;
		break;
	case AnchorMode::BOTTOMCENTER:
		x = position.x - size.x / 2;
		y = position.y - size.y;
		break;
	case AnchorMode::BOTTOMRIGHT:
		x = position.x - size.x;
		y = position.y - size.y;
		break;
	}
	return Vector2(x, y);
}