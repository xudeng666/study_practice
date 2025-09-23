#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart() = default;
	~GameStart() = default;

	GameStart(const std::string& id) : Game(id) {}
	GameStart(const std::string& id, int num) : Game(id, num) {}

	void on_init() override;
	void on_enter() override;
};

