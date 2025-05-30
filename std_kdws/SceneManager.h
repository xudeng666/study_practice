#pragma once
#include "Scene.h"

/*场景管理器*/
class SceneManager
{
public:
	/*枚举类-标记场景状态*/
	enum class SceneType
	{
		Menu,
		Game,
		Selector
	};
public:
	SceneManager() = default;
	~SceneManager() = default;

	/*设置当前场景*/
	void set_current_scene(Scene* scene)
	{
		current_scene = scene;
		current_scene->on_enter();
	}

	/*场景切换*/
	void exchange_scene(SceneType type)
	{
		// 推出当前场景
		current_scene->on_exit();
		// 场景切换
		switch (type)
		{
		case SceneManager::SceneType::Menu:
			break;
		case SceneManager::SceneType::Game:
			break;
		case SceneManager::SceneType::Selector:
			break;
		default:
			break;
		}
		// 新场景初始化
		current_scene->on_enter();
	}

	/*处理数据*/
	void on_update(int delta)
	{
		current_scene->on_update(delta);
	}
	/*用于渲染绘图*/
	void on_draw(const Camera& camera)
	{
		current_scene->on_draw(camera);
	}
	/*处理玩家输入*/
	void on_input(const ExMessage& msg)
	{
		current_scene->on_input(msg);
	}

private:
	/*当前场景*/
	Scene* current_scene = nullptr;
};

