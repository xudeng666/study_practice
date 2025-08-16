#include "game_start.h"
#include "start_menue_scene.h"


void GameStart::on_enter()
{
	current_scene_type = SceneType::MENUE;
	current_scene = start_menue_scene;
	Game::on_enter();
}


void GameStart::on_scene_init()
{
	start_menue_scene = new StartMenueScene();
}

void GameStart::exchange_scene(SceneType type)
{
}