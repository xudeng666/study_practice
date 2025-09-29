#pragma once

#include "scene.h"
#include "game_type.h"

#include <memory>
#include <unordered_map>
#include <utility> 

/*游戏基类*/
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
	/*进入游戏初始化*/
	virtual void on_enter() override;
	/*处理数据*/
	virtual void on_update(float delta) override;
	/*玩家输入*/
	virtual void on_input(const SDL_Event& event) override;
	/*渲染绘图*/
	virtual void on_render() override;
	/*退出游戏*/
	virtual void on_exit() override;
	/*设置ID*/
	virtual void set_ID(const std::string& str) override;
	virtual void set_ID(const std::string& str, const int num) override;
	/*获取ID*/
	virtual std::string get_ID() override;
	/*获取当前场景*/
	std::shared_ptr<Scene> get_current_scene();
	/*场景切换*/
	void exchange_scene(SceneType type);
	/*清理当前场景*/
	virtual void destroy_current_scene();
	/*新建当前场景*/
	virtual void create_target_scene();

protected:
	/*当前场景类型*/
	SceneType current_scene_type = SceneType::MENU;

	std::unordered_map<SceneType, std::shared_ptr<Scene>> scene_pool;
};