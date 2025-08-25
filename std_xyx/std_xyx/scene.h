#pragma once

#include "Camera.h"
#include "game_obj.h"
#include "res_mgr.h"

#include <queue>
#include <iostream>

/*场景类-基类*/
class Scene
{
public:
	Scene()
	{
		root = new GameObj({ 0,0 });
		root->set_ID("root");
		root->set_size({ _WIN_W_,_WIN_H_ });
		root->set_anchor_mode(AnchorMode::TOPLEFT);
		root->set_parent_anchor_mode(AnchorMode::TOPLEFT);

		background = new GameObj({ 0,0 });
		background->set_ID("background");
		background->set_size({ _WIN_W_,_WIN_H_ });
		background->set_anchor_mode(AnchorMode::CENTER);
		background->set_parent_anchor_mode(AnchorMode::CENTER);

		entity = new GameObj({ 0,0 });
		entity->set_ID("entity");
		entity->set_size({ _WIN_W_,_WIN_H_ });
		entity->set_anchor_mode(AnchorMode::CENTER);
		entity->set_parent_anchor_mode(AnchorMode::CENTER);

		ui = new GameObj({ 0,0 });
		ui->set_ID("ui");
		ui->set_size({ _WIN_W_,_WIN_H_ });
		ui->set_anchor_mode(AnchorMode::CENTER);
		ui->set_parent_anchor_mode(AnchorMode::CENTER);

		root->add_children(background);
		root->add_children(entity);
		root->add_children(ui);
	}

	~Scene()
	{
		post_order_traversal(root, [&](GameObj* obj) {
			delete obj;
			});
	}

	/*场景初始化*/
	void on_enter()
	{
		pre_order_traversal(root, [&](GameObj* obj) {
			obj->on_enter();
			});
		if (_DE_BUG_)
		{
			ResMgr::instance()->res_traversal();
			pre_order_traversal(root, [&](GameObj* obj) {
				SDL_FRect r = obj->get_FRect();
				std::cout << "obj   " << obj->get_ID() << std::endl <<
					"         x: " << r.x << "  y: " << r.y << "  w: " << r.w << "  h: " << r.h << std::endl;
				});
		}
	}
	/*处理数据*/
	void on_update(float delta)
	{
		pre_order_traversal(root, [&](GameObj* obj) {
			obj->on_update(delta);
			});
	}

	/*玩家输入*/
	void on_input(const SDL_Event& event)
	{
		pre_order_traversal(root, [&](GameObj* obj) {
			obj->on_input(event);
			});
	}

	/*渲染绘图*/
	void on_render()
	{
		pre_order_traversal(root, [&](GameObj* obj) {
			obj->on_render();
			});
	}
	/*退出场景*/
	void on_exit()
	{
		pre_order_traversal(root, [&](GameObj* obj) {
			obj->on_exit();
			});
	}

	void set_ID(const std::string id)
	{
		ID = id;
	}

	std::string get_ID()
	{
		return ID;
	}

public:
	GameObj* get_obj_of_ID(std::string id)
	{
	}
	// 获取UI根节点
	GameObj* get_ui_root()
	{
		return root;
	}

	/// <summary>
	/// 前序遍历（深度优先）
	/// 先父后子
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void pre_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		if (callback)
		{
			callback(current_node);
		}

		for (GameObj* child : current_node->get_children())
		{
			pre_order_traversal(child, callback);
		}
	}

	/// <summary>
	/// 后序遍历（深度优先）
	/// 先子后父
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void post_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		for (GameObj* child : current_node->get_children())
		{
			post_order_traversal(child, callback);
		}

		if (callback)
		{
			callback(current_node);
		}
	}

	/// <summary>
	/// 层序遍历（广度优先）
	/// 按层次顺序
	/// </summary>
	/// <param name="current_node">遍历起始节点</param>
	/// <param name="callback">回调函数</param>
	void level_order_traversal(GameObj* current_node, const std::function<void(GameObj*)>& callback)
	{
		if (!current_node) return;

		if (!current_node->get_display()) return;

		std::queue<GameObj*> q;

		q.push(current_node);

		while (!q.empty())
		{
			int length = q.size();
			for (int i = 0; i < length; i++)
			{
				GameObj* p = q.front();
				q.pop();
				if (callback)
				{
					callback(p);
				}
				for (GameObj* child: current_node->get_children())
				{
					q.push(child);
				}
			}
		}
	}

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

