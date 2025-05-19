#pragma once
#include <graphics.h>

/*������-����*/
class Scene
{
public:
	Scene() = default;
	~Scene() = default;

	/*���볡����ʼ��*/
	virtual void on_enter() {}
	/*��������*/
	virtual void on_update() {}
	/*������Ⱦ��ͼ*/
	virtual void on_draw() {}
	/*�����������*/
	virtual void on_input(const ExMessage& msg) {}
	/*�˳���������*/
	virtual void on_exit() {}
private:
};

