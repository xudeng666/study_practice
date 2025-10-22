#pragma once

#include "game_collision_box.h"

class CollisionMgr
{
public:
	static CollisionMgr* instance();

	void on_input(const SDL_Event& event);

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

	/// <summary>
	/// 清理所以碰撞箱
	/// </summary>
	void clear_all_box();
	/// <summary>
	/// 清理失效碰撞箱
	/// </summary>
	void clear_invalid();

	/*调试显示碰撞框体*/
	void onDebugRender();

private:
	static CollisionMgr* manager;

	std::vector<TreeNode_SP> box_list;
private:
	CollisionMgr();
	~CollisionMgr();

	/// <summary>
	/// 碰撞箱是否有效
	/// </summary>
	/// <param name="box">碰撞箱指针</param>
	/// <returns>true有效  false无效</returns>
	bool is_collider_valid(TreeNode_SP box);
};
