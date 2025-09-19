#include "game_bar.h"

#include <assert.h>

void GameBar::on_init()
{
	auto bg = TreeNode::create(std::make_unique<GameImg>("img_bg"));
	bg->get_obj()->set_position(Vector2(0, 0));
	bg->get_obj()->set_anchor_mode(AnchorMode::LEFTCENTER);
	bg->get_obj()->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	auto pro = TreeNode::create(std::make_unique<GameImg>("img_pro"));
	pro->get_obj()->set_position(Vector2(0, 0));
	pro->get_obj()->set_anchor_mode(AnchorMode::LEFTCENTER);
	pro->get_obj()->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	img_bg = bg;
	img_pro = pro;

	auto self = self_node.lock();
	self->add_children(std::move(bg));
	self->add_children(std::move(pro));
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

	SDL_Point s = pro->get_obj()->get_size();
	if (is_horizontal)
	{
		s.x = int(percent_num * max_value.x);
	}
	else
	{
		s.y = int(percent_num * max_value.y);
	}
	pro->get_obj()->set_size(s);
}

void GameBar::set_max_value(SDL_Point value)
{
	max_value = value;
}

void GameBar::set_is_horizontal(bool is_h)
{
	is_horizontal = is_h;
}