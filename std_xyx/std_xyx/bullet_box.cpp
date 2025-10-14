#include "bullet_box.h"


void BulletBox::on_enter()
{
	if (_DE_BUG_)
	{
		std::cout << ID << "  on_enter" << std::endl;
	}
	GameObj::on_enter();
}

void BulletBox::on_exit()
{
	GameObj::on_exit();
}

void BulletBox::on_input(const SDL_Event& event)
{
	// 主要接受添加和减少子弹的事件。
	switch (event.type)
	{
	default:
		break;
	}
}

void BulletBox::on_update(float delta)
{
	GameObj::on_update(delta);
	move_bullet(delta);
}

void BulletBox::add_bullet(const int num)
{
	for (size_t i = 0; i < num; i++)
	{
		bul_num++;
		if (bul_num > children.size())
		{
			auto p = TreeNode::create_obj<BulletXcz>("bul_", bul_num - 1);
			p->set_anchor_referent_node(self_node);
			p->on_enter();
			p->set_on_hit_fun([&]() {
				//on_hit();
				});
			add_children(std::move(p));
			children.push_back(p);
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
	while (num > 0)
	{
		num--;
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
	if (children.size() < bul_num) return;
	bul_degrees += delta * angle_speed;
	float angle = 360 / bul_num;
	for (int i = 0; i < bul_num; ++i)
	{
		int dre = bul_degrees + angle * i;
		dre %= 360;
		//std::cout << "bullet dre:   " << dre << std::endl;
		auto p = children[i];
		if (p)
		{
			p->set_position({ (float)cos(dre * _PI_ / 180) * bul_radius, -(float)(sin(dre * _PI_ / 180) * bul_radius) });
			p->set_rotation(90 - dre);
		}
	}
}