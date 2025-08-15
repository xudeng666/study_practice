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
	virtual void on_load() {}
	/*������Ϸ��ʼ��*/
	virtual void on_enter() {}
	/*��������*/
	virtual void on_update(int delta) {}
	/*�������*/
	virtual void on_input(const SDL_Event& event) {}
	/*��Ⱦ��ͼ*/
	virtual void on_render(const Camera* camera) {}
	/*�˳���Ϸ*/
	virtual void on_exit() {}
	/*���õ�ǰ����*/
	virtual void set_current_scene(Scene* scene) {}
	/*�����л�*/
	virtual void exchange_scene(SceneType type) {}

private:
	/*��ǰ����*/
	Scene* current_scene = nullptr;
};

