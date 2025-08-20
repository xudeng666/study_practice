#include "game_img.h"
#include "res_mgr.h"
#include "game_mgr.h"

GameImg::GameImg(const Vector2 pos) :GameObj(pos) {}

GameImg::GameImg(const Vector2 pos, const std::string name) :GameObj(pos)
{
	texture = ResMgr::instance()->find_texture(name);
}

void GameImg::on_update(float delta)
{

}

void GameImg::on_render()
{
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);

	SDL_Rect src = { 0, 0, size.x, size.y };
	SDL_FRect t_dst = { position.x, position.y, (float)size.x, (float)size.y };
	SDL_FRect dst = get_dst_rect(t_dst, anchor_mode);

	GameMgr::instance()->get_camera()->render_texture(texture, position, size, anchor_mode, angle, &center);
}