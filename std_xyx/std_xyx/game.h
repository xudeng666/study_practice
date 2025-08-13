#pragma once

#include "game_type.h"
#include "camera.h"
#include "scene.h"

/*游戏基类*/
class Game
{
public:
	Game() = default;
	~Game() = default;

	/*进入游戏初始化*/
	virtual void on_enter() {}
	/*处理数据*/
	virtual void on_update(int delta) {}
	/*渲染绘图*/
	virtual void on_input(const SDL_Event& event) {}
	/*玩家输入*/
	virtual void on_render(const Camera* camera) {}
	/*退出游戏*/
	virtual void on_exit() {}
	/*设置当前场景*/
	virtual void set_current_scene(Scene* scene) {}
	/*场景切换*/
	virtual void exchange_scene(SceneType type) {}

private:
	GameType game_type = GameType::NONE;
	/*当前场景*/
	Scene* current_scene = nullptr;
};

