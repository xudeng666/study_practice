#pragma once
#include "game.h"
class GamePhf :
    public Game
{
public:
	GamePhf() = default;
	~GamePhf() = default;

	GamePhf(const std::string& id) : Game(id) {}
	GamePhf(const std::string& id, int num) : Game(id, num) {}

	DEFINE_TYPE_NAME(GamePhf);

	void on_init() override;
	void on_enter() override;
	virtual void create_target_scene() override;
};

