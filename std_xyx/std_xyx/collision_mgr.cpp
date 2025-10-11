#include "collision_mgr.h"
#include "event_mgr.h"

#include <memory>


CollisionMgr* CollisionMgr::manager = nullptr;

CollisionMgr* CollisionMgr::instance()
{
	if (!manager)
	{
		manager = new CollisionMgr();
	}
	return manager;
}

TreeNode_SP CollisionMgr::creatCollisionBox(std::string id)
{
	auto node = TreeNode::create_obj<GameCollisionBox>(id);
	box_list.push_back(node);
	return node;
}

TreeNode_SP CollisionMgr::creatCollisionBox(std::string id, int num)
{
	auto node = TreeNode::create_obj<GameCollisionBox>(id, num);
	box_list.push_back(node);
	return node;
}

void CollisionMgr::destroyCollisionBox(TreeNode_SP box)
{
	box_list.erase(std::remove(box_list.begin(),
		box_list.end(), box), box_list.end());
}

void CollisionMgr::destroy()
{
	box_list.clear();
	delete manager;
	manager = nullptr;
}

void CollisionMgr::processCollide()
{
	for (TreeNode_SP box_src : box_list)//¹¥»÷Ñ­»·
	{
		if (auto obj_src = box_src->get_obj_as<GameCollisionBox>())
		{
			if (!obj_src->collision_enabled || obj_src->layer_dst == CollisionLayer::NONE)
			{
				continue;
			}
			for (TreeNode_SP box_dst : box_list)//ÊÜ»÷Ñ­»·
			{
				if (auto obj_dst = box_dst->get_obj_as<GameCollisionBox>())
				{
					if (!obj_dst->collision_enabled || box_dst == box_src || obj_dst->layer_src != obj_src->layer_dst)
					{
						continue;
					}

					if (is_collision(box_src, box_dst))
					{
						SDL_Event event_src;
						event_src.type = EventMgr::instance()->get_event_type(EventType::COLLISION);
						event_src.user.data1 = static_cast<void*>(obj_dst);
						SDL_PushEvent(&event_src);
						SDL_Event event_dst;
						event_dst.type = EventMgr::instance()->get_event_type(EventType::COLLISION);
						event_dst.user.data1 = static_cast<void*>(obj_dst);
						SDL_PushEvent(&event_dst);
					}
				}
			}
		}
	}
}

bool CollisionMgr::is_collision(TreeNode_SP box_t, TreeNode_SP box_p)
{
	SDL_FRect rect_t = box_t->get_FRect();
	SDL_FRect rect_p = box_p->get_FRect();
	return SDL_HasIntersectionF(&rect_t, &rect_p);
}

void CollisionMgr::onDebugRender()
{
	for (TreeNode_SP box : box_list)
	{
		box->on_render();
	}
}

CollisionMgr::CollisionMgr() = default;
CollisionMgr::~CollisionMgr() = default;