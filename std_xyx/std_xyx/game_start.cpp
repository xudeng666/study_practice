#include "game_start.h"
#include "start_menue_scene.h"
//#include <iostream>

void GameStart::on_scene_init()
{
	scene_pool[SceneType::MENUE] = new StartMenueScene();
}

void GameStart::on_enter()
{
	current_scene_type = SceneType::MENUE;
	Game::on_enter();
}
void GameStart::on_exit()
{
	Game::on_exit();
}

GameStart::GameStart() 
{
	on_scene_init();
}

GameStart::~GameStart()
{
}

//void GameStart::exchange_scene(SceneType type)
//{
//}