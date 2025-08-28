#pragma once

#include "game.h"
#include "game_type.h"

/*游戏管理器*/
class GameMgr
{
public:
	static GameMgr* instance();
	/*初始化*/
	void init();
	/*退出游戏*/
	void deinit();
	/*获取当前游戏*/
	Game* get_current_game();
	/*获取当前游戏类型*/
	GameType get_current_type();
	/*游戏切换*/
	void exchange_game(GameType type);
	/*场景切换*/
	void exchange_scene(SceneType type);
	/*游戏初始化*/
	void on_enter();
	/*处理数据*/
	void on_update(float delta);
	/*用于渲染绘图*/
	void on_render();
	/*处理玩家输入*/
	void on_input(const SDL_Event& event);
	/*获取游戏运行*/
	bool get_is_run();
	/*设置游戏运行*/
	void set_is_run(bool run);

private:
	GameMgr() = default;
	~GameMgr() = default;

private:
	static GameMgr* manager;

	bool is_run = true;

	GameType current_type = GameType::START;

	std::unordered_map<GameType, Game*> game_pool;
};

