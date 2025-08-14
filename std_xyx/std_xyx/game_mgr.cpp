#include "game_mgr.h"


GameMgr* GameMgr::manager = nullptr;

GameMgr* GameMgr::instance()
{
	if (!manager)
	{
		manager = new GameMgr();
	}
	return manager;
}

/*设置当前游戏*/
void GameMgr::set_current_game(Game* game)
{
	current_game = game;
	current_game->on_enter();
}

/*游戏切换*/
void GameMgr::exchange_scene(GameType type)
{
	if (type == current_type) return;

	if (type != GameType::START && current_type != GameType::START)
	{
		return;
	}

	current_type = type;
	// 退出当前游戏
	current_game->on_exit();
	// 游戏切换
	switch (current_type)
	{
	case GameType::START:	current_game = start_game;	break;
	case GameType::XCZ:		current_game = xcz_game;	break;
	case GameType::KDWS:	current_game = kdws_game;	break;
	case GameType::DLD:		current_game = dld_game;	break;
	case GameType::ZMDJ:	current_game = zmdj_game;	break;
	case GameType::PHF:		current_game = phf_game;	break;
	}
	// 新游戏初始化
	current_game->on_enter();
}

/*处理数据*/
void GameMgr::on_update(int delta)
{
	current_game->on_update(delta);
}
/*用于渲染绘图*/
void GameMgr::on_render(const Camera* camera)
{
	current_game->on_render(camera);
}
/*处理玩家输入*/
void GameMgr::on_input(const SDL_Event& event)
{
	current_game->on_input(event);
}
/*获取游戏运行*/
bool GameMgr::get_is_run()
{
	return is_run;
}
/*设置游戏运行*/
bool GameMgr::set_is_run(bool run)
{
	is_run = run;
}