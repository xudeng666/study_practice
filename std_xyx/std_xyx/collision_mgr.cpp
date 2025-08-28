#include "collision_mgr.h"
#include "game_wnd.h"


CollisionMgr* CollisionMgr::manager = nullptr;

CollisionMgr* CollisionMgr::instance()
{
	if (!manager)
	{
		manager = new CollisionMgr();
	}
	return manager;
}

GameCollisionBox* CollisionMgr::creatCollisionBox()
{
	GameCollisionBox* box = new GameCollisionBox();
	box_list.push_back(box);
	return box;
}

void CollisionMgr::destroyCollisionBox(GameCollisionBox* box)
{
	box_list.erase(std::remove(box_list.begin(),
		box_list.end(), box), box_list.end());
	delete box;
}

void CollisionMgr::processCollide()
{
	for (GameCollisionBox* box_src : box_list)//¹¥»÷Ñ­»·
	{
		if (!box_src->collision_enabled || box_src->layer_dst == CollisionLayer::NONE)
		{
			continue;
		}
		for (GameCollisionBox* box_dst : box_list)//ÊÜ»÷Ñ­»·
		{
			if (!box_dst->collision_enabled || box_dst == box_src || box_dst->layer_src != box_src->layer_dst)
			{
				continue;
			}

			if (is_collision(box_src, box_dst) && box_dst->call_back)
			{
				box_dst->call_back();
			}
		}
	}
}

bool CollisionMgr::is_collision(GameCollisionBox* box_t, GameCollisionBox* box_p)
{
	SDL_FRect rect_t = box_t->get_FRect();
	SDL_FRect rect_p = box_p->get_FRect();
	return SDL_HasIntersectionF(&rect_t, &rect_p);
}

void CollisionMgr::onDebugRender()
{
	for (GameCollisionBox* box : box_list)
	{
		box->on_render();
	}
}

CollisionMgr::CollisionMgr() = default;
CollisionMgr::~CollisionMgr() = default;