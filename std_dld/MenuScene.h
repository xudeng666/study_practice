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
		animation_peashooter_run_right.set_loop(true);

		timer.set_wait_time(1000);
		timer.set_one_shot(false);
		timer.set_callback(
			[]()
			{
				std::cout << "Shot!" << std::endl;
			}
		);
		/*animation_peashooter_run_right.set_callback(
			[]()
			{
				scene_manager.exchange_scene(SceneManager::SceneType::Game);
			}
		);*/
	}
	/*��������*/
	void on_update(int delta)
	{
		animation_peashooter_run_right.on_updata(delta);
		mainCamera.on_update(delta);
		timer.on_update(delta);
	}
	/*��Ⱦ��ͼ*/
	void on_draw()
	{
		const Vector2& pos_mcamera = mainCamera.get_position();
		animation_peashooter_run_right.on_draw((int)(100 - pos_mcamera.x), (int)(100 - pos_mcamera.y));
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			//scene_manager.exchange_scene(SceneManager::SceneType::Selector);
			mainCamera.shake(10, 350);
		}
	}
	/*�˳���������*/
	void on_exit()
	{
		std::cout << "�˳����˵�" << std::endl;
	}
private:
	Animation animation_peashooter_run_right;
	Camera mainCamera;
	Timer timer;
};

