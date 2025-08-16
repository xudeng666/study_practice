#pragma once

#include "game.h"
#include "res_mgr.h"

void Game::on_load()
{
	ResMgr::instance()->load();
}

void Game::on_enter()
{
	on_load();
	on_scene_init();
	current_scene->on_enter();
}

void Game::on_update(int delta)
{
	current_scene->on_update(delta);
}

void Game::on_input(const SDL_Event& event)
{
	current_scene->on_input(event);
}

void Game::on_render()
{
	current_scene->on_render();
}

void Game::on_exit()
{
	current_scene->on_exit();
	ResMgr::instance()->releaseAll();
}

void Game::set_current_scene(Scene* scene)
{
	current_scene = scene;
}

Scene* Game::get_current_scene()
{
	return current_scene;
}