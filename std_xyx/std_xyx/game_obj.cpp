#include "game_obj.h"
#include "game_mgr.h"


void GameObj::on_enter()
{
}

void GameObj::on_exit()
{
}

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

void GameObj::on_update(float delta)
{
}

void GameObj::on_render()
{
}

void GameObj::set_ID(const std::string id)
{
	ID = id;
}

std::string GameObj::get_ID()
{
	return ID;
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

void GameObj::set_display(bool display)
{
	is_display = display;
}

const bool GameObj::get_display() const
{
	return is_display;
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

void GameObj::set_parent_anchor_mode(const AnchorMode mode)
{
	parent_anchor_mode = mode;
}

const AnchorMode GameObj::get_parent_anchor_mode() const
{
	return parent_anchor_mode;
}

SDL_FRect GameObj::get_FRect()
{
	Vector2 p = get_anchor_position(AnchorMode::TOPLEFT);
	return { p.x, p.y, (float)size.x, (float)size.y };
}

SDL_Rect GameObj::get_Rect()
{
	Vector2 p = get_anchor_position(AnchorMode::TOPLEFT);
	return { (int)p.x, (int)p.y, size.x, size.y };
}

/// <summary>
/// 获取对象锚点的全局坐标
/// </summary>
/// <param name="mode">锚点类型</param>
/// <returns>Vector2</returns>
Vector2 GameObj::get_anchor_position(const AnchorMode mode)
{
	Vector2 t = { 0.0f,0.0f };
	if (parent) // 获取父节点的对齐锚点全局坐标
	{
		t = parent->get_anchor_position(parent_anchor_mode);
	}
	Vector2 p = position;
	int m = static_cast<int>(mode) - static_cast<int>(anchor_mode);
	p.x += ((m % 3) * size.x / 2);
	p.y += ((m / 3) * size.y / 2);
	t += p;
	return t;
}

void GameObj::set_parent(GameObj* p)
{
	parent = p;
}

GameObj* GameObj::get_parent()
{
	return parent;
}

std::list<GameObj*> GameObj::get_children()
{
	return children;
}

void GameObj::add_children(GameObj* obj)
{
	GameObj* p = obj->parent;
	if (p)
	{
		p->children.remove(obj);
	}
	obj->parent = this;
	children.push_back(obj);
}