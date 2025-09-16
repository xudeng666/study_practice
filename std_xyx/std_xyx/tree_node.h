#pragma once

#include "game_obj.h"

#include <memory>
#include <list>



class TreeNode
{
public:
	//构造
	TreeNode(std::unique_ptr<GameObj> d) : obj(std::move(d)) {}
	//析构
	~TreeNode() = default;
	//获取数据
	GameObj* get_obj()
	{
		return obj.get();
	}

    /*设置父节点*/
    void set_parent(TreeNodePtr p);
    /*获取父节点*/
    TreeNodePtr get_parent();
    /*移除(不删除)子节点*/
    TreeNodePtr remove_children(GameObj* obj);
    TreeNodePtr remove_children(ObjPtr obj);
    TreeNodePtr remove_children(TreeNodePtr node);
    TreeNodePtr remove_children(std::string id);
    /*删除子节点*/
    void delete_children(GameObj* obj);
    void delete_children(ObjPtr obj);
    void delete_children(TreeNodePtr node);
    void delete_children(std::string id);
    /// <summary>
    /// 添加子节点（默认表尾添加）
    /// </summary>
    /// <param name="obj">节点智能指针</param>
    /// <param name="is_front">true/false 是否表头添加 默认false</param>
    void add_children(TreeNodePtr node, bool is_front = false);
    /// <summary>
    /// 遍历所有子对象
    /// </summary>
    /// <param name="func">外部传入的函数，参数为子对象的裸指针</param>
    void for_each_child(const std::function<void(GameObj*)>& func);
    /// <summary>
    /// 子节点排序
    /// </summary>
    /// <param name="func">排序顺序函数</param>
    void sort_children(const std::function<bool(const TreeNodePtr&, const TreeNodePtr&)>& func);
    /// <summary>
    /// 删除符合条件的子节点
    /// </summary>
    /// <param name="func"></param>
    void remove_children_if(const std::function<bool(const TreeNodePtr&)>& func);
    /// <summary>
    /// 清理子节点
    /// </summary>
    void clear_children();
    /// <summary>
    /// 获取子节点数量
    /// </summary>
    /// <returns>int</returns>
    int get_children_size();

private:
	ObjPtr obj;
    ParentPtr parent;
	std::list<TreeNodePtr> children;
};

typedef std::shared_ptr<TreeNode> TreeNodePtr;
typedef std::unique_ptr<GameObj> ObjPtr;
typedef std::weak_ptr<GameObj> ParentPtr;
