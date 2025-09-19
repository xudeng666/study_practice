#include "game_start.h"
#include "start_menue_scene.h"
#include "game_wnd.h"

void GameStart::on_init()
{
	scene_pool[SceneType::MENUE] = std::make_shared<StartMenueScene>("StartMenueScene");
}

void GameStart::on_enter()
{
	GameWnd::instance()->set_title(u8"п║сно╥");
	current_scene_type = SceneType::MENUE;
	Game::on_enter();
}