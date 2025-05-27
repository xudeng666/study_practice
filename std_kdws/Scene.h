#pragma once
#include <graphics.h>
#include "Camera.h"

/*������-����*/
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	/*���볡����ʼ��*/
	virtual void on_enter() {}
	/*��������*/
	virtual void on_update(int delta) {}
	/*������Ⱦ��ͼ*/
	virtual void on_draw(const Camera& camera) {}
	/*�����������*/
	virtual void on_input(const ExMessage& msg) {}
	/*�˳���������*/
	virtual void on_exit() {}
private:
};

