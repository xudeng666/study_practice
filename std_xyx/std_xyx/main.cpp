
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include <chrono>
#include <thread>

#include "util.h"

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool is_quit = false;

void init();							// ��Ϸ�����ʼ��
void init_regions();					// ��ʼ���ɽ�������
void deinit();							// ��Ϸ���򷴳�ʼ��(�ͷ���Դ)
void on_update(float delta);			// �߼�����
void on_render(SDL_Renderer* renderer);	// ������Ⱦ
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

	window = SDL_CreateWindow(u8"����С��Ϸ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _WIN_W_, _WIN_H_, SDL_WINDOW_SHOWN);
	SDL_SetWindowTitle(window, "С��Ϸ");

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(SDL_DISABLE);//�������������

	//ResMgr::instance()->load(renderer);
	init_regions();

	//Mix_PlayChannel(-1, ResMgr::instance()->find_audio("bgm"), -1);
}

void init_regions()
{
	/*RegionMgr::instance()->add("delivery_driver_1", new DeliveryDriver(385, 142));
	RegionMgr::instance()->add("delivery_driver_2", new DeliveryDriver(690, 142));
	RegionMgr::instance()->add("delivery_driver_3", new DeliveryDriver(995, 142));

	RegionMgr::instance()->add("cola_bundle", new ColaBundle(300, 390));
	RegionMgr::instance()->add("sprite_bundle", new SpriteBundle(425, 390));
	RegionMgr::instance()->add("tb_bundle", new TbBundle(550, 418));

	RegionMgr::instance()->add("mb_box_bundle", new MbBoxBundle(225, 520));
	RegionMgr::instance()->add("bc_box_bundle", new BcBoxBundle(395, 520));
	RegionMgr::instance()->add("rcp_box_bundle", new RcpBoxBundle(565, 520));

	RegionMgr::instance()->add("microwave_oven_1", new MicrowaveOven(740, 400));
	RegionMgr::instance()->add("microwave_oven_2", new MicrowaveOven(975, 400));

	RegionMgr::instance()->add("takeout_box_1", new TakeoutBox(830, 580));
	RegionMgr::instance()->add("takeout_box_2", new TakeoutBox(935, 580));
	RegionMgr::instance()->add("takeout_box_3", new TakeoutBox(1040, 580));
	RegionMgr::instance()->add("takeout_box_4", new TakeoutBox(1145, 580));*/
}

void deinit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void on_update(float delta)
{
	//RegionMgr::instance()->on_update(delta);
}

void on_render(SDL_Renderer* renderer)
{
	//SDL_Rect rect_bg = { 0, 0, _W_, _H_ };
	//SDL_RenderCopy(renderer, ResMgr::instance()->find_texture("background"), nullptr, &rect_bg);

	//RegionMgr::instance()->on_render(renderer);
	//CursorMgr::instance()->on_render(renderer);
}

void mainloop()
{
	using namespace std::chrono;

	SDL_Event event;

	const nanoseconds frame_duration(1000000000 / _FPS_);
	steady_clock::time_point last_tick = steady_clock::now();

	while (!is_quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: is_quit = true; break;
			}
			//CursorMgr::instance()->on_input(event);
			//RegionMgr::instance()->on_input(event);
		}

		steady_clock::time_point frome_start = steady_clock::now();
		duration<float> delta = duration<float>(frome_start - last_tick);
		// ��������
		on_update(delta.count());

		// �����һ֡
		SDL_RenderClear(renderer);
		// ��Ⱦ��ͼ
		on_render(renderer);
		SDL_RenderPresent(renderer);

		last_tick = frome_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}
}