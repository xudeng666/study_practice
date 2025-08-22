#include "game_img.h"
#include "res_mgr.h"
#include "game_mgr.h"

GameImg::GameImg(const Vector2 pos) :GameObj(pos) {}

GameImg::GameImg(const Vector2 pos, const std::string name) :GameObj(pos)
{
	res_name = name;
}

void GameImg::on_enter()
{
	set_texture();
	set_size();
}

void GameImg::on_update(float delta)
{
}

void GameImg::on_render()
{
	SDL_Rect src = { 0,0,size.x,size.y };
	SDL_FRect dst = get_FRect();
	GameMgr::instance()->get_camera()->render_texture(texture, &src, &dst, angle, &center);
}

void GameImg::set_size()
{
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
}

void GameImg::set_size(const SDL_Point& size)
{
	this->size = size;
}

void GameImg::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name);
}

SDL_Texture* GameImg::get_texture()
{
	return texture;
}

void GameImg::set_res_name(const std::string name)
{
	res_name = name;
}