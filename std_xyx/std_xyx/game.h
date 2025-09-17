#pragma once

#include "obj.h"
#include "scene.h"
#include "game_type.h"

/*��Ϸ����*/
class Game: public Obj
{
public:
	Game();
	virtual ~Game();

	/*������Ϸ��ʼ��*/
	virtual void on_enter() override;
	/*��������*/
	virtual void on_update(float delta) override;
	/*�������*/
	virtual void on_input(const SDL_Event& event) override;
	/*��Ⱦ��ͼ*/
	virtual void on_render() override;
	/*�˳���Ϸ*/
	virtual void on_exit() override;
	/*��ȡ��ǰ����*/
	Scene* get_current_scene();
	/*�����л�*/
	void exchange_scene(SceneType type);
	/*������ʼ��*/
	virtual void on_scene_init() = 0;
	/*����ID*/
	virtual void set_ID(const std::string str) override;
	virtual void set_ID(const std::string str, const int num) override;
	/*��ȡID*/
	virtual std::string get_ID() override;

protected:
	/*��ǰ��������*/
	SceneType current_scene_type = SceneType::MENUE;

	std::unordered_map<SceneType, Scene* > scene_pool;
};