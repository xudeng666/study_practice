#include "game_xcz.h"
#include "xcz_menue_scene.h"
//#include "xcz_game_scene.h"

void GameXcz::on_scene_init()
{
	scene_pool[SceneType::MENUE] = new XczMenueScene();
	//scene_pool[SceneType::GAME] = new XczGameScene();
}

void GameXcz::on_enter()
{
	current_scene_type = SceneType::MENUE;
	Game::on_enter();
}
void GameXcz::on_exit()
{
	Game::on_exit();
}

GameXcz::GameXcz()
{
	on_scene_init();
}

GameXcz::~GameXcz() {}
