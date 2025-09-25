#pragma once

#include "game_obj.h"

class TreeMgr
{
public:
	static TreeMgr* instance();

	/// <summary>
	/// ���Ҷ���
	/// </summary>
	/// <param name="id">std::string ����ID</param>
	/// <param name="node">TreeNode_SP ��ʼ�ڵ�</param>
	/// <returns>TreeNode_SP ����ָ��</returns>
	TreeNode_SP find_obj(std::string id, TreeNode_SP start_node = nullptr);

	// ��ȡ���ڵ�
	TreeNode_SP get_root_node();
	// ��ȡ�����ڵ�
	TreeNode_SP get_bg_node();
	// ��ȡ��Ϸ�ڵ�
	TreeNode_SP get_game_node();
	// ��ȡUI�ڵ�
	TreeNode_SP get_ui_node();
	// �½��㼶�ڵ�
	TreeNode_SP create_layer_node(const std::string& id);
	// �½����ڵ�
	TreeNode_SP create_root_node(const std::string& id);
	// �ͷ����нڵ�
	void release_all();
	// �ͷ�������Ϸ��ڵ�
	void release_all_game();

	/// <summary>
	/// ǰ�������������ȣ�
	/// �ȸ�����
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	/// <param name="check_display">�Ƿ�������� true/false ��/��</param>
	void pre_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback, bool check_display);
	/// <summary>
	/// ���������������ȣ�
	/// ���Ӻ�
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	/// <param name="check_display">�Ƿ�������� true/false ��/��</param>
	void post_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback, bool check_display);

	/// <summary>
	/// ���������������ȣ�
	/// �����˳��
	/// </summary>
	/// <param name="current_node">������ʼ�ڵ�</param>
	/// <param name="callback">�ص�����</param>
	/// <param name="check_display">�Ƿ�������� true/false ��/��</param>
	void level_order_traversal(TreeNode_SP current_node, const std::function<void(TreeNode_SP)>& callback, bool check_display);
private:
	TreeMgr();
	~TreeMgr();

private:
	static TreeMgr* manager;

	// ��Ŀ¼
	TreeNode_SP root_node = nullptr;
	// �����ڵ�
	TreeNode_WP bg_node;
	// ��Ϸ����ڵ�
	TreeNode_WP game_node;
	// UI�ڵ�
	TreeNode_WP ui_node;
};

