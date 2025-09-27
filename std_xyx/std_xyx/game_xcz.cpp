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
	GameWnd::instance()->set_title(u8"提瓦特幸存者");
	current_scene_type = SceneType::MENU;
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("music_bgm"), -1);
}

void GameXcz::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::MENU:
		create_scene<XczMenuScene>(SceneType::MENU, "XczMenuScene");
		break;
	case SceneType::GAME:
		create_scene<XczGameScene>(SceneType::GAME, "XczGameScene");
		break;
	default:
		assert(false && "未知的 SceneType，无法创建场景");
		break;
	}
}