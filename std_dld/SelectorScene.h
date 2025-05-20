#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>

extern SceneManager scene_manager;

/*ѡȡ��ɫ����*/
class SelectorScene :
    public Scene
{
public:
	SelectorScene() = default;
	~SelectorScene() = default;

	/*���볡����ʼ��*/
	void on_enter()
	{
		std::cout << "����ѡ�ǽ���" << std::endl;
	}
	/*��������*/
	void on_update(int delta)
	{
		std::cout << "ѡ�ǽ���������..." << std::endl;
	}
	/*������Ⱦ��ͼ*/
	void on_draw()
	{
		outtextxy(0, 0, _T("����ѡ�ǽ���"));
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Game);
		}
	}
	/*�˳���Ϸ����*/
	void on_exit()
	{
		std::cout << "�˳�ѡ�ǽ���" << std::endl;
	}
};

