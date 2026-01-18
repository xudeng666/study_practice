#include "tree_node.h"
#include "game_obj.h"

#include <assert.h>

void TreeNode::set_parent(TreeNode_SP p)
{
	parent = p;
}

TreeNode_SP TreeNode::get_parent()
{
	return parent.lock();
}

void TreeNode::set_self_node(TreeNode_SP self)
{
	self_node = self;
}

TreeNode_SP TreeNode::get_self_node()
{
	return self_node.lock();
}

void TreeNode::set_node_type(NodeType type)
{
	node_type = type;
}

NodeType TreeNode::get_node_type()
{
	return node_type;
}

TreeNode_SP TreeNode::remove_children(TreeNode_SP node)
{
	auto it = find_child_iterator(node);
	if (it == children.end())
	{
		assert(false && "尝试删除不存在的子节点");
		return nullptr;
	}
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	children_change();
	removedObj->parent.reset();
	return removedObj;
}

TreeNode_SP TreeNode::remove_children(const std::function<bool(const TreeNode_SP&)>& func)
{
	auto it = find_child_iterator(func);
	if (it == children.end())
	{
		assert(false && "尝试删除不存在的子节点");
		return nullptr;
	}
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	children_change();
	removedObj->parent.reset();
	return removedObj;
}

void TreeNode::delete_children(TreeNode_SP node)
{
	auto it = find_child_iterator(node);
	if (it != children.end())
	{
		(*it)->parent.reset();
		(*it)->children.clear();
		children.erase(it);
	}
	children_change();
}

void TreeNode::delete_children(const std::function<bool(const TreeNode_SP&)>& func)
{
	auto it = find_child_iterator(func);
	if (it != children.end())
	{
		(*it)->parent.reset();
		(*it)->children.clear();
		children.erase(it);
	}
	children_change();
}

bool TreeNode::add_children(TreeNode_SP node, bool is_front)
{
	if (!node)
	{
		assert(false && "Cannot add null node as child");
		return false;
	}
	if (!node->parent.expired()) {
		node = node->get_parent()->remove_children(node);
	}

	// 步骤2：设置当前节点为新父节点
	node->set_parent(self_node.lock());
	node->run_added_fun();
	if (is_front)
	{
		children.insert(children.begin(), std::move(node));
	}
	else
	{
		children.push_back(std::move(node));
	}
	children_change();
	return true;
}

void TreeNode::run_added_fun()
{
	if (on_added_func)
	{
		on_added_func();
	}
}

void TreeNode::set_added_fun(const std::function<void()>& func)
{
	on_added_func = func;
}

void TreeNode::children_change()
{
}

void TreeNode::for_each_child(const std::function<void(TreeNode_SP)>& func)
{
	if (!func) return;

	for (const auto& child_ptr : children) {
		if (child_ptr) {
			func(child_ptr);
		}
	}
}

void TreeNode::sort_children(const std::function<bool(const TreeNode_SP&, const TreeNode_SP&)>& func)
{
	if (!func) return;

	std::sort(children.begin(), children.end(), [&func](const TreeNode_SP& a, const TreeNode_SP& b) {
		// 如果有空节点，则排在后面
		if (!a) return false;
		if (!b) return true;
		// 解引用智能指针，调用外部传入的比较逻辑
		return func(a, b);
		});
}

void TreeNode::remove_children_if(const std::function<bool(const TreeNode_SP&)>& func)
{
	if (!func) return;

	children.erase(std::remove_if(children.begin(), children.end(), [&func](const TreeNode_SP& child) {
			if (!child)
			{
				return true;
			}
			return func(child);
			}),children.end()
	);
	
	children_change();
}

void TreeNode::clear_children()
{
	children.clear();
}

int TreeNode::get_children_size()
{
	return children.size();
}

TreeNode_SP TreeNode::find_child(const std::function<bool(const TreeNode_SP&)>& func)
{
	ChildIt it = find_child_iterator(func);

	return (it != children.end()) ? *it : nullptr;
}

TreeNode::ChildIt TreeNode::find_child_iterator(TreeNode_SP node)
{
	return std::find(children.begin(), children.end(), node);
}

TreeNode::ChildIt TreeNode::find_child_iterator(const std::function<bool(const TreeNode_SP&)>& func)
{
	return std::find_if(children.begin(), children.end(),
		[&func](const TreeNode_SP& child) {
			return func(child);
		});
}

void TreeNode::self_delete()
{
	auto p = parent.lock();
	if (p) {
		p->delete_children(self_node.lock());
	}
}

TreeNode_SP TreeNode::take_out_of_children(bool is_front)
{
	if (children.empty()) return nullptr;

	TreeNode_SP node = nullptr;
	if (is_front)
	{
		node = children.front();
		children.erase(children.begin());
	}
	else
	{
		node = children.back();
		children.pop_back();
	}
	node->set_parent(nullptr);	// 取出后，应当将父节点设置为空
	children_change();
	return node;
}