#pragma once

#include "game.h"
/*��Ϸ�������Ҵ���*/
class GameXcz :public Game
{
public:
	GameXcz() = default;
	~GameXcz() = default;

	GameXcz(const std::string& id) : Game(id) {}
	GameXcz(const std::string& id, int num) : Game(id, num) {}

	DEFINE_TYPE_NAME(GameXcz);

	void on_init() override;
	void on_enter() override;
	virtual void create_target_scene() override;
};