#pragma once

#include "game.h"
/*��Ϸ�������Ҵ���*/
class GameXcz :public Game
{
public:
	GameXcz() = default;
	~GameXcz() = default;

	void on_init() override;
	void on_enter() override;
};

