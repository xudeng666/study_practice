#include "game_xcz.h"
#include "xcz_menu_scene.h"
#include "xcz_game_scene.h"
#include "res_mgr.h"
#include "game_wnd.h"

void GameXcz::on_init()
{
	Game::create_scene<XczMenuScene>(SceneType::MENU, "XczMenuScene");
	Game::create_scene<XczGameScene>(SceneType::GAME, "XczGameScene");
}

void GameXcz::on_enter()
{
	GameWnd::instance()->set_title(u8"ÌáÍßÌØÐÒ´æÕß");
	current_scene_type = SceneType::MENU;
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("music_bgm"), -1);
}
