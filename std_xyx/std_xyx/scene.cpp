#include "scene.h"
#include "tree_mgr.h"
#include "collision_mgr.h"

#include <iostream>

INIT_TYPE_NAME(Scene);

Scene::Scene(const std::string id)
{
	set_ID(id);
}

Scene::Scene(const std::string id, const int num)
{
	set_ID(id, num);
}

void Scene::on_enter()
{
	std::cout << get_ID() << "    Scene::on_enter()" << std::endl;
	TreeMgr::instance()->pre_order_traversal([&](TreeNode_SP node) {
		if (node)
		{
			node->on_enter();
		}
		});
}

void Scene::do_update(float delta)
{
	TreeMgr::instance()->pre_order_traversal([&](TreeNode_SP node) {
		if (node)
		{
			node->on_update(delta);
		}
		});
	on_update(delta);
	CollisionMgr::instance()->clear_invalid();
}

void Scene::on_update(float delta)
{
}

void Scene::on_input(const SDL_Event& event)
{
	TreeMgr::instance()->pre_order_traversal([&](TreeNode_SP node) {
		if (node)
		{
			node->on_input(event);
		}
		});
	CollisionMgr::instance()->on_input(event);
}

void Scene::on_render()
{
	TreeMgr::instance()->pre_order_traversal([&](TreeNode_SP node) {
		if (node)
		{
			node->on_render();
		}
		});
}

void Scene::on_exit()
{
	CollisionMgr::instance()->clear_all_box();
	TreeMgr::instance()->release_all_game();
}

void Scene::set_ID(const std::string& str)
{
	ID = str;
}

void Scene::set_ID(const std::string& str, const int num)
{
	ID = str + std::to_string(num);
}

std::string Scene::get_ID()
{
	return ID;
}