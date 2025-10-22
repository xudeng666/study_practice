#include "game_collision_box.h"
#include "event_mgr.h"

INIT_TYPE_NAME(GameCollisionBox);

void GameCollisionBox::on_init()
{
}

void GameCollisionBox::on_input(const SDL_Event& event)
{
	const EventTypeId type = EventMgr::instance()->get_event_type(EventType::COLLISION);

	if (type == event.type)
	{
		EventData* data = static_cast<EventData*>(event.user.data1);
		if (!data) return;
		std::string id;
		if (data->get("id", id))
		{
			std::cout << "Åö×²»Øµ÷£º  " << id << "   &   " << get_ID() << std::endl;
			if (id == get_ID() && call_back)
			{
				call_back();
			}
		}
		delete data;
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