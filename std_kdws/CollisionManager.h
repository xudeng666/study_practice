#pragma once
#include "CollisionBox.h"

class CollisionManager
{
public:
	static CollisionManager* instance();

	/**
	* @brief ´´½¨Åö×²Ïä
	* @return ·µ»ØÅö×²ÏäÖ¸Õë
	*/
	CollisionBox* creatCollisionBox();

	/**
	* @brief É¾³ıÊÍ·ÅÅö×²Ïä
	* @param box Åö×²ÏäÖ¸Õë
	*/
	void destroyCollisionBox(CollisionBox* box);

	/**
	* @brief Åö×²±éÀú
	*/
	void processCollide();
	/*µ÷ÊÔÏÔÊ¾Åö×²¿òÌå*/
	void onDebugRender();


private:
	static CollisionManager* manager;

	std::vector<CollisionBox*> box_list;
private:
	CollisionManager();
	~CollisionManager();
};

