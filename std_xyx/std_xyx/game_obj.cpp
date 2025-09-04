#include "game_obj.h"
#include "game_wnd.h"


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
	if (_DE_BUG_)
	{
		SDL_Rect r = get_Rect();
		GameWnd::instance()->render_line_rect(&r);
	}
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

void GameObj::set_anchor_referent_mode(const AnchorMode mode)
{
	anchor_referent_mode = mode;
}

const AnchorMode GameObj::get_anchor_referent_mode() const
{
	return anchor_referent_mode;
}

void GameObj::set_anchor_referent_obj(GameObj* obj)
{
	anchor_referent_obj = obj;
}

const GameObj* GameObj::get_anchor_referent_obj()
{
	return anchor_referent_obj;
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

Vector2 GameObj::get_anchor_position(const AnchorMode mode)
{
	Vector2 t = { 0.0f,0.0f };
	if (anchor_referent_obj) // 获取父节点的对齐锚点全局坐标
	{
		t = anchor_referent_obj->get_anchor_position(anchor_referent_mode);
	}

	Vector2 p = position;
	int m = static_cast<int>(mode);
	int a = static_cast<int>(anchor_mode);

	p.x += (m % 3 - a % 3) * size.x / 2;
	p.y += (m / 3 - a / 3) * size.y / 2;
	t += p;

	return t;
}

Vector2 GameObj::get_anchor_position(GameObj* obj, const AnchorMode mode)
{
	Vector2 t = { 0.0f,0.0f };
	if (obj) // 获取锚定对象的对齐锚点全局坐标
	{
		t = obj->get_anchor_position(anchor_referent_mode);
	}

	Vector2 p = position;
	int m = static_cast<int>(mode);
	int a = static_cast<int>(anchor_mode);

	p.x += (m % 3 - a % 3) * size.x / 2;
	p.y += (m / 3 - a / 3) * size.y / 2;
	t += p;

	return t;
}

Vector2 GameObj::get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size)
{
	Vector2 t = get_anchor_position(aligned);
	int m = static_cast<int>(target);
	int a = static_cast<int>(reference);
	pos.x += (m % 3 - a % 3) * p_size.x / 2;
	pos.y += (m / 3 - a / 3) * p_size.y / 2;
	t += pos;
	return t;
}

void GameObj::set_parent(GameObj* p)
{
	if (parent == anchor_referent_obj || !anchor_referent_obj)
	{
		anchor_referent_obj = p;
	}
	parent = p;
}

GameObj* GameObj::get_parent()
{
	return parent;
}

std::list<GameObj*>& GameObj::get_children()
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
	obj->set_parent(this);
	children.push_back(obj);
}

void GameObj::remove_children(GameObj* obj)
{
	obj->set_parent(nullptr);
	obj->set_anchor_referent_obj(nullptr);
	children.remove(obj);
}

void GameObj::delete_children(GameObj* obj)
{
	children.remove(obj);
	delete obj;
}

bool GameObj::check_in_screen(int val = 0)
{
	SDL_FRect r = get_FRect();
	int w = GameWnd::instance()->get_width();
	int h = GameWnd::instance()->get_height();

	bool b_w = !(r.x + r.w<0 || r.x>w);
	bool b_h = !(r.y + r.h<0 || r.y>h);

	if (val < 0)
	{
		return b_w;
	}
	else if (val > 0)
	{
		return b_h;
	}
	else
	{
		return b_w && b_h;
	}
}