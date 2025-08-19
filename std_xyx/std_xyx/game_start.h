#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart();
	~GameStart();

	void on_enter();
	void on_exit();
	void on_scene_init() override;
};

