#include "tree_mgr.h"

#include <queue>
#include <assert.h>


TreeMgr* TreeMgr::manager = nullptr;

TreeMgr* TreeMgr::instance()
{
	if (!manager)
	{
		manager = new TreeMgr();
	}
	return manager;
}

TreeMgr::TreeMgr()
{
	root_node = create_root_node("root");

	TreeNode_SP bg_n = create_layer_node("bg");
	TreeNode_SP game_n = create_layer_node("game");
	TreeNode_SP ui_n = create_layer_node("ui");

	bg_node = bg_n;
	game_node = game_n;
	ui_node = ui_n;

	root_node->add_children(std::move(bg_n));
	root_node->add_children(std::move(game_n));
	root_node->add_children(std::move(ui_n));
}

TreeMgr::~TreeMgr()
{
	manager = nullptr;
}

TreeNode_SP TreeMgr::find_obj(std::string id, TreeNode_SP start_node)
{
	TreeNode_SP result = nullptr;
	pre_order_traversal([&](TreeNode_SP node) {
		if (node->get_ID() == id)
		{
			result = node;
		}
		}, start_node);
	return result;
}

TreeNode_SP TreeMgr::get_root_node()
{
	return root_node;
}

TreeNode_SP TreeMgr::get_bg_node()
{
	return bg_node.lock();
}

TreeNode_SP TreeMgr::get_game_node()
{
	return game_node.lock();
}

TreeNode_SP TreeMgr::get_ui_node()
{
	return ui_node.lock();
}
/*创建层级节点*/
TreeNode_SP TreeMgr::create_layer_node(const std::string& id)
{
	auto node = TreeNode::create_obj<GameObj>(NodeType::LAYER, id);
	node->set_position(Vector2(0, 0));
	node->set_size({ _WIN_W_, _WIN_H_ });
	node->set_anchor_mode(AnchorMode::CENTER);
	node->set_anchor_referent_mode(AnchorMode::CENTER);
	return node;
}
/*创建根节点*/
TreeNode_SP TreeMgr::create_root_node(const std::string& id)
{
	auto node = TreeNode::create_obj<GameObj>(NodeType::ROOT, id);
	node->set_position(Vector2(0, 0));
	node->set_size({ _WIN_W_, _WIN_H_ });
	node->set_anchor_mode(AnchorMode::TOPLEFT);
	node->set_anchor_referent_mode(AnchorMode::TOPLEFT);
	return node;
}
// 释放所有节点
void TreeMgr::release_all()
{
	root_node.reset();
}
// 释放所有游戏类节点
void TreeMgr::release_all_game()
{
	if (!root_node) return;

	TreeNode_SP root_t = TreeNode::create_obj<GameObj>("temp");
	level_order_traversal([&](TreeNode_SP node) {
		if (node->get_node_type() == NodeType::GAMENODE)
		{
			root_t->add_children(node);
			//node->self_delete();
		}
		}, root_node, false);
	root_t.reset();
}

void TreeMgr::pre_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node, bool check_display)
{
	if (!current_node)
	{
		current_node = root_node;
	}

	if (check_display && !current_node->get_display()) return;

	if (callback)
	{
		callback(current_node);
	}

	current_node->for_each_child([&](TreeNode_SP node) {
		pre_order_traversal(callback, node, check_display);
		});
}

void TreeMgr::post_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node, bool check_display)
{
	if (!current_node)
	{
		current_node = root_node;
	}

	if (check_display && !current_node->get_display()) return;

	current_node->for_each_child([&](TreeNode_SP node) {
		post_order_traversal(callback, node, check_display);
		});

	if (callback)
	{
		callback(current_node);
	}
}

void TreeMgr::level_order_traversal(const std::function<void(TreeNode_SP)>& callback, TreeNode_SP current_node, bool check_display)
{
	if (!current_node)
	{
		current_node = root_node;
	}

	if (check_display && !current_node->get_display()) return;

	std::queue<TreeNode_SP> q;

	q.push(current_node);

	while (!q.empty())
	{
		int length = q.size();
		for (int i = 0; i < length; i++)
		{
			TreeNode_SP p = q.front();
			q.pop();
			if (callback)
			{
				callback(p);
			}
			p->for_each_child([&](TreeNode_SP node) {
				if (!check_display || node->get_display())
				{
					q.push(node);
				}
				});
		}
	}
}