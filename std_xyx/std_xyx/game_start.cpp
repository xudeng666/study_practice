#include "game_start.h"
#include "start_menu_scene.h"
#include "game_wnd.h"

#include <assert.h>

void GameStart::on_init()
{
}

void GameStart::on_enter()
{
	GameWnd::instance()->set_title(u8"С��Ϸ");
	current_scene_type = SceneType::MENU;
	create_target_scene();
	Game::on_enter();
}

void GameStart::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::MENU:
		Game::create_scene<StartMenuScene>(current_scene_type, "StartMenuScene");
		break;
	default:
		assert(false && "δ֪�� SceneType���޷���������");
		break;
	}
}