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

void CollisionMgr::on_input(const SDL_Event& event)
{
	for (TreeNode_SP box : box_list)
	{
		box->on_input(event);
	}
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
	for (TreeNode_SP box_src : box_list)//攻击循环
	{
		if (!is_collider_valid(box_src))
		{
			continue;
		}
		if (auto obj_src = box_src->get_obj_as<GameCollisionBox>())
		{
			if (!obj_src->collision_enabled || obj_src->layer_dst == CollisionLayer::NONE)
			{
				continue;
			}
			for (TreeNode_SP box_dst : box_list)//受击循环
			{
				if (!is_collider_valid(box_dst))
				{
					continue;
				}
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
						event_src.user.data1 = static_cast<void*>(obj_src);
						SDL_PushEvent(&event_src);
						SDL_Event event_dst;
						event_dst.type = EventMgr::instance()->get_event_type(EventType::COLLISION);
						event_dst.user.data1 = static_cast<void*>(obj_dst);
						SDL_PushEvent(&event_dst);
						std::cout << "碰撞发生：  " << event_src.type << "   &   " << event_dst.type << std::endl;
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

void CollisionMgr::clear_all_box()
{
	box_list.clear();
}

void CollisionMgr::clear_invalid()
{
	box_list.erase(std::remove_if(box_list.begin(),
		box_list.end(), [&](TreeNode_SP box) {
			return !is_collider_valid(box);
		}), box_list.end());
}

void CollisionMgr::onDebugRender()
{
	for (TreeNode_SP box : box_list)
	{
		box->on_render();
	}
}

bool CollisionMgr::is_collider_valid(TreeNode_SP box) {
	// 当前仅检测锚定对象是否存在
	auto ref = box->get_anchor_referent();
	return ref != nullptr;
}

CollisionMgr::CollisionMgr() = default;
CollisionMgr::~CollisionMgr() = default;