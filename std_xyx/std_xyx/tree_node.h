#pragma once

#include "game_obj.h"

#include <memory>
#include <list>



class TreeNode
{
public:
	//����
	TreeNode(std::unique_ptr<GameObj> d) : obj(std::move(d)) {}
	//����
	~TreeNode() = default;
	//��ȡ����
	GameObj* get_obj()
	{
		return obj.get();
	}

    /*���ø��ڵ�*/
    void set_parent(TreeNodePtr p);
    /*��ȡ���ڵ�*/
    TreeNodePtr get_parent();
    /*�Ƴ�(��ɾ��)�ӽڵ�*/
    TreeNodePtr remove_children(GameObj* obj);
    TreeNodePtr remove_children(ObjPtr obj);
    TreeNodePtr remove_children(TreeNodePtr node);
    TreeNodePtr remove_children(std::string id);
    /*ɾ���ӽڵ�*/
    void delete_children(GameObj* obj);
    void delete_children(ObjPtr obj);
    void delete_children(TreeNodePtr node);
    void delete_children(std::string id);
    /// <summary>
    /// ����ӽڵ㣨Ĭ�ϱ�β��ӣ�
    /// </summary>
    /// <param name="obj">�ڵ�����ָ��</param>
    /// <param name="is_front">true/false �Ƿ��ͷ��� Ĭ��false</param>
    void add_children(TreeNodePtr node, bool is_front = false);
    /// <summary>
    /// ���������Ӷ���
    /// </summary>
    /// <param name="func">�ⲿ����ĺ���������Ϊ�Ӷ������ָ��</param>
    void for_each_child(const std::function<void(GameObj*)>& func);
    /// <summary>
    /// �ӽڵ�����
    /// </summary>
    /// <param name="func">����˳����</param>
    void sort_children(const std::function<bool(const TreeNodePtr&, const TreeNodePtr&)>& func);
    /// <summary>
    /// ɾ�������������ӽڵ�
    /// </summary>
    /// <param name="func"></param>
    void remove_children_if(const std::function<bool(const TreeNodePtr&)>& func);
    /// <summary>
    /// �����ӽڵ�
    /// </summary>
    void clear_children();
    /// <summary>
    /// ��ȡ�ӽڵ�����
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
