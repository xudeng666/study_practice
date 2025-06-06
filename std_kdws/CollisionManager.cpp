#include "CollisionManager.h"


CollisionManager* CollisionManager::manager = nullptr;

CollisionManager* CollisionManager::instance()
{
	if (!manager)
	{
		manager = new CollisionManager();
	}
	return manager;
}

CollisionBox* CollisionManager::creatCollisionBox()
{
	CollisionBox* box = new CollisionBox();
	box_list.push_back(box);
	return box;
}

void CollisionManager::destroyCollisionBox(CollisionBox* box)
{
	box_list.erase(std::remove(box_list.begin(), 
		box_list.end(), box),box_list.end());
	delete box;
}

void CollisionManager::processCollide()
{
	for (CollisionBox* box_src : box_list)//¹¥»÷Ñ­»·
	{
		if (!box_src->enabled || box_src->layer_dst == CollisionLayer::None)
		{
			continue;
		}
		for (CollisionBox* box_dst : box_list)//ÊÜ»÷Ñ­»·
		{
			if (!box_dst->enabled || box_dst == box_src || box_dst->layer_src != box_src->layer_dst)
			{
				continue;
			}

			bool is_collision = checkRectToRect(
				box_src->position.x - box_src->size.x/2, box_src->position.x + box_src->size.x/2, 
				box_src->position.y - box_src->size.y/2, box_src->position.y + box_src->size.y/2,
				box_dst->position.x - box_dst->size.x/2, box_dst->position.x + box_dst->size.x/2, 
				box_dst->position.y - box_dst->size.y/2, box_dst->position.y + box_dst->size.y/2
			);
			if (is_collision && box_dst->call_back)
			{
				box_dst->call_back();
			}
		}
	}
}
void CollisionManager::onDebugRender()
{
	for (CollisionBox* box : box_list)
	{
		setlinecolor(box->enabled ? RGB(255, 195, 195) : RGB(115, 115, 175));
		rectangle(
			box->position.x - box->size.x / 2, 
			box->position.y - box->size.y / 2, 
			box->position.x + box->size.x / 2,
			box->position.y + box->size.y / 2
		);
	}
}

std::vector<CollisionBox*> box_list;
CollisionManager::CollisionManager() = default;
CollisionManager::~CollisionManager() = default;