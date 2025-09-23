#include "tree_node.h"
#include "game_obj.h"

#include <assert.h>

template <typename T, typename... Args>
std::shared_ptr<T> TreeNode::create_obj(Args&&... args)
{
	std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
	node->on_init();
	node->set_self_node(node);
	return node;
}

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

TreeNode_SP TreeNode::remove_children(TreeNode_SP node)
{
	auto it = find_child_iterator(node);
	if (it == children.end()) return nullptr;
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	removedObj->parent.reset();
	return removedObj;
}

TreeNode_SP TreeNode::remove_children(const std::function<bool(const TreeNode_SP&)>& func)
{
	auto it = find_child_iterator(func);
	if (it == children.end()) return nullptr;
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	removedObj->parent.reset();
	return removedObj;
}

void TreeNode::delete_children(TreeNode_SP node)
{
	auto it = find_child_iterator(node);
	if (it != children.end())
	{
		(*it)->parent.reset();
		children.erase(it);
	}
}

void TreeNode::delete_children(const std::function<bool(const TreeNode_SP&)>& func)
{
	auto it = find_child_iterator(func);
	if (it != children.end())
	{
		(*it)->parent.reset();
		children.erase(it);
	}
}

void TreeNode::add_children(TreeNode_SP node, bool is_front)
{
	if (!node)
	{
		assert(false && "Cannot add null node as child");
		return;
	}
	if (!node->parent.expired()) {
		node = node->get_parent()->remove_children(node);
	}

	// 步骤2：设置当前节点为新父节点
	node->set_parent(self_node.lock());

	// 步骤3：将子节点的 unique_ptr 移动到当前节点的 children 列表
	is_front ? children.push_front(std::move(node)) : children.push_back(std::move(node));
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

	children.sort([&func](const TreeNode_SP& a, const TreeNode_SP& b) {
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

	children.remove_if([&func](const TreeNode_SP& child) {
		if (!child)
		{
			return true;
		}
		return func(child);
		});
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