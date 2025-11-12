#include "game_phf.h"
#include "phf_game_scene.h"
#include "res_mgr.h"
#include "game_wnd.h"

#include <assert.h>

INIT_TYPE_NAME(GamePhf);

void GamePhf::on_init()
{
}

void GamePhf::on_enter()
{
	GameWnd::instance()->set_title(u8"拼好饭传奇");
	current_scene_type = SceneType::GAME;
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("music_bgm"), -1);
}

void GamePhf::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::GAME:
		create_scene<PhfGameScene>(SceneType::GAME, "PhfGameScene");
		break;
	default:
		assert(false && "未知的 SceneType，无法创建场景");
		break;
	}
}

