#pragma once

#include "game.h"
/*��Ϸ�������Ҵ���*/
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

