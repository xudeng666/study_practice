#include "tree_mgr.h"
#include "game_obj.h"

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
	root_node = TreeNode::create(std::make_unique<GameObj>("root"));
	root_node->get_obj()->set_position(Vector2(0, 0));
	root_node->get_obj()->set_size({ _WIN_W_,_WIN_H_ });
	root_node->get_obj()->set_anchor_mode(AnchorMode::TOPLEFT);
	root_node->get_obj()->set_anchor_referent_mode(AnchorMode::TOPLEFT);

	TreeNode_SP bg_n = create_layer_node("bg");
	TreeNode_SP game_n = create_layer_node("game");
	TreeNode_SP ui_n = create_layer_node("ui");

	bg_node = bg_n;
	game_node = game_n;
	ui_node = ui_n;

	root_node->add_children(bg_n);
	root_node->add_children(game_n);
	root_node->add_children(ui_n);
}

TreeMgr::~TreeMgr()
{
	manager = nullptr;
}

TreeNode_SP TreeMgr::find_obj(std::string id, TreeNode_SP start_node)
{
	TreeNode_SP result = nullptr;
	if (!start_node)
	{
		start_node = root_node;
	}
	pre_order_traversal(start_node, [&](TreeNode_SP node) {
		if (node->get_obj()->get_ID() == id)
		{
			result = node;
		}
		});
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

TreeNode_SP TreeMgr::create_layer_node(const std::string& id)
{
	auto node = TreeNode::create(std::make_unique<GameObj>(id));
	node->get_obj()->set_position(Vector2(0, 0));
	node->get_obj()->set_size({ _WIN_W_, _WIN_H_ });
	node->get_obj()->set_anchor_mode(AnchorMode::CENTER);
	node->get_obj()->set_anchor_referent_mode(AnchorMode::CENTER);
	return node;
}

void TreeMgr::pre_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_obj()->get_display()) return;

	if (callback)
	{
		callback(current_node);
	}

	current_node->for_each_child([&](TreeNode_SP node) {
		pre_order_traversal(node, callback);
		});
}

void TreeMgr::post_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_obj()->get_display()) return;

	current_node->for_each_child([&](TreeNode_SP node) {
		post_order_traversal(node, callback);
		});

	if (callback)
	{
		callback(current_node);
	}
}

void TreeMgr::level_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback)
{
	if (!current_node) return;

	if (!current_node->get_obj()->get_display()) return;

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
				if (node->get_obj()->get_display())
				{
					q.push(node);
				}
				});
		}
	}
}