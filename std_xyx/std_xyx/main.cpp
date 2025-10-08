
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

#include "util.h"
#include "game_mgr.h"
#include "res_mgr.h"
#include "collision_mgr.h"
#include "tree_mgr.h"
#include "game_wnd.h"
#include "event_mgr.h"

void init();							// 游戏程序初始化
void deinit();							// 游戏程序反初始化(释放资源)
void on_update(float delta);			// 逻辑更新
void on_render();						// 画面渲染
void mainloop();						// 游戏主循环

int main(int argc, char* argv[])
{
	init();
	mainloop();
	deinit();

	return 0;
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(32);

	GameMgr::instance()->init();
}

void deinit()
{
	EventMgr::instance()->destroy();
	CollisionMgr::instance()->destroy();
	TreeMgr::instance()->destroy();
	ResMgr::instance()->destroy();
	GameMgr::instance()->deinit();

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void on_update(float delta)
{
	GameMgr::instance()->on_update(delta);
}

void on_render()
{
	GameMgr::instance()->on_render();
}

void mainloop()
{
	using namespace std::chrono;

	SDL_Event event;

	const nanoseconds frame_duration(1000000000 / _FPS_);
	steady_clock::time_point last_tick = steady_clock::now();

	while (GameMgr::instance()->get_is_run())
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:	GameMgr::instance()->set_is_run(false);	break;
			}
			// GameMgr::instance()->on_input(event);
			EventMgr::instance()->dispatch_sdl_event(event);
		}

		EventMgr::instance()->execute_event();

		steady_clock::time_point frome_start = steady_clock::now();
		duration<float> delta = duration<float>(frome_start - last_tick);
		// 处理数据
		on_update(delta.count());

		// 清空上一帧
		SDL_RenderClear(GameWnd::instance()->get_renderer());
		// 渲染绘图
		on_render();
		SDL_RenderPresent(GameWnd::instance()->get_renderer());

		last_tick = frome_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}
}