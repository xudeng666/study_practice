#include "game_start.h"
#include "start_menue_scene.h"
#include "game_wnd.h"

void GameStart::on_scene_init()
{
	scene_pool[SceneType::MENUE] = std::make_shared<StartMenueScene>("StartMenueScene");
}

void GameStart::on_enter()
{
	GameWnd::instance()->set_title(u8"–°”Œœ∑");
	current_scene_type = SceneType::MENUE;
	Game::on_enter();
}
void GameStart::on_exit()
{
	Game::on_exit();
}

GameStart::GameStart(const std::string id) :Game(id)
{
	on_scene_init();
}

GameStart::GameStart(const std::string id, const int num) :Game(id, num)
{
	on_scene_init();
}

GameStart::~GameStart()
{
}