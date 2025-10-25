#pragma once
#include "game.h"
class GameZmdj :
    public Game
{
public:
	GameZmdj() = default;
	~GameZmdj() = default;

	GameZmdj(const std::string& id) : Game(id) {}
	GameZmdj(const std::string& id, int num) : Game(id, num) {}

	DEFINE_TYPE_NAME(GameZmdj);

	void on_init() override;
	void on_enter() override;
	virtual void create_target_scene() override;
};

