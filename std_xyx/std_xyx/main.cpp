
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

#include "util.h"
#include "game_mgr.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Camera* camera = nullptr;

void init();							// 游戏程序初始化
void deinit();							// 游戏程序反初始化(释放资源)
void on_update(float delta);			// 逻辑更新
void on_render(Camera* camera);			// 画面渲染
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

	window = SDL_CreateWindow(u8"集合小游戏", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _WIN_W_, _WIN_H_, SDL_WINDOW_SHOWN);
	SDL_SetWindowTitle(window, "小游戏");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	camera = new Camera(renderer);
}

void deinit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete camera;

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void on_update(float delta)
{
	GameMgr::instance()->on_update(delta);
}

void on_render(Camera* camera)
{
	GameMgr::instance()->on_render(camera);
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
			GameMgr::instance()->on_input(event);
		}

		steady_clock::time_point frome_start = steady_clock::now();
		duration<float> delta = duration<float>(frome_start - last_tick);
		// 处理数据
		on_update(delta.count());

		// 清空上一帧
		SDL_RenderClear(renderer);
		// 渲染绘图
		on_render(camera);
		SDL_RenderPresent(renderer);

		last_tick = frome_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}
}