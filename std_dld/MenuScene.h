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
	}
	/*��������*/
	void on_update(int delta)
	{
	}
	/*��Ⱦ��ͼ*/
	void on_draw(const Camera& camera)
	{
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
	}
	/*�˳���������*/
	void on_exit()
	{
		std::cout << "�˳����˵�" << std::endl;
	}
private:
	Animation animation_peashooter_run_right;
};

