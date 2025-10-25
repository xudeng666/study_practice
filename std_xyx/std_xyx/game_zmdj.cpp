#include "game_zmdj.h"
#include "zmdj_game_scene.h"
#include "res_mgr.h"
#include "game_wnd.h"

#include <assert.h>

INIT_TYPE_NAME(GameZmdj);

void GameZmdj::on_init()
{
}

void GameZmdj::on_enter()
{
	GameWnd::instance()->set_title(u8"������");
	current_scene_type = SceneType::GAME;
	Game::on_enter();
	Mix_PlayMusic(ResMgr::instance()->find_music("bgm"), -1);
}

void GameZmdj::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::GAME:
		create_scene<ZmdjGameScene>(SceneType::GAME, "ZmdjGameScene");
		break;
	default:
		assert(false && "δ֪�� SceneType���޷���������");
		break;
	}
}
