#pragma once

#include "game_type.h"

#include <memory>
#include <list>
#include <string>
#include <functional>

class GameObj;

typedef std::shared_ptr<GameObj> TreeNode_SP;      // �ڵ�ָ�루ǿ��
typedef std::weak_ptr<GameObj> TreeNode_WP;        // �ڵ�ָ�루����

class TreeNode:public std::enable_shared_from_this<TreeNode>
{
public:
    /*�����ڵ�(Ĭ�ϴ�����Ϸ����ڵ�)*/
    template <typename T, typename... Args>
    static std::shared_ptr<T> create_obj(Args&&... args)
    {
        std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
        node->set_node_type(NodeType::GAMENODE);
        node->on_init();
        node->set_self_node(node);
        return node;
    }

    /*����ָ�����ͽڵ�*/
    template <typename T, typename... Args>
    static std::shared_ptr<T> create_obj(NodeType type, Args&&... args)
    {
        std::shared_ptr<T> node = std::make_shared<T>(std::forward<Args>(args)...);
        node->set_node_type(type);
        node->on_init();
        node->set_self_node(node);
        return node;
    }

    //�ж�����
    template <typename T> bool is_type()const
    {
        return typeid(*this) == typeid(T);
    }

    //��ȡ����
    template <typename T> T* get_obj_as()
    {
        if (this->is_type<T>())
        {
            return  static_cast<T*>(this);
        }
        return nullptr;
    }
    //��ȡ����
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
	//����
	virtual ~TreeNode() = default;
    // ���ÿ���
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;
    // �����ƶ�
    TreeNode(TreeNode&&) = default;
    TreeNode& operator=(TreeNode&&) = default;

    /*���ø��ڵ�*/
    void set_parent(TreeNode_SP p);
    /*��ȡ���ڵ�*/
    TreeNode_SP get_parent();
    /*��������ڵ�*/
    void set_self_node(TreeNode_SP self);
    /*��ȡ�����*/
    TreeNode_SP get_self_node();
    /*���ýڵ�����*/
    void set_node_type(NodeType type);
    /*���ýڵ�����*/
    NodeType get_node_type();
    /*�Ƴ�(��ɾ��)�ӽڵ�*/
    TreeNode_SP remove_children(TreeNode_SP node);
    /*�Ƴ�(��ɾ��)�����ӽڵ�*/
    TreeNode_SP remove_children(const std::function<bool(const TreeNode_SP&)>& func);
    /*ɾ���ӽڵ�*/
    void delete_children(TreeNode_SP node);
    /*ɾ�������ӽڵ�*/
    void delete_children(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// ����ӽڵ㣨Ĭ�ϱ�β��ӣ�
    /// </summary>
    /// <param name="obj">�ڵ�����ָ��</param>
    /// <param name="is_front">true/false �Ƿ��ͷ��� Ĭ��false</param>
    void add_children(TreeNode_SP node, bool is_front = false);
    /// <summary>
    /// ���������Ӷ���
    /// </summary>
    /// <param name="func">ִ�к���</param>
    void for_each_child(const std::function<void(TreeNode_SP)>& func);
    /// <summary>
    /// �ӽڵ�����
    /// </summary>
    /// <param name="func">����˳����</param>
    void sort_children(const std::function<bool(const TreeNode_SP&, const TreeNode_SP&)>& func);
    /// <summary>
    /// ɾ�������������ӽڵ�
    /// </summary>
    /// <param name="func"></param>
    void remove_children_if(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// �����ӽڵ�
    /// </summary>
    void clear_children();
    /// <summary>
    /// ��ȡ�ӽڵ�����
    /// </summary>
    /// <returns>int</returns>
    int get_children_size();
    /// <summary>
    /// ����ֱ���ӽڵ�
    /// </summary>
    /// <param name="func">�������� bool</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(const std::function<bool(const TreeNode_SP&)>& func);
    /// <summary>
    /// ȡ�����б��Ա
    /// </summary>
    /// <param name="is_front">Ĭ�ϴӱ�ͷȡ��</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP take_out_of_children(bool is_front = true);
    /// <summary>
    /// ɾ�����ڵ�
    /// </summary>
    void self_delete();
protected:
    using ChildIt = std::list<TreeNode_SP>::iterator;
    /// <summary>
    /// ����ֱ���ӽڵ�it
    /// </summary>
    /// <param name="node">TreeNode_SP</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(TreeNode_SP node);
    /// <summary>
    /// ����ֱ���ӽڵ�it
    /// </summary>
    /// <param name="func">�������� bool</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(const std::function<bool(const TreeNode_SP&)>& func);

protected:
    TreeNode_WP parent;
    TreeNode_WP self_node;
	std::list<TreeNode_SP> children;
    NodeType node_type;
};