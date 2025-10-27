#include "bullet_box.h"
#include "event_mgr.h"

#include <assert.h>

INIT_TYPE_NAME(BulletBox);

void BulletBox::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID << "  on_enter" << std::endl;
	}
	GameObj::on_enter();
	enable_angle = true;
	bul_num = 0;
	bul_degrees = 0;
}

void BulletBox::on_exit()
{
	GameObj::on_exit();
	clear_children();
}

void BulletBox::on_input(const SDL_Event& event)
{
	if (event.type == EventMgr::instance()->get_event_type(EventType::ADD_BULLET))
	{
		add_bullet(1);
	}
	else if (event.type == EventMgr::instance()->get_event_type(EventType::REDUCE_BULLET))
	{
		reduce_bullet(1);
	}
}

void BulletBox::on_update(float delta)
{
	GameObj::on_update(delta);
	move_bullet(delta);
}

void BulletBox::add_bullet(const int num)
{
	std::cout << "BulletBox::添加子弹" << std::endl;
	for (size_t i = 0; i < num; i++)
	{
		bul_num++;
		if (bul_num > children.size())
		{
			auto p = TreeNode::create_obj<BulletXcz>("bul_", bul_num - 1);
			p->set_anchor_referent_node(self_node);
			p->on_enter();
			p->set_on_hit_fun([&]() {
				if (on_hit_fun)
				{
					on_hit_fun();
				}
				});
			p->set_anchor_mode(AnchorMode::CENTER);
			p->set_anchor_referent_mode(AnchorMode::CENTER);
			p->set_position(Vector2(0, -bul_radius));
			add_children(std::move(p));
		}
		else
		{
			auto p = children[bul_num - 1];
			p->on_enter();
		}
	}
}
void BulletBox::reduce_bullet(int num)
{
	std::cout << "BulletBox::减少子弹" << std::endl;
	bul_num -= num;
	while (num > 0)
	{
		num--;
		auto p = children[bul_num + num];
		p->on_exit();
	}
}

int BulletBox::get_bullet_num()
{
	return bul_num;
}

void BulletBox::set_bullet_num(const int num)
{
	bul_num = num;
}

void BulletBox::move_bullet(float delta)
{
	if (children.size() < bul_num)
	{
		assert(false && "未知原因子弹数据错误");
	}

	angle += delta * angle_speed;

	for (int i = 0; i < bul_num; ++i)
	{
		auto p = children[i];
		if (p)
		{
			p->set_rotation(angle);
		}
	}

	/*bul_degrees += delta * angle_speed;
	float angle = bul_num == 0 ? 0 : 360 / bul_num;
	for (int i = 0; i < bul_num; ++i)
	{
		int dre = bul_degrees + angle * i;
		dre %= 360;
		auto p = children[i];
		if (p)
		{
			p->set_position({ (float)cos(dre * _PI_ / 180) * bul_radius, -(float)(sin(dre * _PI_ / 180) * bul_radius) });
			p->set_rotation(90 - dre);
		}
	}*/
}

void BulletBox::set_hit_fun(std::function<void()> call_back)
{
	if (call_back)
	{
		on_hit_fun = call_back;
	}
}