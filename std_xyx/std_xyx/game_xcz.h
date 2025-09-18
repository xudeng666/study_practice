#pragma once

#include "game.h"
/*游戏提瓦特幸存者*/
class GameXcz :public Game
{
public:
	GameXcz() = default;
	GameXcz(const std::string id);
	GameXcz(const std::string id, const int num);
	~GameXcz();

	void on_enter() override;
	void on_exit() override;
	void on_scene_init() override;
};

