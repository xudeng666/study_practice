#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

extern SceneManager scene_manager;

/*选取角色场景*/
class SelectorScene :
    public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	/*进入场景初始化*/
	void on_enter()
	{
		std::cout << "进入选角界面" << std::endl;
	}
	/*处理数据*/
	void on_update(int delta)
	{
		std::cout << "选角界面运行中..." << std::endl;
	}
	/*用于渲染绘图*/
	void on_draw()
	{
		outtextxy(0, 0, _T("绘制选角界面"));
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Game);
		}
	}
	/*退出游戏场景*/
	void on_exit()
	{
		std::cout << "退出选角界面" << std::endl;
	}
};

