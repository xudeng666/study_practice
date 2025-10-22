#pragma once

#include "game_collision_box.h"

class CollisionMgr
{
public:
	static CollisionMgr* instance();

	void on_input(const SDL_Event& event);

	/**
	* @brief ������ײ��
	* @return ������ײ��ָ��
	*/
	TreeNode_SP creatCollisionBox(std::string id);
	TreeNode_SP creatCollisionBox(std::string id, int num);

	/**
	* @brief ɾ���ͷ���ײ��
	* @param box ��ײ��ָ��
	*/
	void destroyCollisionBox(TreeNode_SP box);
	/**
	* @brief ���ٹ�����
	*/
	void destroy();

	/**
	* @brief ��ײ����
	*/
	void processCollide();
	/*
	* �ж�������ײ���Ƿ���ײ
	*/
	bool is_collision(TreeNode_SP box_t, TreeNode_SP box_p);

	/// <summary>
	/// ����������ײ��
	/// </summary>
	void clear_all_box();
	/// <summary>
	/// ����ʧЧ��ײ��
	/// </summary>
	void clear_invalid();

	/*������ʾ��ײ����*/
	void onDebugRender();

private:
	static CollisionMgr* manager;

	std::vector<TreeNode_SP> box_list;
private:
	CollisionMgr();
	~CollisionMgr();

	/// <summary>
	/// ��ײ���Ƿ���Ч
	/// </summary>
	/// <param name="box">��ײ��ָ��</param>
	/// <returns>true��Ч  false��Ч</returns>
	bool is_collider_valid(TreeNode_SP box);
};
