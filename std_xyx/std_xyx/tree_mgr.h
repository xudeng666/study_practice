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

	// ��Ŀ¼
	std::shared_ptr<TreeNode<GameObj>> root = nullptr;
	// UI ��Ŀ¼
	std::shared_ptr<TreeNode<GameObj>> background = nullptr;
	// UI ��Ŀ¼
	std::shared_ptr<TreeNode<GameObj>> entity = nullptr;
	// UI ��Ŀ¼
	std::shared_ptr<TreeNode<GameObj>> ui = nullptr;
};

