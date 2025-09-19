#pragma once

#include "game.h"
/*游戏提瓦特幸存者*/
class GameXcz :public Game
{
public:
	GameXcz() = default;
	~GameXcz() = default;

	void on_init() override;
	void on_enter() override;
};

