#include "game_start.h"
#include "start_menu_scene.h"
#include "game_wnd.h"

void GameStart::on_init()
{
	Game::create_scene<StartMenuScene>(SceneType::MENU, "StartMenuScene");
}

void GameStart::on_enter()
{
	GameWnd::instance()->set_title(u8"п║сно╥");
	current_scene_type = SceneType::MENU;
	Game::on_enter();
}