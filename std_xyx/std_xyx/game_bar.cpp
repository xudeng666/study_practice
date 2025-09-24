#include "game_bar.h"

#include <assert.h>

void GameBar::on_init()
{
	auto bg = TreeNode::create_obj<GameImg>("img_bg");
	bg->set_position(Vector2(0, 0));
	bg->set_anchor_mode(AnchorMode::LEFTCENTER);
	bg->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	auto pro = TreeNode::create_obj<GameImg>("img_pro");
	pro->set_position(Vector2(0, 0));
	pro->set_anchor_mode(AnchorMode::LEFTCENTER);
	pro->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	img_bg = bg;
	img_pro = pro;

	add_children(std::move(bg));
	add_children(std::move(pro));
}

void GameBar::on_enter()
{
	GameObj::on_enter();
}

void GameBar::on_update(float delta)
{
	GameObj::on_update(delta);
}

void GameBar::on_render()
{
	GameObj::on_render();
}

void GameBar::set_size(const SDL_Point& size)
{
	img_bg.lock()->set_size(size);
	img_pro.lock()->set_size(size);
	this->size = size;
}

TreeNode_SP GameBar::get_img_bg()
{
	return img_bg.lock();
}

TreeNode_SP GameBar::get_img_pro()
{
	return img_pro.lock();
}

void GameBar::set_percent_num(float num)
{
	if (num < 0 || num > 1) return;
	percent_num = num;
	auto pro = img_pro.lock();

	assert(pro && "此处不能为假！");

	SDL_Point s = pro->get_size();
	if (is_horizontal)
	{
		s.x = int(percent_num * max_value.x);
	}
	else
	{
		s.y = int(percent_num * max_value.y);
	}
	pro->set_size(s);
}

void GameBar::set_max_value(const SDL_Point& value)
{
	max_value = value;
}

void GameBar::set_is_horizontal(bool is_h)
{
	is_horizontal = is_h;
}