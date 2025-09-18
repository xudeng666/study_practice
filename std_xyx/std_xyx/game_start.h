#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart() = default;
	GameStart(const std::string id);
	GameStart(const std::string id, const int num);
	~GameStart();

	void on_enter() override;
	void on_exit() override;
	void on_scene_init() override;
};

