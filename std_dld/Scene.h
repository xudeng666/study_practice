#pragma once
#include <graphics.h>

/*场景类-基类*/
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	/*进入场景初始化*/
	virtual void on_enter() {}
	/*处理数据*/
	virtual void on_update() {}
	/*用于渲染绘图*/
	virtual void on_draw() {}
	/*处理玩家输入*/
	virtual void on_input(const ExMessage& msg) {}
	/*退出场景处理*/
	virtual void on_exit() {}
private:
};

