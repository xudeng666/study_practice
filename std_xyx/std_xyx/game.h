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
	virtual void on_enter();
	/*��������*/
	virtual void on_update(float delta);
	/*�������*/
	virtual void on_input(const SDL_Event& event);
	/*��Ⱦ��ͼ*/
	virtual void on_render();
	/*�˳���Ϸ*/
	virtual void on_exit();
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

