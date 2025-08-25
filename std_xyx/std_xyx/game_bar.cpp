#include "game_bar.h"
#include "res_mgr.h"
#include "game_mgr.h"


GameBar::GameBar(const Vector2 pos):GameObj(pos)
{
	img_bg = new GameImg({0,0});
	img_bg->set_anchor_mode(AnchorMode::LEFTCENTER);
	img_bg->set_parent_anchor_mode(AnchorMode::LEFTCENTER);

	img_pro = new GameImg({ 0,0 });
	img_pro->set_anchor_mode(AnchorMode::LEFTCENTER);
	img_pro->set_parent_anchor_mode(AnchorMode::LEFTCENTER);

	add_children(img_bg);
	add_children(img_pro);
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
	s.x = int(percent_num * max_value);
	img_pro->set_size(s);
}

void GameBar::set_max_value(float num)
{
	max_value = num;
}