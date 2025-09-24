#include "game_mgr.h"
#include "game_start.h"
#include "game_xcz.h"

#include <assert.h>

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
	create_game<GameStart>(GameType::START, "GameStart");

	current_type = GameType::START;

	on_enter();
}

void GameMgr::deinit()
{
	game_pool.clear();
	delete manager;
	manager = nullptr;
}

std::shared_ptr<Game> GameMgr::get_current_game()
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
	auto last_game = get_current_game();
	if (last_game) {
		last_game->on_exit();			// 调用游戏的退出逻辑（释放场景、资源）
		game_pool.erase(current_type);	// 从游戏池删除旧游戏
	}
	current_type = type;
	switch (current_type)
	{
	case GameType::START:
		create_game<GameStart>(current_type, "GameStart");
		break;
	case GameType::XCZ:
		create_game<GameXcz>(current_type, "GameXcz");
		break;
	/*case GameType::KDWS:
		create_game<GameKdws>(current_type, "GameKdws");
		break;
	case GameType::DLD:
		create_game<GameDld>(current_type, "GameDld");
		break;
	case GameType::ZMDJ:
		create_game<GameZmdj>(current_type, "GameZmdj");
		break;
	case GameType::PHF:
		create_game<GamePhf>(current_type, "GamePhf");
		break;*/
	default:
		assert(false && "未知的 GameType，无法创建场景");
		break;
	}
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