#pragma once

#include "game.h"
/*��Ϸ�������Ҵ���*/
class GameXcz :public Game
{
public:
	GameXcz();
	~GameXcz();

	void on_enter() override;
	void on_exit() override;
	void on_scene_init() override;
};

