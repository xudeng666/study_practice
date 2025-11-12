#pragma once

#include "game_type.h"

#include <memory>
#include <vector>
#include <string>
#include <functional>

class GameObj;

typedef std::shared_ptr<GameObj> TreeNode_SP;      // 节点指针（强）
typedef std::weak_ptr<GameObj> TreeNode_WP;        // 节点指针（弱）

class TreeNode:public std::enable_shared_from_this<TreeNode>
{
public:
    /*创建节点(默认创建游戏对象节点)*/
    template <typename T, typename... Args>
    static std::shared_ptr<T> create_obj(Args&&... args)
    {
        std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
        node->set_node_type(NodeType::GAMENODE);
        node->set_self_node(node);
        node->on_init();
        //std::cout << "create_obj: " << "GAMENODE: "  /*<< args[0]*/ << std::endl;
        return node;
    }

    /*创建指定类型节点*/
    template <typename T, typename... Args>
    static std::shared_ptr<T> create_obj(NodeType type, Args&&... args)
    {
        std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
        node->set_node_type(type);
        node->set_self_node(node);
        node->on_init();
        std::cout << "create_obj: " << "NO_GAMENODE:  " /*<< args[0]*/ << std::endl;
        return node;
    }

    //判断类型
    template <typename T> bool is_type()const
    {
        return typeid(*this) == typeid(T);
    }

    //获取数据
    template <typename T> T* get_obj_as()
    {
        if (this->is_type<T>())
        {
            return  static_cast<T*>(this);
        }
        return nullptr;
    }
    //获取数据
    template <typename T> const T* get_obj_as() const
    {
        if (this->is_type<T>())
        {
            return  static_cast<T*>(this);
        }
        return nullptr;
    }

public:
    TreeNode() = default;
	//析构
	virtual ~TreeNode() = default;
    // 禁用拷贝
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;
    // 允许移动
    TreeNode(TreeNode&&) = default;
    TreeNode& operator=(TreeNode&&) = default;

    /*设置父节点*/
    void set_parent(TreeNode_SP p);
    /*设置被添加回调*/
    virtual void set_added_fun(const std::function<void()>& func);
    /*执行被添加回调*/
    void run_added_fun();
    /*获取父节点*/
    TreeNode_SP get_parent();
    /*设置自身节点*/
    void set_self_node(TreeNode_SP self);
    /*获取自身点*/
    TreeNode_SP get_self_node();
    /*设置节点类型*/
    void set_node_type(NodeType type);
    /*设置节点类型*/
    NodeType get_node_type();
    /*移除(不删除)子节点*/
    TreeNode_SP remove_children(TreeNode_SP node);
    /*移除(不删除)条件子节点*/
    TreeNode_SP remove_children(const std::function<bool(const TreeNode_SP&)>& func);
    /*删除子节点*/
    void delete_children(TreeNode_SP node);
    /*删除条件子节点*/
    void delete_children(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// 添加子节点（默认表尾添加）
    /// </summary>
    /// <param name="obj">节点智能指针</param>
    /// <param name="is_front">true/false 是否表头添加 默认false</param>
    /// <returns>true/false  成功/失败</returns>
    bool add_children(TreeNode_SP node, bool is_front = false);
    /// <summary>
    /// 遍历所有子对象
    /// </summary>
    /// <param name="func">执行函数</param>
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
    /// 查找直属子节点
    /// </summary>
    /// <param name="func">条件函数 bool</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// 取出子列表成员
    /// </summary>
    /// <param name="is_front">默认从末尾取出</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP take_out_of_children(bool is_front = false);
    /// <summary>
    /// 删除本节点
    /// </summary>
    void self_delete();
protected:
    using ChildIt = std::vector<TreeNode_SP>::iterator;
    /// <summary>
    /// 查找直属子节点it
    /// </summary>
    /// <param name="node">TreeNode_SP</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(TreeNode_SP node);
    /// <summary>
    /// 查找直属子节点it
    /// </summary>
    /// <param name="func">条件函数 bool</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(const std::function<bool(const TreeNode_SP&)>& func);

protected:
    TreeNode_WP parent;
    TreeNode_WP self_node;
	std::vector<TreeNode_SP> children;
    NodeType node_type;
    std::function<void()> on_added_func = nullptr;
};