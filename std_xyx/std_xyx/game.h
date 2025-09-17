#pragma once

#include "obj.h"
#include "scene.h"
#include "game_type.h"

/*游戏基类*/
class Game: public Obj
{
public:
	Game();
	virtual ~Game();

	/*进入游戏初始化*/
	virtual void on_enter() override;
	/*处理数据*/
	virtual void on_update(float delta) override;
	/*玩家输入*/
	virtual void on_input(const SDL_Event& event) override;
	/*渲染绘图*/
	virtual void on_render() override;
	/*退出游戏*/
	virtual void on_exit() override;
	/*获取当前场景*/
	Scene* get_current_scene();
	/*场景切换*/
	void exchange_scene(SceneType type);
	/*场景初始化*/
	virtual void on_scene_init() = 0;
	/*设置ID*/
	virtual void set_ID(const std::string str) override;
	virtual void set_ID(const std::string str, const int num) override;
	/*获取ID*/
	virtual std::string get_ID() override;

protected:
	/*当前场景类型*/
	SceneType current_scene_type = SceneType::MENUE;

	std::unordered_map<SceneType, Scene* > scene_pool;
};