
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

#include "util.h"
#include "game_mgr.h"

void init();							// ��Ϸ�����ʼ��
void deinit();							// ��Ϸ���򷴳�ʼ��(�ͷ���Դ)
void on_update(float delta);			// �߼�����
void on_render();						// ������Ⱦ
void mainloop();						// ��Ϸ��ѭ��

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
			GameMgr::instance()->on_input(event);
		}

		steady_clock::time_point frome_start = steady_clock::now();
		duration<float> delta = duration<float>(frome_start - last_tick);
		// ��������
		on_update(delta.count());

		// �����һ֡
		SDL_RenderClear(GameMgr::instance()->get_renderer());
		// ��Ⱦ��ͼ
		on_render();
		SDL_RenderPresent(GameMgr::instance()->get_renderer());

		last_tick = frome_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}
}