#pragma once

#include "game.h"
#include "res_mgr.h"

#include <assert.h>

INIT_TYPE_NAME(Game);

Game::Game(const std::string& id)
{
	set_ID(id);
}

Game::Game(const std::string& id, const int num)
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
	create_target_scene();
	get_current_scene()->on_enter();
}

void Game::on_update(float delta)
{
	get_current_scene()->do_update(delta);
}

void Game::on_input(const SDL_Event& event)
{
	get_current_scene()->do_input(event);
}

void Game::on_render()
{
	get_current_scene()->on_render();
}

void Game::on_exit()
{
	destroy_current_scene();
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
	destroy_current_scene();

	current_scene_type = type;
	// 创建新场景
	create_target_scene(); 
	// 激活新场景
	auto new_scene = get_current_scene();
	if (new_scene) {
		new_scene->on_enter();
	}
	else {
		assert(false && "创建目标场景失败，scene_pool 中无对应场景");
	}
}

void Game::destroy_current_scene()
{
	auto scene = get_current_scene();
	if (!scene) {
		return; // 无当前场景，无需销毁
	}
	scene->do_exit();
	scene_pool.erase(current_scene_type);
}

void Game::create_target_scene()
{
	// 由子类重写，基类不做约束
}

void Game::set_ID(const std::string& str)
{
	ID = str;
}

void Game::set_ID(const std::string& str, const int num)
{
	ID = str + std::to_string(num);
}

std::string Game::get_ID()
{
	return ID;
}