#include "game_obj.h"
#include "game_wnd.h"

#include <assert.h>


GameObj::GameObj(const std::string id)
{
	set_ID(id);
}

GameObj::GameObj(const std::string id, const int num)
{
	set_ID(id, num);
}

GameObj::~GameObj()
{
	std::cout << "Destroying ~GameObj id  "<< get_path_ID() <<" at: " << this << std::endl;
}

void GameObj::on_init()
{
}

void GameObj::on_enter()
{
}

void GameObj::on_exit()
{
	anchor_referent_node.reset();
}

void GameObj::on_input(const SDL_Event& event)
{
}

void GameObj::on_update(float delta)
{
}

void GameObj::on_render()
{
}

void GameObj::set_ID(const std::string& str)
{
	ID = str;
}

void GameObj::set_ID(const std::string& str, const int num)
{
	ID = str + std::to_string(num);
}

std::string GameObj::get_ID()
{
	return ID;
}

std::string GameObj::get_path_ID()
{
	GameObj* parent = get_parent();
	return parent ? parent->get_path_ID() + "/" + ID : ID;
}

void GameObj::set_self_node(TreeNode_WP self)
{
	assert((self.lock() && self.lock()->get_obj() == this) && "自身节点不能为空或指向别的数据！");
	self_node = self;
}

GameObj* GameObj::get_parent()
{
	auto node = self_node.lock();
	if (node)
	{
		auto parent = node->get_parent();
		if (parent)
		{
			return parent->get_obj();
		}
	}
	return  nullptr;
}

bool GameObj::id_contains(const std::string& str)
{
	return ID.find(str) != std::string::npos;
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

double GameObj::get_rotation()
{
	GameObj* p = get_anchor_referent();
	double val = p ? p->get_rotation() : 0;
	return val + angle;
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

void GameObj::set_anchor_referent_node(TreeNode_WP node)
{
	anchor_referent_node.reset();
	anchor_referent_node = node;
}

GameObj* GameObj::get_anchor_referent()
{
	auto node = anchor_referent_node.lock();
	if (node)
	{
		return node->get_obj();
	}
	return  nullptr;
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
	if (anchor_referent_node.lock()) // 获取锚定节点的对齐锚点全局坐标
	{
		t = anchor_referent_node.lock()->get_obj()->get_anchor_position(anchor_referent_mode);
	}

	Vector2 p = position;
	int m = static_cast<int>(mode);
	int a = static_cast<int>(anchor_mode);

	p.x += (m % 3 - a % 3) * size.x / 2;
	p.y += (m / 3 - a / 3) * size.y / 2;
	t += p;

	return t;
}

Vector2 GameObj::get_anchor_position(TreeNode_WP node, const AnchorMode mode)
{
	Vector2 t = { 0.0f,0.0f };
	if (node.lock()) // 获取锚定对象的对齐锚点全局坐标
	{
		t = node.lock()->get_obj()->get_anchor_position(anchor_referent_mode);
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

bool GameObj::check_in_screen(int val)
{
	GameWnd* wnd = GameWnd::instance();
	assert(wnd != nullptr && "GameWnd 应已完成实例化");

	SDL_FRect r = get_FRect();
	int w = wnd->get_width();
	int h = wnd->get_height();

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