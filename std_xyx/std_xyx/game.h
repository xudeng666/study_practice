#pragma once

#include "scene.h"
#include "game_type.h"

/*游戏基类*/
class Game
{
public:
	Game();
	~Game();

	/*进入游戏初始化*/
	virtual void on_enter();
	/*处理数据*/
	virtual void on_update(float delta);
	/*玩家输入*/
	virtual void on_input(const SDL_Event& event);
	/*渲染绘图*/
	virtual void on_render();
	/*退出游戏*/
	virtual void on_exit();
	/*获取当前场景*/
	Scene* get_current_scene();
	/*场景切换*/
	void exchange_scene(SceneType type);
	/*场景初始化*/
	virtual void on_scene_init() = 0;

protected:
	/*当前场景类型*/
	SceneType current_scene_type = SceneType::MENUE;

	std::unordered_map<SceneType, Scene* > scene_pool;
};

