#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>


extern SceneManager scene_manager;

/*游戏场景*/
class GamaScene :
    public Scene
{
public:
	GamaScene() = default;
	~GamaScene() = default;

	/*进入场景初始化*/
	void on_enter()
	{
		std::cout << "进入游戏" << std::endl;
	}
	/*处理数据*/
	void on_update(int delta)
	{
		std::cout << "游戏运行中..." << std::endl;
	}
	/*用于渲染绘图*/
	void on_draw(const Camera& camera)
	{
		outtextxy(0, 0, _T("绘制游戏"));
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Menu);
		}
	}
	/*退出游戏场景*/
	void on_exit()
	{
		std::cout << "退出游戏" << std::endl;
	}
private:
};

