#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>


extern SceneManager scene_manager;

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
		// 进入主菜单
		std::cout<<"进入主菜单" << std::endl;
	}
	/*处理数据*/
	void on_update()
	{
		std::cout << "主菜单运行中..." << std::endl;
	}
	/*用于渲染绘图*/
	void on_draw()
	{
		outtextxy(0,0,_T("绘制主菜单"));
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Selector);
		}
	}
	/*退出场景处理*/
	void on_exit()
	{
		std::cout << "退出主菜单" << std::endl;
	}
private:
};

