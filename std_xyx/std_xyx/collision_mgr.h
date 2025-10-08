#pragma once

#include "game_collision_box.h"

class CollisionMgr
{
public:
	static CollisionMgr* instance();

	/**
	* @brief 创建碰撞箱
	* @return 返回碰撞箱指针
	*/
	TreeNode_SP creatCollisionBox(std::string id);
	TreeNode_SP creatCollisionBox(std::string id, int num);

	/**
	* @brief 删除释放碰撞箱
	* @param box 碰撞箱指针
	*/
	void destroyCollisionBox(TreeNode_SP box);
	/**
	* @brief 销毁管理器
	*/
	void destroy();

	/**
	* @brief 碰撞遍历
	*/
	void processCollide();
	/*
	* 判定两个碰撞箱是否碰撞
	*/
	bool is_collision(TreeNode_SP box_t, TreeNode_SP box_p);
	/*调试显示碰撞框体*/
	void onDebugRender();

private:
	static CollisionMgr* manager;

	std::vector<TreeNode_SP> box_list;
private:
	CollisionMgr();
	~CollisionMgr();
};

