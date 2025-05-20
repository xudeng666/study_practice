#pragma once
#include "Scene.h"
#include "Atlas.h"
#include "Animation.h"
#include "SceneManager.h"
#include <iostream>

extern Atlas atlas_peashooter_run_right;
extern SceneManager scene_manager;

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
		animation_peashooter_run_right.set_atlas(&atlas_peashooter_run_right);
		animation_peashooter_run_right.set_interval(75);
		animation_peashooter_run_right.set_loop(false);
		animation_peashooter_run_right.set_callback(
			[]()
			{
				scene_manager.exchange_scene(SceneManager::SceneType::Game);
			}
		);
	}
	/*��������*/
	void on_update(int delta)
	{
		animation_peashooter_run_right.on_updata(delta);
	}
	/*��Ⱦ��ͼ*/
	void on_draw()
	{
		animation_peashooter_run_right.on_draw(100,100);
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Selector);
		}
	}
	/*�˳���������*/
	void on_exit()
	{
		std::cout << "�˳����˵�" << std::endl;
	}
private:
	Animation animation_peashooter_run_right;
};

