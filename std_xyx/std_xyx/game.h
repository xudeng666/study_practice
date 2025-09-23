#pragma once

#include "scene.h"
#include "game_type.h"

#include <memory>
#include <unordered_map>
#include <utility> 

/*��Ϸ����*/
class Game: public Obj
{
public:
	Game() = default;
	Game(const std::string& id);
	Game(const std::string& id, const int num);
	virtual ~Game() override;

	template <typename T, typename... Args>
	static std::shared_ptr<T> create_scene(Args&&... args);

	DEFINE_TYPE_NAME(Game);

	virtual void on_init() override;
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
	/*����ID*/
	virtual void set_ID(const std::string& str) override;
	virtual void set_ID(const std::string& str, const int num) override;
	/*��ȡID*/
	virtual std::string get_ID() override;

	/*��ȡ��ǰ����*/
	std::shared_ptr<Scene> get_current_scene();
	/*�����л�*/
	void exchange_scene(SceneType type);

protected:
	/*��ǰ��������*/
	SceneType current_scene_type = SceneType::MENU;

	std::unordered_map<SceneType, std::shared_ptr<Scene>> scene_pool;
};

INIT_TYPE_NAME(Game);