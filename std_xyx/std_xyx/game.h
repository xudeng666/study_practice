#pragma once

#include "game_type.h"
#include "camera.h"
#include "scene.h"

/*��Ϸ����*/
class Game
{
public:
	Game();
	~Game();

	/*������Ϸ��ʼ��*/
	void on_enter();
	/*��������*/
	void on_update(float delta);
	/*�������*/
	void on_input(const SDL_Event& event);
	/*��Ⱦ��ͼ*/
	void on_render();
	/*�˳���Ϸ*/
	void on_exit();
	/*��ȡ��ǰ����*/
	Scene* get_current_scene();
	/*�����л�*/
	void exchange_scene(SceneType type);
	/*������ʼ��*/
	virtual void on_scene_init() = 0;

protected:
	/*��ǰ��������*/
	SceneType current_scene_type = SceneType::MENUE;

	std::unordered_map<SceneType, Scene* > scene_pool;
};

