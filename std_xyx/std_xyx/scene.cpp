#include "scene.h"
#include <iostream>

Scene::Scene(const std::string id)
{
	set_ID(id);
	on_init();
}

Scene::Scene(const std::string id, const int num)
{
	set_ID(id, num);
	on_init();
}

void Scene::on_init()
{
}

void Scene::on_enter()
{
	std::cout << get_ID() << "    Scene::on_enter()" << std::endl;
	// 需要添加节点遍历代码
}

void Scene::on_update(float delta)
{
	// 需要添加节点遍历代码
}

void Scene::on_input(const SDL_Event& event)
{
	// 需要添加节点遍历代码
}

void Scene::on_render()
{
	// 需要添加节点遍历代码
}

void Scene::on_exit()
{
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