#include "game_obj.h"
#include "game_wnd.h"
#include "event_mgr.h"

#include "SDL_util.h"

#include <assert.h>

INIT_TYPE_NAME(GameObj);

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
	std::cout << "Destroying ~GameObj id  "<< path_id << std::endl;
}

void GameObj::on_init()
{
	set_added_fun([&]() {
		set_path_ID();
		});
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
	if (_DE_BUG_)
	{
		SDL_Rect r = get_Rect();
		GameWnd::instance()->render_line_rect(&r);
	}
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
	return path_id;
}

void GameObj::set_path_ID()
{
	path_id = ID;
	auto p = parent.lock();
	if (p && p->get_node_type() == NodeType::GAMENODE)
	{
		//std::cout << "get_path_ID" << std::endl;
		path_id = p->get_path_ID() + "/" + ID;
	}
}

bool GameObj::id_contains(const std::string& str)
{
	return ID.find(str) != std::string::npos;
}

void GameObj::set_position(const Vector2& pos)
{
	position = pos;
}

void GameObj::set_position(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

const Vector2& GameObj::get_position() const
{
	return position;
}

const Vector2& GameObj::get_rect_position()
{
	return get_rect_pos(anchor_mode);
}

void GameObj::set_size(const SDL_Point& size)
{
	this->size = size;
}

void GameObj::set_size(const int w, const int h)
{
	size.x = w;
	size.y = h;
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

void GameObj::set_center(const Vector2& pos)
{
	center = pos;
}
void GameObj::set_center(const float x, const float y)
{
	center.x = x;
	center.y = y;
}
Vector2 GameObj::get_center()
{
	return center;
}
SDL_FPoint GameObj::get_center_point()
{
	Vector2 p = get_anchor_difference(AnchorMode::TOPLEFT, angle_anchor_mode) + center;
	return { p.x, p.y };
}
void GameObj::set_angle_anchor_mode(const AnchorMode mode)
{
	angle_anchor_mode = mode;
}
AnchorMode GameObj::get_angle_anchor_mode()
{
	return angle_anchor_mode; 
}
void GameObj::set_enable_angle(bool tga)
{
	enable_angle = tga;
}
bool GameObj::get_enable_angle()
{
	return enable_angle;
}
bool GameObj::get_extend_enable_angle()
{
	bool tag = enable_angle;
	if (!tag)
	{
		auto ref = get_anchor_referent();
		if (ref)
		{
			return ref->get_extend_enable_angle();
		}
	}
	return tag;
}
void GameObj::set_rotation(double val)
{
	angle = val;
}

double GameObj::get_rotation()
{
	return getRadiansByAngle(get_angle());
}

double GameObj::get_angle()
{
	auto p = get_anchor_referent();
	double val = p ? p->get_angle() : 0;
	return (val + (enable_angle ? angle : 0));
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

TreeNode_SP GameObj::get_anchor_referent()
{
	if (anchor_referent_node.expired())
	{
		if (parent.expired())
		{
			return nullptr;
		}
		anchor_referent_node = parent;
	}
	return  anchor_referent_node.lock();
}

Vector2 GameObj::get_rect_pos(const AnchorMode m)
{
	return get_center_position() + get_anchor_difference(AnchorMode::CENTER, m);
}

SDL_FRect GameObj::get_FRect()
{
	Vector2 p = get_rect_pos(AnchorMode::TOPLEFT);
	SDL_Point s = get_size();
	return { p.x, p.y, (float)s.x, (float)s.y };
}

SDL_Rect GameObj::get_Rect()
{
	Vector2 p = get_rect_pos(AnchorMode::TOPLEFT);
	SDL_Point s = get_size();
	return { (int)p.x, (int)p.y, s.x, s.y };
}

Vector2 GameObj::get_anchor_difference(const AnchorMode p, const AnchorMode t, Vector2 t_size)
{
	if (p == t)
	{
		return Vector2(0, 0);
	}
	int m = static_cast<int>(t);
	int a = static_cast<int>(p);

	return Vector2((m % 3 - a % 3) * t_size.x / 2, (m / 3 - a / 3) * t_size.y / 2);
}

Vector2 GameObj::get_anchor_difference(const AnchorMode p, const AnchorMode t)
{
	if (p == t)
	{
		return Vector2(0, 0);
	}
	int m = static_cast<int>(t);
	int a = static_cast<int>(p);

	SDL_Point s = get_size();
	return Vector2((m % 3 - a % 3) * s.x / 2, (m / 3 - a / 3) * s.y / 2);
}

Vector2 GameObj::get_rotatio_center_position()
{
	/*旋转核心代码*/
	/*本函数所求取的，本节点的旋转中心点全局坐标 = 父节点旋转中心 + 父节点锚点差 + 本节点坐标 + 本节点锚点差 + 父节点旋转差*/ 
	Vector2 cc = { 0,0 };
	// 本节点锚定差
	Vector2 ct = get_anchor_difference(angle_anchor_mode, anchor_mode);
	Vector2 cm = position + ct + center; 
	// 获取父节点中心点全局坐标
	auto ref = get_anchor_referent();

	if (ref)
	{
		if (ref->get_extend_enable_angle())
		{
			Vector2 pc = ref->get_rotatio_center_position();
			Vector2 pp = ref->get_center();
			Vector2 pt = get_anchor_difference(anchor_referent_mode, ref->get_angle_anchor_mode());
			cc = pc - pp + pt + cm;

			if (ref->get_enable_angle())// 计算父节点旋转差
			{
				cc = get_Rotate_Vector(cc, pc, ref->get_rotation());
			}
		}
		else
		{
			cc = ref->get_anchor_position(anchor_referent_mode) + cm;
		}
	}
	else // 没有父节点则为屏幕中心(应该为相机中心，不过本项目不考虑相机旋转问题，相机只作为一个点存在)
	{
		cc = get_anchor_position(anchor_referent_mode) + cm - position;
	}

	return cc;
}

Vector2 GameObj::get_center_position()
{
	if (get_extend_enable_angle())
	{
		Vector2 cc = get_rotatio_center_position();
		Vector2 ct = get_anchor_difference(angle_anchor_mode, AnchorMode::CENTER);
		Vector2 mc = cc - center + ct;
		if (enable_angle)
		{
			mc = get_Rotate_Vector(mc, cc, get_rotation());
		}
		return mc;
	}
	else
	{
		return get_anchor_position(AnchorMode::CENTER);
	}
}

Vector2 GameObj::get_anchor_position(const AnchorMode mode)
{
	// 如果没有父节点，则统一锚屏幕中心
	Vector2 t = GameWnd::instance()->get_center();
	auto ref = get_anchor_referent();
	if (ref)
	{
		t = ref->get_anchor_position(anchor_referent_mode);
	}

	Vector2 p = position;
	p += get_anchor_difference(anchor_mode, mode);
	t += p;

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


bool GameObj::contains_point(const SDL_Point* point)
{
	SDL_Rect r = get_Rect();
	return  SDL_PointInRect(point, &r);
}
/*获取透明度*/
float GameObj::get_alpha()
{
	auto p = parent.lock();
	float a = alpha;
	if (p)
	{
		a *= p->get_alpha();
	}
	return a;
}
/*设置透明度*/
void GameObj::set_alpha(float alp)
{
	alpha = alp;
}