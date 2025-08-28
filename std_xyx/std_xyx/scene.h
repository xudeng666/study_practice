#pragma once

//#include "game_obj.h"
//#include "game_mgr.h"

#include <queue>
#include <functional>
#include <string>

#include <SDL.h>

class GameObj;

/*场景类-基类*/
class Scene
{
public:
	Scene();
	virtual ~Scene();
	/*场景初始化*/
	virtual void on_enter();
	/*处理数据*/
	virtual void on_update(float delta);
	/*玩家输入*/
	virtual void on_input(const SDL_Event& event);
	/*渲染绘图*/
	virtual void on_render();
	/*退出场景*/
	virtual void on_exit();
	void set_ID(const std::string id);
	std::string get_ID();

public:
	/// <summary>
	/// 查找对象
	/// </summary>
	/// <param name="id">std::string 对象ID</param>
	/// <returns>GameObj* 对象指针</returns>
	GameObj* find_obj(std::string id);

	// 获取UI根节点
	GameObj* get_ui_root();

	/// <summary>
	/// 前序遍历（深度优先）
	/// 先父后子
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void pre_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);
	/// <summary>
	/// 后序遍历（深度优先）
	/// 先子后父
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void post_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);

	/// <summary>
	/// 层序遍历（广度优先）
	/// 按层次顺序
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void level_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback);

protected:
	std::string ID;
	// UI 根目录
	GameObj* root = nullptr;
	// UI 根目录
	GameObj* background = nullptr;
	// UI 根目录
	GameObj* entity = nullptr;
	// UI 根目录
	GameObj* ui = nullptr;
	// UI 索引表 暂时用不着
	// std::unordered_map<std::string, GameObj* > ui_map;
};

