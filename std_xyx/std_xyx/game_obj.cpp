#include "game_obj.h"
#include "game_wnd.h"


GameObj::GameObj()
{
}

GameObj::GameObj(const Vector2 pos) : position(pos)
{
}

GameObj::~GameObj()
{
	clear_children();
}

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
			SDL_Point p = { event.button.x,event.button.y };
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
			SDL_Point p = { event.button.x,event.button.y };
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
		GameWnd* wnd = GameWnd::instance();
		if (wnd == nullptr) {
			std::cout << "GameWnd  δ��ʼ����" << std::endl;
			return;
		}
		wnd->render_line_rect(&r);
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
	for (auto it = children.begin(); it != children.end(); ++it)
	{
		if (it->get())
		{
			it->get()->set_rotation(val);
		}
	}
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
	if (anchor_referent_obj) // ��ȡ���ڵ�Ķ���ê��ȫ������
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
	if (obj) // ��ȡê������Ķ���ê��ȫ������
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

//std::list<uqp_obj>& GameObj::get_children()
//{
//	return children;
//}

void GameObj::add_children(uqp_obj obj, bool is_front)
{
	// ����1�����ӽڵ�����ԭ���ڵ㣬�ȴ�ԭ���ڵ��Ƴ�
	if (obj->parent != nullptr) {
		auto& old_children = obj->parent->children;
		for (auto it = old_children.begin(); it != old_children.end(); ++it) {
			if (it->get() == obj.get()) { // �ҵ���Ӧ�ӽڵ�� unique_ptr
				old_children.erase(it); // ��ԭ���ڵ��б��Ƴ���ת������Ȩ��
				break;
			}
		}
	}

	// ����2�����õ�ǰ�ڵ�Ϊ�¸��ڵ�
	obj->set_parent(this);

	// ����3�����ӽڵ�� unique_ptr �ƶ�����ǰ�ڵ�� children �б�
	is_front ? children.push_front(std::move(obj)) : children.push_back(std::move(obj));
}

uqp_obj GameObj::remove_children(GameObj* obj) {
	uqp_obj removedObj; // ���ڽ��ձ��Ƴ����ӽڵ� 

	for (auto it = children.begin(); it != children.end(); ++it) {
		if (it->get() == obj) { // �ҵ���Ӧ�ӽڵ�� unique_ptr
			removedObj = std::move(*it); // ת������Ȩ�� removedObj
			children.erase(it);          // ���б����Ƴ�
			break;
		}
	}

	// ���ɹ��Ƴ����Ͽ����ӹ�ϵ
	if (removedObj) {
		removedObj->set_parent(nullptr);
		removedObj->set_anchor_referent_obj(nullptr);
	}

	return removedObj; // ���÷�����ӽڵ������Ȩ
}

void GameObj::delete_children(GameObj* obj)
{
	for (auto it = children.begin(); it != children.end(); ++it) {
		if (it->get() == obj) { // �ҵ���Ӧ�ӽڵ�� unique_ptr
			// �Ͽ����ӹ�ϵ
			(*it)->set_parent(nullptr);
			(*it)->set_anchor_referent_obj(nullptr);

			children.erase(it); // �Ƴ���unique_ptr ���� �� �Զ� delete obj
			break;
		}
	}
}

bool GameObj::check_in_screen(int val)
{

	GameWnd* wnd = GameWnd::instance();
	if (wnd == nullptr) {
		std::cout << "GameWnd  δ��ʼ����" << std::endl;
		return false;
	}

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

void GameObj::for_each_child(const std::function<void(GameObj*)>& func)
{
	if (!func) return;

	for (const auto& child_ptr : children) {
		if (child_ptr) {
			func(child_ptr.get());
		}
	}
}

void GameObj::sort_children(const std::function<bool(const uqp_obj&, const uqp_obj&)>& func)
{
	if (!func) return;

	children.sort([&func](const uqp_obj& a, const uqp_obj& b) {
		// ����пսڵ㣬�����ں���
		if (!a) return false;
		if (!b) return true;
		// ����������ָ�룬�����ⲿ����ıȽ��߼�
		return func(a, b);
		});
}

void GameObj::remove_children_if(const std::function<bool(const uqp_obj&)>& func)
{
	if (!func) return;

	children.remove_if([&func](const uqp_obj& child) {
		if (!child)
		{
			return true;
		}
		if (func(child)) {
			child->set_parent(nullptr);
			child->set_anchor_referent_obj(nullptr);
			return true;
		}
		return false;
		});
}

void GameObj::clear_children()
{
	children.remove_if([](const uqp_obj& child) {
		if (child)
		{
			child->set_parent(nullptr);
			child->set_anchor_referent_obj(nullptr);
		}
		return true;
		});
}