/*”Œœ∑----¥Û¬“∂∑*/
#include "MenuScene.h"
#include "GamaScene.h"
#include "SelectorScene.h"
#include "SceneManager.h"

Scene* game_scene = nullptr;
Scene* menu_scene = nullptr;
Scene* selector_scene = nullptr;

SceneManager scene_manager;


int main()
{
	ExMessage msg;
	const int FPS = 60;
	initgraph(1280, 720, EX_SHOWCONSOLE);

	BeginBatchDraw();

	menu_scene = new MenuScene();
	game_scene = new GamaScene();
	selector_scene = new SelectorScene();

	scene_manager.set_current_scene(menu_scene);



	while (true)
	{
		DWORD stime = GetTickCount();

		while (peekmessage(&msg))
		{
			scene_manager.on_input(msg);
		}

		scene_manager.on_update();

		scene_manager.on_draw();

		FlushBatchDraw();
		DWORD etime = GetTickCount();
		DWORD dtime = etime - stime;
		if (dtime < 1000 / FPS)
		{
			Sleep(1000 / FPS - dtime);
		}
	}
	EndBatchDraw();
	return 0;
}