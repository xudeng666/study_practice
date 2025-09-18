#pragma once

#include "game.h"
#include "res_mgr.h"


Game::Game(const std::string id)
{
	set_ID(id);
}

Game::Game(const std::string id, const int num)
{
	set_ID(id, num);
}

Game::~Game()
{
	scene_pool.clear();
}

void Game::on_enter()
{
	ResMgr::instance()->load();
	get_current_scene()->on_enter();
}

void Game::on_update(float delta)
{
	get_current_scene()->on_update(delta);
}

void Game::on_input(const SDL_Event& event)
{
	get_current_scene()->on_input(event);
}

void Game::on_render()
{
	get_current_scene()->on_render();
}

void Game::on_exit()
{
	get_current_scene()->on_exit();
	ResMgr::instance()->releaseAll();
}

std::shared_ptr<Scene> Game::get_current_scene()
{
	return scene_pool[current_scene_type];
}

void Game::exchange_scene(SceneType type)
{
	if (type == current_scene_type) return;
	// 退出当前场景
	get_current_scene()->on_exit();

	current_scene_type = type;

	get_current_scene()->on_enter();
}

void Game::set_ID(const std::string str)
{
	ID = str;
}

void Game::set_ID(const std::string str, const int num)
{
	ID = str + std::to_string(num);
}

std::string Game::get_ID()
{
	return ID;
}