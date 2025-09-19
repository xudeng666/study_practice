#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart() = default;
	~GameStart() = default;

	void on_init() override;
	void on_enter() override;
};

