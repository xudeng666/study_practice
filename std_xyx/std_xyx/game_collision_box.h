#pragma once

#include "game_obj.h"

class CollisionMgr;

class GameCollisionBox :
    public GameObj
{
	friend class CollisionMgr;
public:
	GameCollisionBox(const std::string& id) : GameObj(id) {}
	GameCollisionBox(const std::string& id, int num) : GameObj(id, num) {}

	void on_update(float delta) override;
	void on_render() override;

	DEFINE_TYPE_NAME(GameCollisionBox);

	/*�����Ƿ�������ײ���*/
	void set_collision_enabled(bool flag);
	/*����������ײ��*/
	void set_layer_src(CollisionLayer layer);
	/*���öԷ���ײ��*/
	void set_layer_dst(CollisionLayer layer);
	/*������ײ�ص�����*/
	void set_call_back(std::function<void()> call_back);

private:
	GameCollisionBox() = default;
	virtual ~GameCollisionBox() = default;

private:
	// �Ƿ�������ײ���
	bool collision_enabled = true;
	// ��ײ��Ļص�����
	std::function<void()> call_back = nullptr;
	// ������ײ��
	CollisionLayer layer_src = CollisionLayer::NONE;
	// Ŀ����ײ��
	CollisionLayer layer_dst = CollisionLayer::NONE;
};

INIT_TYPE_NAME(GameCollisionBox);