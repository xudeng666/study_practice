#pragma once
#include "Scene.h"
#include "SceneManager.h"
#include <iostream>


extern SceneManager scene_manager;

/*��Ϸ����*/
class GamaScene :
    public Scene
{
public:
	GamaScene() = default;
	~GamaScene() = default;

	/*���볡����ʼ��*/
	void on_enter()
	{
		std::cout << "������Ϸ" << std::endl;
	}
	/*��������*/
	void on_update(int delta)
	{
		std::cout << "��Ϸ������..." << std::endl;
	}
	/*������Ⱦ��ͼ*/
	void on_draw(const Camera& camera)
	{
		outtextxy(0, 0, _T("������Ϸ"));
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		if (msg.message == WM_KEYDOWN)
		{
			scene_manager.exchange_scene(SceneManager::SceneType::Menu);
		}
	}
	/*�˳���Ϸ����*/
	void on_exit()
	{
		std::cout << "�˳���Ϸ" << std::endl;
	}
private:
};

