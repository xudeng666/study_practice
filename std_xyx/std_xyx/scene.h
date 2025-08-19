#pragma once

#include "Camera.h"

/*������-����*/
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	/*������ʼ��*/
	virtual void on_enter() {}
	/*��������*/
	virtual void on_update(float delta) {}
	/*��Ⱦ��ͼ*/
	virtual void on_input(const SDL_Event& event) {}
	/*�������*/
	virtual void on_render() {}
	/*�˳�����*/
	virtual void on_exit() {}
};

