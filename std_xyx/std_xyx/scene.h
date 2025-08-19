#pragma once

#include "Camera.h"

/*场景类-基类*/
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	/*场景初始化*/
	virtual void on_enter() {}
	/*处理数据*/
	virtual void on_update(float delta) {}
	/*渲染绘图*/
	virtual void on_input(const SDL_Event& event) {}
	/*玩家输入*/
	virtual void on_render() {}
	/*退出场景*/
	virtual void on_exit() {}
};

