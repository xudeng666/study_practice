#pragma once
#include "Scene.h"
#include "Atlas.h"
#include "Camera.h"
#include "Timer.h"
#include "Animation.h"
#include "SceneManager.h"
#include <iostream>

extern Atlas atlas_peashooter_run_right;
extern SceneManager scene_manager;
extern IMAGE img_menu_background;

/*菜单类*/
class MenuScene :
    public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	/*进入场景初始化*/
	void on_enter()
	{
	}
	/*处理数据*/
	void on_update(int delta)
	{
	}
	/*渲染绘图*/
	void on_draw(const Camera& camera)
	{
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
	}
	/*退出场景处理*/
	void on_exit()
	{
		std::cout << "退出主菜单" << std::endl;
	}
private:
	Animation animation_peashooter_run_right;
};

