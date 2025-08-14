#pragma once

#include "game.h"
#include "game_type.h"

/*游戏管理器*/
class GameMgr
{
public:
	static GameMgr* instance();
	/*设置当前游戏*/
	void set_current_game(Game* game);
	/*游戏切换*/
	void exchange_scene(GameType type);
	/*处理数据*/
	void on_update(int delta);
	/*用于渲染绘图*/
	void on_render(const Camera* camera);
	/*处理玩家输入*/
	void on_input(const SDL_Event& event);
	/*获取游戏运行*/
	bool get_is_run();
	/*设置游戏运行*/
	bool set_is_run(bool run);

private:
	GameMgr() = default;
	~GameMgr() = default;

private:
	static GameMgr* manager;

	bool is_run = true;

	GameType current_type = GameType::START;
	/*当前游戏*/
	Game* current_game = nullptr;

	Game* start_game = nullptr;
	Game* xcz_game = nullptr;
	Game* kdws_game = nullptr;
	Game* dld_game = nullptr;
	Game* zmdj_game = nullptr;
	Game* phf_game = nullptr;
};

