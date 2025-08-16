#pragma once

#include "game_type.h"
#include "camera.h"
#include "scene.h"

/*��Ϸ����*/
class Game
{
public:
	Game() = default;
	~Game() = default;

	/*������Ϸ������Դ*/
	void on_load();
	/*������Ϸ��ʼ��*/
	void on_enter();
	/*��������*/
	void on_update(int delta);
	/*�������*/
	void on_input(const SDL_Event& event);
	/*��Ⱦ��ͼ*/
	void on_render();
	/*�˳���Ϸ*/
	void on_exit();
	/*���õ�ǰ����*/
	void set_current_scene(Scene* scene);
	/*��ȡ��ǰ����*/
	Scene* get_current_scene();
	/*�����л�*/
	virtual void exchange_scene(SceneType type) {}
	/*������ʼ��*/
	virtual void on_scene_init() {}

protected:
	/*��ǰ����*/
	Scene* current_scene = nullptr;
	/*��ǰ��������*/
	SceneType current_scene_type = SceneType::MENUE;
};

