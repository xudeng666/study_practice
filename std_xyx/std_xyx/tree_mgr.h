#pragma once

#include "game_obj.h"

class TreeMgr
{
public:
	static TreeMgr* instance();
	/// <summary>
	/// 销毁管理器
	/// </summary>
	void destroy();

	/// <summary>
	/// 查找对象
	/// </summary>
	/// <param name="id">std::string 对象ID</param>
	/// <param name="node">TreeNode_SP 起始节点</param>
	/// <returns>TreeNode_SP 对象指针</returns>
	TreeNode_SP find_obj(std::string id, TreeNode_SP start_node = nullptr);

	// 获取根节点
	TreeNode_SP get_root_node();
	// 获取背景节点
	TreeNode_SP get_bg_node();
	// 获取游戏节点
	TreeNode_SP get_game_node();
	// 获取UI节点
	TreeNode_SP get_ui_node();
	// 新建层级节点
	TreeNode_SP create_layer_node(const std::string& id);
	// 新建根节点
	TreeNode_SP create_root_node(const std::string& id);
	// 释放所有节点
	void release_all();
	// 释放所有游戏类节点
	void release_all_game();
	// 添加到背景节点
	bool add_to_bg(TreeNode_SP node);
	// 添加到游戏节点
	bool add_to_game(TreeNode_SP node);
	// 添加到UI节点
	bool add_to_ui(TreeNode_SP node);

	/// <summary>
	/// 前序遍历（深度优先）
	/// 先父后子
	/// </summary>
	/// <param name="callback">回调函数</param>
	/// <param name="current_node">遍历起始节点 默认根节点</param>
	/// <param name="check_display">是否计入隐藏 true/false 是/否</param>
	void pre_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node = nullptr, bool check_display = true);
	/// <summary>
	/// 后序遍历（深度优先）
	/// 先子后父
	/// </summary>
	/// <param name="callback">回调函数</param>
	/// <param name="current_node">遍历起始节点 默认根节点</param>
	/// <param name="check_display">是否计入隐藏 true/false 是/否</param>
	void post_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node = nullptr, bool check_display = true);

	/// <summary>
	/// 层序遍历（广度优先）
	/// 按层次顺序
	/// </summary>
	/// <param name="callback">回调函数</param>
	/// <param name="current_node">遍历起始节点 默认根节点</param>
	/// <param name="check_display">是否计入隐藏 true/false 是/否</param>
	void level_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node = nullptr, bool check_display = true);
private:
	TreeMgr();
	~TreeMgr();

private:
	static TreeMgr* manager;

	// 根目录
	TreeNode_SP root_node = nullptr;
	// 背景节点
	TreeNode_WP bg_node;
	// 游戏对象节点
	TreeNode_WP game_node;
	// UI节点
	TreeNode_WP ui_node;
};

