#include "game_bar.h"


GameBar::GameBar(const Vector2 pos):GameObj(pos)
{

	auto img_bg_prt = std::make_unique<GameImg>(Vector2(0, 0));
	img_bg = img_bg_prt.get();
	img_bg->set_ID("img_bg");
	img_bg->set_anchor_mode(AnchorMode::LEFTCENTER);
	img_bg->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	auto img_pro_prt = std::make_unique<GameImg>(Vector2(0, 0));
	img_pro = img_pro_prt.get();
	img_pro->set_ID("img_pro");
	img_pro->set_anchor_mode(AnchorMode::LEFTCENTER);
	img_pro->set_anchor_referent_mode(AnchorMode::LEFTCENTER);

	add_children(std::move(img_bg_prt));
	add_children(std::move(img_pro_prt));
}

GameBar::~GameBar()
{
	GameObj::~GameObj();
	img_bg = nullptr;
	img_pro = nullptr;
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

GameImg* GameBar::get_img_bg()
{
	return img_bg;
}

GameImg* GameBar::get_img_pro()
{
	return img_pro;
}

void GameBar::set_percent_num(float num)
{
	if (num < 0 || num > 1) return;
	percent_num = num;
	SDL_Point s = img_pro->get_size();
	if (is_horizontal)
	{
		s.x = int(percent_num * max_value.x);
	}
	else
	{
		s.y = int(percent_num * max_value.y);
	}
	img_pro->set_size(s);
}

void GameBar::set_max_value(SDL_Point value)
{
	max_value = value;
}

void GameBar::set_is_horizontal(bool is_h)
{
	is_horizontal = is_h;
}