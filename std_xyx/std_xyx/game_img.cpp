#include "game_img.h"
#include "game_wnd.h"
#include "res_mgr.h"

INIT_TYPE_NAME(GameImg);

GameImg::~GameImg() 
{
	texture = nullptr;
}

void GameImg::on_enter()
{
	GameObj::on_enter();
	set_texture();
	//init_size();
}

void GameImg::on_update(float delta)
{
	GameObj::on_update(delta);
}

void GameImg::on_render()
{
	if (texture)
	{
		SDL_Rect src = { 0,0,0,0 };
		SDL_FRect dst = get_FRect();
		Vector2 p = {dst.x, dst.y};
		Vector2 t_s = { dst.w, dst.h };

		SDL_FPoint center_r = get_center_point();

		if (map_type == TextureMapType::TILE)
		{
			SDL_Point s;
			SDL_QueryTexture(texture, nullptr, nullptr, &s.x, &s.y);
			int len_h = t_s.y / s.y;
			int len_w = t_s.x / s.x;

			for (int i = 0; i <= len_h; i++)
			{
				dst.y = i * s.y;
				int wy = t_s.y - dst.y;
				src.h = wy < s.y ? wy : s.y;
				dst.y += p.y;
				for (int j = 0; j <= len_w; j++)
				{
					dst.x = j * s.x;
					int wx = t_s.x - dst.x;
					src.w = wx < s.x ? wx : s.x;

					dst.x += p.x;
					dst.w = src.w;
					dst.h = src.h;

					GameWnd::instance()->render_texture(texture, &src, &dst, get_angle(), &center_r);
				}
			}
		}
		else
		{
			src = { 0,0,(int)t_s.x,(int)t_s.y };
			GameWnd::instance()->render_texture(texture, &src, &dst, get_angle(), &center_r);
		}
	}
	GameObj::on_render();
}

const SDL_Point& GameImg::get_size() const
{
	if (map_type == TextureMapType::AUTO)
	{
		if (texture)
		{
			SDL_Point s;
			SDL_QueryTexture(texture, nullptr, nullptr, &s.x, &s.y);
			return s;
		}
	}
	return size;
}
//
//void GameImg::init_size()
//{
//	if (map_type == TextureMapType::AUTO)
//	{
//		if (texture)
//		{
//			SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
//		}
//	}
//}

void GameImg::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name);
	if (!texture)
	{
		std::cout << ID << " texture null"<< "   res_name:"<< res_name << std::endl;
	}
}

SDL_Texture* GameImg::get_texture()
{
	if (!texture)
	{
		set_texture();
	}
	return texture;
}

void GameImg::set_texture_map_type(TextureMapType type)
{
	map_type = type;
}

TextureMapType GameImg::get_texture_map_type()
{
	return map_type;
}

void GameImg::set_res_name(const std::string name)
{
	res_name = name;
	set_texture();
	//init_size();
}