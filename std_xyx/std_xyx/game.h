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
	std::shared_ptr<T> create_scene(SceneType type, Args&&... args)
	{
		std::shared_ptr<T> scene = std::make_shared<T>(std::forward<Args>(args)...);
		scene->on_init();
		scene_pool[type] = scene;
		std::cout << "create_scene:" << scene_pool[type]->get_type_name() << std::endl;
		return scene;
	}

	DEFINE_TYPE_NAME(Game);

	virtual void on_init() = 0;
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
	/*����ǰ����*/
	virtual void destroy_current_scene();
	/*�½���ǰ����*/
	virtual void create_target_scene();

protected:
	/*��ǰ��������*/
	SceneType current_scene_type = SceneType::MENU;

	std::unordered_map<SceneType, std::shared_ptr<Scene>> scene_pool;
};