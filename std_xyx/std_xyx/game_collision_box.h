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

	/*设置是否启用碰撞检测*/
	void set_collision_enabled(bool flag);
	/*设置自身碰撞层*/
	void set_layer_src(CollisionLayer layer);
	/*设置对方碰撞层*/
	void set_layer_dst(CollisionLayer layer);
	/*设置碰撞回调函数*/
	void set_call_back(std::function<void()> call_back);

private:
	GameCollisionBox() = default;
	virtual ~GameCollisionBox() = default;

private:
	// 是否启用碰撞检测
	bool collision_enabled = true;
	// 碰撞后的回调函数
	std::function<void()> call_back = nullptr;
	// 自身碰撞层
	CollisionLayer layer_src = CollisionLayer::NONE;
	// 目标碰撞层
	CollisionLayer layer_dst = CollisionLayer::NONE;
};

INIT_TYPE_NAME(GameCollisionBox);