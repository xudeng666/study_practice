#pragma once

#include "tree_node.h"
#include "game_obj.h"

class TreeMgr
{
public:
	static TreeMgr* instance();
private:
	TreeMgr() = default;
	~TreeMgr() = default;

private:
	static TreeMgr* manager;

	// 根目录
	std::shared_ptr<TreeNode<GameObj>> root = nullptr;
	// UI 根目录
	std::shared_ptr<TreeNode<GameObj>> background = nullptr;
	// UI 根目录
	std::shared_ptr<TreeNode<GameObj>> entity = nullptr;
	// UI 根目录
	std::shared_ptr<TreeNode<GameObj>> ui = nullptr;
};

