#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart();
	~GameStart();

	void on_enter() override;
	void on_exit() override;
	void on_scene_init() override;
};

