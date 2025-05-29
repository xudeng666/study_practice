#pragma once
#include "CollisionBox.h"

class CollisionManager
{
public:
	static CollisionManager* instance();

	/**
	* @brief ������ײ��
	* @return ������ײ��ָ��
	*/
	CollisionBox* creatCollisionBox();

	/**
	* @brief ɾ���ͷ���ײ��
	* @param box ��ײ��ָ��
	*/
	void destroyCollisionBox(CollisionBox* box);

	/**
	* @brief ��ײ����
	*/
	void processCollide();
	/*������ʾ��ײ����*/
	void onDebugRender();


private:
	static CollisionManager* manager;

	std::vector<CollisionBox*> box_list;
private:
	CollisionManager();
	~CollisionManager();
};

