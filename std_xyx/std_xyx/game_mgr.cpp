#include "game_mgr.h"
#include "game_start.h"
#include "game_xcz.h"

//#include <iostream>

GameMgr* GameMgr::manager = nullptr;

GameMgr* GameMgr::instance()
{
	if (!manager)
	{
		manager = new GameMgr();
	}
	return manager;
}

void GameMgr::init()
{
	game_pool[GameType::START] = new GameStart();
	game_pool[GameType::XCZ] = new GameXcz();
	/*game_pool[GameType::KDWS] = new GameStart();
	game_pool[GameType::DLD] = new GameStart();
	game_pool[GameType::ZMDJ] = new GameStart();
	game_pool[GameType::PHF] = new GameStart();*/

	current_type = GameType::START;

	on_enter();
}

void GameMgr::deinit()
{
	// 释放游戏列表
	for (auto& [name, game] : game_pool) {
		delete game;
	}
	game_pool.clear();
}

Game* GameMgr::get_current_game()
{
	return game_pool[current_type];
}

GameType GameMgr::get_current_type()
{
	return current_type;
}

/*游戏切换*/
void GameMgr::exchange_game(GameType type)
{
	if (type == current_type) return;
	// 只允许从开始游戏和子游戏互相切换
	if (type != GameType::START && current_type != GameType::START)
	{
		return;
	}
	// 退出当前游戏
	get_current_game()->on_exit();

	current_type = type;

	get_current_game()->on_enter();
}

/*场景切换*/
void GameMgr::exchange_scene(SceneType type)
{
	get_current_game()->exchange_scene(type);
}

/*游戏初始化*/
void GameMgr::on_enter()
{
	get_current_game()->on_enter();
}

/*处理数据*/
void GameMgr::on_update(float delta)
{
	get_current_game()->on_update(delta);
}
/*用于渲染绘图*/
void GameMgr::on_render()
{
	get_current_game()->on_render();
}
/*处理玩家输入*/
void GameMgr::on_input(const SDL_Event& event)
{
	get_current_game()->on_input(event);
}
/*获取游戏运行*/
bool GameMgr::get_is_run()
{
	return is_run;
}
/*设置游戏运行*/
void GameMgr::set_is_run(bool run)
{
	is_run = run;
}