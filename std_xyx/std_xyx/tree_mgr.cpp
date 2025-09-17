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
	GameObj_UP root = std::make_unique<GameObj>("root");
	root->set_position(Vector2(0, 0));
	root->set_size({ _WIN_W_,_WIN_H_ });
	root->set_anchor_mode(AnchorMode::TOPLEFT);
	root->set_anchor_referent_mode(AnchorMode::TOPLEFT);
	GameObj_UP bg = std::make_unique<GameObj>("bg");
	bg->set_position(Vector2(0, 0));
	bg->set_size({ _WIN_W_,_WIN_H_ });
	bg->set_anchor_mode(AnchorMode::CENTER);
	bg->set_anchor_referent_mode(AnchorMode::CENTER);
	GameObj_UP game = std::make_unique<GameObj>("game");
	game->set_position(Vector2(0, 0));
	game->set_size({ _WIN_W_,_WIN_H_ });
	game->set_anchor_mode(AnchorMode::CENTER);
	game->set_anchor_referent_mode(AnchorMode::CENTER);
	GameObj_UP ui = std::make_unique<GameObj>("ui");
	ui->set_position(Vector2(0, 0));
	ui->set_size({ _WIN_W_,_WIN_H_ });
	ui->set_anchor_mode(AnchorMode::CENTER);
	ui->set_anchor_referent_mode(AnchorMode::CENTER);

	root_node = std::make_shared<TreeNode>(root);
	TreeNode_SP bg_n = std::make_shared<TreeNode>(bg);
	TreeNode_SP game_n = std::make_shared<TreeNode>(game);
	TreeNode_SP ui_n = std::make_shared<TreeNode>(ui);

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