#pragma once

#include "game.h"
/*��Ϸ�������Ҵ���*/
class GameXcz :public Game
{
public:
	GameXcz();
	~GameXcz();

	void on_enter();
	void on_exit();
	void on_scene_init() override;
};

