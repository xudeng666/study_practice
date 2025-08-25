#include "game_img.h"
#include "res_mgr.h"
#include "game_mgr.h"

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
		int len_y = size.y / s.y;
		int len_x = size.x / s.x;
		for (int y = 0; y <= len_y; y++)
		{
			dst.y = y * size.y;
			int wy = s.y - dst.y;
			src.h = wy < size.y ? wy : size.y;
			for (int x = 0; x <= len_x; x++)
			{
				dst.x = x * size.x;
				int wx = s.x - dst.x;
				src.w = wx < size.x ? wx : size.x;

				dst.w = (float)src.w;
				dst.h = (float)src.h;

				GameMgr::instance()->get_camera()->render_texture(texture, &src, &dst, angle, &center);
			}
		}
	}
	else
	{
		src = { 0,0,size.x,size.y };
		dst = { p.x,p.y,(float)size.x,(float)size.y };
		GameMgr::instance()->get_camera()->render_texture(texture, &src, &dst, angle, &center);
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
	this->size = size;
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