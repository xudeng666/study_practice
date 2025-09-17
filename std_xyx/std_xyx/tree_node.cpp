#include "tree_node.h"

#include <assert.h>


TreeNode::TreeNode(GameObj_UP d) : obj(std::move(d))
{
	assert(obj != nullptr && "GameObj cannot be null");
}

GameObj* TreeNode::get_obj()
{
	return obj.get();
}

void TreeNode::set_parent(TreeNode_SP p)
{
	parent = p;
}

TreeNode_SP TreeNode::get_parent()
{
	return parent.lock();
}

TreeNode_SP TreeNode::remove_children(GameObj* obj)
{
	auto it = find_child_iterator(obj);
	if (it == children.end()) return nullptr;
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	removedObj->parent.reset();
	return removedObj;
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

TreeNode_SP TreeNode::remove_children(std::string id)
{
	auto it = find_child_iterator(id);
	if (it == children.end()) return nullptr;
	TreeNode_SP removedObj = std::move(*it);
	children.erase(it);
	removedObj->parent.reset();
	return removedObj;
}

void TreeNode::delete_children(GameObj* obj)
{
	auto it = find_child_iterator(obj);
	if (it != children.end())
	{
		(*it)->parent.reset();
		children.erase(it);
	}
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
void TreeNode::delete_children(std::string id)
{
	auto it = find_child_iterator(id);
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
	node->set_parent(shared_from_this());

	// 步骤3：将子节点的 unique_ptr 移动到当前节点的 children 列表
	is_front ? children.push_front(std::move(node)) : children.push_back(std::move(node));
}

void TreeNode::for_each_child(const std::function<void(GameObj*)>& func)
{
	if (!func) return;

	for (const auto& child_ptr : children) {
		if (child_ptr) {
			func(child_ptr->get_obj());
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

TreeNode_SP TreeNode::find_child(GameObj* obj)
{
	auto it = find_child_iterator(obj);
	if (it != children.end() && *it) {
		return *it;
	}
	return nullptr;
}

TreeNode_SP TreeNode:: find_child(const std::string& id)
{
	auto it = find_child_iterator(id);
	if (it != children.end() && *it) {
		return *it;
	}
	return nullptr;
}

TreeNode::ChildIt TreeNode:: find_child_iterator(GameObj* obj)
{
	return std::find_if(children.begin(), children.end(),
		[obj](const TreeNode_SP& child) {
			return child->get_obj() == obj;
		});
}

TreeNode::ChildIt TreeNode:: find_child_iterator(TreeNode_SP node)
{
	return std::find(children.begin(), children.end(), node);
}

TreeNode::ChildIt TreeNode:: find_child_iterator(const std::string& id)
{
	return std::find_if(children.begin(), children.end(),
		[id](const TreeNode_SP& child) {
			return child->get_obj()->get_ID() == id;
		});
}