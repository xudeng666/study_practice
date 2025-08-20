#pragma once

#include "game_collision_box.h"

class CollisionMgr
{
public:
	static CollisionMgr* instance();

	/**
	* @brief ������ײ��
	* @return ������ײ��ָ��
	*/
	GameCollisionBox* creatCollisionBox();

	/**
	* @brief ɾ���ͷ���ײ��
	* @param box ��ײ��ָ��
	*/
	void destroyCollisionBox(GameCollisionBox* box);

	/**
	* @brief ��ײ����
	*/
	void processCollide();
	/*
	* �ж�������ײ���Ƿ���ײ
	*/
	bool is_collision(GameCollisionBox* box_t, GameCollisionBox* box_p);
	/*������ʾ��ײ����*/
	void onDebugRender();

private:
	static CollisionMgr* manager;

	std::vector<GameCollisionBox*> box_list;
private:
	CollisionMgr();
	~CollisionMgr();
};

