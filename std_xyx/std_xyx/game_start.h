#pragma once

#include "game.h"

class GameStart :public Game
{
public:
	GameStart() = default;
	~GameStart() = default;

	void on_enter();
	void on_scene_init() override;

	/*³¡¾°ÇÐ»»*/
	void exchange_scene(SceneType type) override;

private:
	Scene* start_menue_scene = nullptr;
};

