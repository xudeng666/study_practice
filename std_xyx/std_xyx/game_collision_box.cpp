#include "game_collision_box.h"
#include "game_mgr.h"


void GameCollisionBox::on_update(float delta)
{
}

void GameCollisionBox::on_render()
{
	GameMgr::instance()->get_camera()->render_line_rect(position, size, AnchorMode::CENTER);
}

void GameCollisionBox::set_collision_enabled(bool flag)
{
	collision_enabled = flag;
}

void GameCollisionBox::set_layer_src(CollisionLayer layer)
{
	layer_src = layer;
}

void GameCollisionBox::set_layer_dst(CollisionLayer layer)
{
	layer_dst = layer;
}

void GameCollisionBox::set_call_back(std::function<void()> call_back)
{
	this->call_back = call_back;
}