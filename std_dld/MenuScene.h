#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>


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
		// �������˵�
		std::cout<<"�������˵�" << std::endl;
	}
	/*��������*/
	void on_update()
	{
		std::cout << "���˵�������..." << std::endl;
	}
	/*������Ⱦ��ͼ*/
	void on_draw()
	{
		outtextxy(0,0,_T("�������˵�"));
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
};

