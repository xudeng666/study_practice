#include "game_xcz.h"
#include "xcz_menu_scene.h"
#include "xcz_game_scene.h"
#include "res_mgr.h"
#include "game_wnd.h"

void GameXcz::on_init()
{
	scene_pool[SceneType::MENU] = std::make_shared<XczMenuScene>("XczMenuScene");
	scene_pool[SceneType::GAME] = std::make_shared<XczGameScene>("XczGameScene");
}

void GameXcz::on_enter()
{
	GameWnd::instance()->set_title(u8"ÌáÍßÌØÐÒ´æÕß");
	current_scene_type = SceneType::MENU;
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("music_bgm"), -1);
}
