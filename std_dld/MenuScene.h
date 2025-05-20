#pragma once
#include "Scene.h"
#include "Camera.h"
#include "SceneManager.h"
#include <iostream>

extern SceneManager scene_manager;
extern IMAGE img_menu_background;

/*�˵���*/
class MenuScene :
    public Scene
{
public:
	MenuScene() = default;
	~MenuScene() = default;

	/*���볡����ʼ��*/
	void on_enter()
	{
		mciSendString(_T("play bgm_menu repeat from 0"), nullptr, 0, nullptr);
	}
	/*��������*/
	void on_update(int delta)
	{
	}
	/*��Ⱦ��ͼ*/
	void on_draw(const Camera& camera)
	{
		putimage(0,0,&img_menu_background);
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYUP)
		{
			mciSendString(_T("play ui_confirm from 0"), nullptr, 0, nullptr);
			scene_manager.exchange_scene(SceneManager::SceneType::Selector);
		}
	}
	/*�˳���������*/
	void on_exit()
	{
		std::cout << "�˳����˵�" << std::endl;
	}
private:
};

