#include "scene.h"
#include <iostream>

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
}

void Scene::on_update(float delta)
{
}

void Scene::on_input(const SDL_Event& event)
{
}

void Scene::on_render()
{
}

void Scene::on_exit()
{
}

void Scene::set_ID(const std::string str)
{
	ID = str;
}

void Scene::set_ID(const std::string str, const int num)
{
	ID = str + std::to_string(num);
}

std::string Scene::get_ID()
{
	return ID;
}