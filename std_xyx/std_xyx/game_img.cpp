#include "game_img.h"
#include "res_mgr.h"

GameImg::GameImg(const Vector2 pos) :GameObj(pos) {}

GameImg::GameImg(const Vector2 pos, const std::string name) :GameObj(pos)
{
	texture = ResMgr::instance()->find_texture(name);
}

void GameImg::on_update(float delta)
{

}

void GameImg::on_render(const Camera* camera)
{
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);

	SDL_Rect src = { 0, 0, size.x, size.y };
	SDL_FRect t_dst = { position.x, position.y, size.x, size.y };
	SDL_FRect dst = get_dst_rect(t_dst, anchor_mode);

	camera->render_texture(texture, &src, &dst, angle, &center);
}