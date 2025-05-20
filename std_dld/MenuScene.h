#pragma once
#include "Scene.h"
#include "Camera.h"
#include "SceneManager.h"
#include <iostream>

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
		mciSendString(_T("play bgm_menu repeat from 0"), nullptr, 0, nullptr);
	}
	/*处理数据*/
	void on_update(int delta)
	{
	}
	/*渲染绘图*/
	void on_draw(const Camera& camera)
	{
		putimage(0,0,&img_menu_background);
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString(_T("play ui_confirm from 0"), nullptr, 0, nullptr);
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

