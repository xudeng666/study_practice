#pragma once

#include "game_obj.h"

#include <memory>
#include <list>


class TreeNode;

typedef std::shared_ptr<TreeNode> TreeNode_SP;      // �ڵ�ָ�루ǿ��
typedef std::unique_ptr<GameObj> GameObj_UP;        // ����ָ�루ר��
typedef std::weak_ptr<TreeNode> TreeNode_WP;        // �ڵ�ָ�루����

class TreeNode:public std::enable_shared_from_this<TreeNode>
{
public:
	//����
    TreeNode(GameObj_UP d);
	//����
	~TreeNode() = default;
    // ���ÿ���
    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;
    // �����ƶ�
    TreeNode(TreeNode&&) = default;
    TreeNode& operator=(TreeNode&&) = default;
	//��ȡ����
    GameObj* get_obj();
    /*���ø��ڵ�*/
    void set_parent(TreeNode_SP p);
    /*��ȡ���ڵ�*/
    TreeNode_SP get_parent();
    /*�Ƴ�(��ɾ��)�ӽڵ�*/
    TreeNode_SP remove_children(GameObj* obj);
    TreeNode_SP remove_children(TreeNode_SP node);
    TreeNode_SP remove_children(std::string id);
    /*ɾ���ӽڵ�*/
    void delete_children(GameObj* obj);
    void delete_children(TreeNode_SP node);
    void delete_children(std::string id);
    /// <summary>
    /// ����ӽڵ㣨Ĭ�ϱ�β��ӣ�
    /// </summary>
    /// <param name="obj">�ڵ�����ָ��</param>
    /// <param name="is_front">true/false �Ƿ��ͷ��� Ĭ��false</param>
    void add_children(TreeNode_SP node, bool is_front = false);
    /// <summary>
    /// ���������Ӷ���
    /// </summary>
    /// <param name="func">�ⲿ����ĺ���������Ϊ�Ӷ����ָ��</param>
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
    /// �����ӽڵ㣨ֱ�ӣ�
    /// </summary>
    /// <param name="obj">GameObj*</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(GameObj* obj);
    /// <summary>
    /// �����ӽڵ㣨ֱ�ӣ�
    /// </summary>
    /// <param name="id">string id</param>
    /// <returns>TreeNode_SP</returns>
    TreeNode_SP find_child(const std::string& id);
private:
    using ChildIt = std::list<TreeNode_SP>::iterator;
    /// <summary>
    /// �����ӽڵ�it��ֱ�ӣ�
    /// </summary>
    /// <param name="obj">GameObj*</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(GameObj* obj);
    /// <summary>
    /// �����ӽڵ�it��ֱ�ӣ�
    /// </summary>
    /// <param name="node">TreeNode_SP</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(TreeNode_SP node);
    /// <summary>
    /// �����ӽڵ�it��ֱ�ӣ�
    /// </summary>
    /// <param name="id">string id</param>
    /// <returns>ChildIt</returns>
    ChildIt find_child_iterator(const std::string& id);

private:
	GameObj_UP obj;
    TreeNode_WP parent;
	std::list<TreeNode_SP> children;
};