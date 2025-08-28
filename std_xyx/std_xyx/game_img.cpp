#include "game_img.h"
#include "game_wnd.h"
#include "res_mgr.h"

GameImg::GameImg(const Vector2 pos) :GameObj(pos)
{
	size = { 100,100 };
}

GameImg::GameImg(const Vector2 pos, const std::string name) :GameObj(pos)
{
	res_name = name;
	size = { 100,100 };
}

void GameImg::on_enter()
{
	GameObj::on_enter();
	set_texture();
	set_size();
}

void GameImg::on_update(float delta)
{
	GameObj::on_update(delta);
}

void GameImg::on_render()
{
	if (!texture) return;

	SDL_Rect src = { 0,0,0,0 };
	SDL_FRect dst = { 0,0,0,0 };
	Vector2 p = get_anchor_position(AnchorMode::TOPLEFT);

	if (map_type == TextureMapType::TILE)
	{
		SDL_Point s;
		SDL_QueryTexture(texture, nullptr, nullptr, &s.x, &s.y);
		int len_h = size.y / s.y;
		int len_w = size.x / s.x;

		/*if (_DE_BUG_)
		{
			std::cout << "len_w:	" << len_w << std::endl
				<< "len_h:	" << len_h << std::endl;
		}*/

		for (int i = 0; i <= len_h; i++)
		{
			dst.y = i * s.y;
			int wy = size.y - dst.y;
			src.h = wy < s.y ? wy : s.y;
			dst.y += p.y;
			for (int j = 0; j <= len_w; j++)
			{
				dst.x = j * s.x;
				int wx = size.x - dst.x;
				src.w = wx < s.x ? wx : s.x;

				dst.x += p.x;
				dst.w = src.w;
				dst.h = src.h;

				//if (_DE_BUG_)
				//{
				//	std::cout << "dst.x:	" << dst.x << std::endl
				//		<< "dst.y:	" << dst.y << std::endl
				//		<< "dst.w:	" << dst.w << std::endl
				//		<< "dst.h:	" << dst.h << std::endl<< std::endl;
				//}
				GameWnd::instance()->get_camera()->render_texture(texture, &src, &dst, angle, &center);
			}
		}
	}
	else
	{
		src = { 0,0,size.x,size.y };
		dst = { p.x,p.y,(float)size.x,(float)size.y };
		GameWnd::instance()->get_camera()->render_texture(texture, &src, &dst, angle, &center);
	}

	GameObj::on_render();
}

void GameImg::set_size()
{
	if (map_type == TextureMapType::AUTO && texture)
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	}
}

void GameImg::set_size(const SDL_Point& size)
{
	GameObj::set_size(size);
}

void GameImg::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name);
	if (!texture)
	{
		std::cout << ID << " texture null" << std::endl;
	}
}

SDL_Texture* GameImg::get_texture()
{
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
}