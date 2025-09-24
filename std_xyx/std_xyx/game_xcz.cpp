#include "game_xcz.h"
#include "xcz_menu_scene.h"
#include "xcz_game_scene.h"
#include "res_mgr.h"
#include "game_wnd.h"

#include <assert.h>

void GameXcz::on_init()
{
}

void GameXcz::on_enter()
{
	GameWnd::instance()->set_title(u8"�������Ҵ���");
	current_scene_type = SceneType::MENU;
	create_target_scene();
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("music_bgm"), -1);
}

void GameXcz::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::MENU:
		Game::create_scene<XczMenuScene>(current_scene_type, "XczMenuScene");
		break;
	case SceneType::GAME:
		Game::create_scene<XczGameScene>(current_scene_type, "XczGameScene");
		break;
	default:
		assert(false && "δ֪�� SceneType���޷���������");
		break;
	}
}