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

	/*进入游戏加载资源*/
	void on_load();
	/*进入游戏初始化*/
	void on_enter();
	/*处理数据*/
	void on_update(int delta);
	/*玩家输入*/
	void on_input(const SDL_Event& event);
	/*渲染绘图*/
	void on_render();
	/*退出游戏*/
	void on_exit();
	/*设置当前场景*/
	void set_current_scene(Scene* scene);
	/*获取当前场景*/
	Scene* get_current_scene();
	/*场景切换*/
	virtual void exchange_scene(SceneType type) {}
	/*场景初始化*/
	virtual void on_scene_init() {}

protected:
	/*当前场景*/
	Scene* current_scene = nullptr;
	/*当前场景类型*/
	SceneType current_scene_type = SceneType::MENUE;
};

