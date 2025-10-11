#include "game_collision_box.h"
#include "event_mgr.h"

INIT_TYPE_NAME(GameCollisionBox);

void GameCollisionBox::on_init()
{
}

void GameCollisionBox::on_input(const SDL_Event& event)
{
	const Uint32 type = EventMgr::instance()->get_event_type(EventType::COLLISION);

	if (type == event.type && event.user.data1 == this)
	{
		if (call_back)
		{
			call_back();
		}
	}
}

void GameCollisionBox::on_update(float delta)
{
	if (!collision_enabled)
	{
		return;
	}
	GameObj::on_update(delta);
}

void GameCollisionBox::on_render()
{
	if (!collision_enabled)
	{
		return;
	}
	GameObj::on_render();
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