#include "game_start.h"
#include "start_menu_scene.h"
#include "game_wnd.h"

#include <assert.h>

void GameStart::on_init()
{
}

void GameStart::on_enter()
{
	GameWnd::instance()->set_title(u8"小游戏");
	current_scene_type = SceneType::MENU;
	Game::on_enter();
}

void GameStart::create_target_scene()
{
	switch (current_scene_type)
	{
	case SceneType::MENU:
		create_scene<StartMenuScene>(SceneType::MENU, "StartMenuScene");
		break;
	default:
		assert(false && "未知的 SceneType，无法创建场景");
		break;
	}
}