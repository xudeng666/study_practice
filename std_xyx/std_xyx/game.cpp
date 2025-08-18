#pragma once

#include "game.h"
#include "res_mgr.h"

Game::Game()
{
	ResMgr::instance()->load();
}

Game::~Game()
{
	// 释放场景列表
	for (auto& [name, scene] : scene_pool) {
		delete scene;
	}
	scene_pool.clear();
}

void Game::on_enter()
{
	get_current_scene()->on_enter();
}

void Game::on_update(int delta)
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

Scene* Game::get_current_scene()
{
	return scene_pool[current_scene_type];
}