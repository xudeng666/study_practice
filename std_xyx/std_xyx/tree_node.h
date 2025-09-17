#pragma once

#include "game_obj.h"

#include <memory>
#include <list>


class TreeNode;

typedef std::shared_ptr<TreeNode> TreeNode_SP;      // 节点指针（强）
typedef std::unique_ptr<GameObj> GameObj_UP;        // 对象指针（专）
typedef std::weak_ptr<TreeNode> TreeNode_WP;        // 节点指针（弱）

class TreeNode:public std::enable_shared_from_this<TreeNode>
{
public:
	//构造
    TreeNode(GameObj_UP d);
	//析构
	~TreeNode() = default;
    // 禁用拷贝
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;
    // 允许移动
    TreeNode(TreeNode&&) = default;
    TreeNode& operator=(TreeNode&&) = default;
	//获取数据
    GameObj* get_obj();
    /*设置父节点*/
    void set_parent(TreeNode_SP p);
    /*获取父节点*/
    TreeNode_SP get_parent();
    /*移除(不删除)子节点*/
    TreeNode_SP remove_children(GameObj* obj);
    TreeNode_SP remove_children(TreeNode_SP node);
    TreeNode_SP remove_children(std::string id);
    /*删除子节点*/
    void delete_children(GameObj* obj);
    void delete_children(TreeNode_SP node);
    void delete_children(std::string id);
    /// <summary>
    /// 添加子节点（默认表尾添加）
    /// </summary>
    /// <param name="obj">节点智能指针</param>
    /// <param name="is_front">true/false 是否表头添加 默认false</param>
    void add_children(TreeNode_SP node, bool is_front = false);
    /// <summary>
    /// 遍历所有子对象
    /// </summary>
    /// <param name="func">外部传入的函数，参数为子对象的指针</param>
    void for_each_child(const std::function<void(TreeNode_SP)>& func);
    /// <summary>
    /// 子节点排序
    /// </summary>
    /// <param name="func">排序顺序函数</param>
    void sort_children(const std::function<bool(const TreeNode_SP&, const TreeNode_SP&)>& func);
    /// <summary>
    /// 删除符合条件的子节点
    /// </summary>
    /// <param name="func"></param>
    void remove_children_if(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// 清理子节点
    /// </summary>
    void clear_children();
    /// <summary>
    /// 获取子节点数量
    /// </summary>
    /// <returns>int</returns>
    int get_children_size();
    /// <summary>
    /// 查找子节点（直接）
    /// </summary>
    /// <param name="obj">GameObj*</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(GameObj* obj);
    /// <summary>
    /// 查找子节点（直接）
    /// </summary>
    /// <param name="id">string id</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(const std::string& id);
private:
    using ChildIt = std::list<TreeNode_SP>::iterator;
    /// <summary>
    /// 查找子节点it（直接）
    /// </summary>
    /// <param name="obj">GameObj*</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(GameObj* obj);
    /// <summary>
    /// 查找子节点it（直接）
    /// </summary>
    /// <param name="node">TreeNode_SP</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(TreeNode_SP node);
    /// <summary>
    /// 查找子节点it（直接）
    /// </summary>
    /// <param name="id">string id</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(const std::string& id);

private:
	GameObj_UP obj;
    TreeNode_WP parent;
	std::list<TreeNode_SP> children;
};