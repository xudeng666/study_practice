#include "game_bar.h"
#include "res_mgr.h"
#include "game_mgr.h"


GameBar::GameBar(const Vector2 pos):GameObj(pos)
{
	anchor_mode = AnchorMode::TOPLEFT;
	img_bg = new GameImg(pos);
	img_pro = new GameImg(pos);
}

void GameBar::on_enter()
{
	point_num = init_point;
	img_bg->set_anchor_mode(anchor_mode);
	img_pro->set_anchor_mode(anchor_mode);
}

void GameBar::on_update(float delta)
{
}

void GameBar::on_render()
{
	if (img_bg)
	{
		img_bg->on_render();
	}
	if (img_pro)
	{
		SDL_Texture* pro_t = img_pro->get_texture();
		SDL_Point s = img_pro->get_size();
		SDL_Rect src = { 0,0,s.x,s.y };
		SDL_FRect dst = img_pro->get_FRect();
		if (is_point)
		{
			for (size_t i = 0; i < point_num; i++)
			{
				GameMgr::instance()->get_camera()->render_texture(pro_t, &src, &dst, angle, &center);
				dst.x += dst.w;
			}
		}
		else
		{
			dst.w *= percent_num;
			GameMgr::instance()->get_camera()->render_texture(pro_t, &src, &dst, angle, &center);
		}
	}
}

void GameBar::set_img_bg_texture(const std::string name)
{
	img_bg->set_res_name(name);
	img_bg->on_enter();
}

void GameBar::set_img_pro_texture(const std::string name)
{
	img_pro->set_res_name(name);
	img_pro->on_enter();
}

void GameBar::set_point_num(int num)
{
	point_num = num;
}

void GameBar::set_init_point(int num)
{
	init_point = num;
}

void GameBar::set_percent_num(float num)
{
	if (num < 0 || num > 1) return;
	percent_num = num;
}

void GameBar::set_is_point(bool point)
{
	is_point = point;
}