#pragma once
#include "Scene.h"

/*����������*/
class SceneManager
{
public:
	/*ö����-��ǳ���״̬*/
	enum class SceneType
	{
		Menu,
		Game,
		Selector
	};
public:
	SceneManager() = default;
	~SceneManager() = default;

	/*���õ�ǰ����*/
	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

	/*�����л�*/
	void exchange_scene(SceneType type)
	{
		// �Ƴ���ǰ����
		current_scene->on_exit();
		// �����л�
		switch (type)
		{
		case SceneManager::SceneType::Menu:
			break;
		case SceneManager::SceneType::Game:
			break;
		case SceneManager::SceneType::Selector:
			break;
		default:
			break;
		}
		// �³�����ʼ��
		current_scene->on_enter();
	}

	/*��������*/
	void on_update(int delta)
	{
		current_scene->on_update(delta);
	}
	/*������Ⱦ��ͼ*/
	void on_draw(const Camera& camera)
	{
		current_scene->on_draw(camera);
	}
	/*�����������*/
	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}

private:
	/*��ǰ����*/
	Scene* current_scene = nullptr;
};

