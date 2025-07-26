#define SDL_MAIN_HANDLED


#define PI 3.14159265
#define _W_ 1280
#define _H_ 720
#define _FPS_ 60

#include "bullet.h"
#include "chicken.h"
#include "chicken_fast.h"
#include "chicken_medium.h"
#include "chicken_slow.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <chrono>
#include <thread>
#include <string>
#include <algorithm>

Camera* camera = nullptr;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

bool is_quit = false;							// �Ƿ��˳�����
SDL_Texture* tex_heart = nullptr;				// ����ֵͼ������
SDL_Texture* tex_bullet = nullptr;				// �ӵ�����
SDL_Texture* tex_battery = nullptr;				// ��̨��������
SDL_Texture* tex_crosshair = nullptr;			// ���׼������
SDL_Texture* tex_background = nullptr;			// ����ͼ����
SDL_Texture* tex_barrel_idle = nullptr;			// �ڹ�Ĭ��״̬����

Atlas atlas_barrel_fire;						// �ڹܿ��𶯻�ͼ��
Atlas atlas_chicken_fast;						// ���ٽ�ʬ����ͼ��
Atlas atlas_chicken_medium;						// ���ٽ�ʬ����ͼ��
Atlas atlas_chicken_slow;						// ���ٽ�ʬ����ͼ��
Atlas atlas_explosion;							// ��ʬ������ը����ͼ��

Mix_Music* music_bgm = nullptr;					// ��������
Mix_Music* music_loss = nullptr;				// ��Ϸʧ������

Mix_Chunk* sound_hurt = nullptr;				// ����ֵ������Ч
Mix_Chunk* sound_fire_1 = nullptr;				// ������Ч1
Mix_Chunk* sound_fire_2 = nullptr;				// ������Ч2
Mix_Chunk* sound_fire_3 = nullptr;				// ������Ч3
Mix_Chunk* sound_explosion = nullptr;			// ��ʬ������ը��Ч

TTF_Font* font = nullptr;						// �÷��ı�����

int hp = 10;									// ����ֵ
int score = 0;									// ��Ϸ�÷�
std::vector<Bullet> bullet_list;				// �ӵ��б�
std::vector<Chicken*> chicken_list;				// ��ʬ���б�

int num_per_gen = 2;							// ÿ�����ɵļ�����
Timer timer_generate;							// ��ʬ�����ɶ�ʱ��
Timer timer_increase_num_per_gen;				// ����ÿ������������ʱ��

Vector2 pos_crosshair;							// ׼��λ��
double angle_barrel = 0;						// �ڹ���ת�Ƕ�
float barrel_speed = 0.04f;						// �ڹ�����
const Vector2 pos_battery = { 640, 600 };		// ��̨��������λ��
const Vector2 pos_barrel = { 592, 585 };		// �ڹ�����תĬ��λ��
const SDL_FPoint center_barrel = { 48, 25 };	// �ڹ���ת���ĵ�����

bool is_cool_down = true;						// �Ƿ���ȴ����
bool is_fire_key_down = false;					// ������Ƿ���
Animation animation_barrel_fire;				// �ڹܿ��𶯻�

void load_resources();					// ������Ϸ��Դ
void unload_resources();				// ж����Ϸ��Դ
void init();							// ��Ϸ�����ʼ��
void deinit();							// ��Ϸ���򷴳�ʼ��(�ͷ���Դ)
void on_update(float delta);			// �߼�����
void on_render(const Camera& camera);	// ������Ⱦ
void mainloop();						// ��Ϸ��ѭ��

int main(int argc, char** argv)
{
	init();
	mainloop();
	deinit();

	return 0;
}

void load_resources()
{
	tex_heart = IMG_LoadTexture(renderer, "resources/heart.png");
	tex_bullet = IMG_LoadTexture(renderer, "resources/bullet.png");
	tex_battery = IMG_LoadTexture(renderer, "resources/battery.png");
	tex_crosshair = IMG_LoadTexture(renderer, "resources/crosshair.png");
	tex_background = IMG_LoadTexture(renderer, "resources/background.png");
	tex_barrel_idle = IMG_LoadTexture(renderer, "resources/barrel_idle.png");

	atlas_barrel_fire.load(renderer, "resources/barrel_fire_%d.png", 3);
	atlas_chicken_fast.load(renderer, "resources/chicken_fast_%d.png", 4);
	atlas_chicken_medium.load(renderer, "resources/chicken_medium_%d.png", 6);
	atlas_chicken_slow.load(renderer, "resources/chicken_slow_%d.png", 8);
	atlas_explosion.load(renderer, "resources/explosion_%d.png", 5);

	music_bgm = Mix_LoadMUS("resources/bgm.mp3");
	music_loss = Mix_LoadMUS("resources/loss.mp3");

	sound_hurt = Mix_LoadWAV("resources/hurt.wav");
	sound_fire_1 = Mix_LoadWAV("resources/fire_1.wav");
	sound_fire_2 = Mix_LoadWAV("resources/fire_2.wav");
	sound_fire_3 = Mix_LoadWAV("resources/fire_3.wav");
	sound_explosion = Mix_LoadWAV("resources/explosion.wav");

	font = TTF_OpenFont("resources/IPix.ttf", 28);
}

void unload_resources()
{
	SDL_DestroyTexture(tex_heart);
	SDL_DestroyTexture(tex_bullet);
	SDL_DestroyTexture(tex_battery);
	SDL_DestroyTexture(tex_crosshair);
	SDL_DestroyTexture(tex_background);
	SDL_DestroyTexture(tex_barrel_idle);

	Mix_FreeMusic(music_bgm);
	Mix_FreeMusic(music_loss);

	Mix_FreeChunk(sound_hurt);
	Mix_FreeChunk(sound_fire_1);
	Mix_FreeChunk(sound_fire_2);
	Mix_FreeChunk(sound_fire_3);
	Mix_FreeChunk(sound_explosion);
}

void init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_AllocateChannels(32);

	window = SDL_CreateWindow(u8"����-������", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _W_, _H_, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_ShowCursor(SDL_DISABLE);//�������������

	load_resources();

	camera = new Camera(renderer);
	timer_generate.set_one_shot(false);
	timer_generate.set_wait_time(1.5f);
	timer_generate.set_on_timeout([&]()
		{
			for (int i = 0; i < num_per_gen; i++)
			{
				int val = getIntRand(0, 99);
				Chicken* chicken = nullptr;
				if (val < 50)       // 50%
					chicken = new ChickenSlow();
				else if (val < 80)  // 30%
					chicken = new ChickenMedium();
				else                // 20%
					chicken = new ChickenFast();
				chicken_list.push_back(chicken);
			}
		});

	timer_increase_num_per_gen.set_one_shot(false);
	timer_increase_num_per_gen.set_wait_time(8.0f);
	timer_increase_num_per_gen.set_on_timeout([&]()
		{ num_per_gen += 1; });

	animation_barrel_fire.set_loop(false);
	animation_barrel_fire.set_interval(barrel_speed);
	animation_barrel_fire.set_center(center_barrel);
	animation_barrel_fire.add_frame(&atlas_barrel_fire);
	animation_barrel_fire.set_on_finished([&]()
		{ is_cool_down = true; });
	animation_barrel_fire.set_position({ 718, 610 });

	Mix_PlayMusic(music_bgm, -1);//���ű������֣�-1Ϊѭ��
}

void deinit()
{
	delete camera;

	unload_resources();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void on_update(float delta)
{
	timer_generate.on_update(delta);
	timer_increase_num_per_gen.on_update(delta);

	// �����ӵ��б�
	for (Bullet& bullet : bullet_list)
		bullet.on_update(delta);

	// ���½�ʬ�����󲢴����ӵ���ײ
	for (Chicken* chicken : chicken_list)
	{
		chicken->on_update(delta);

		for (Bullet& bullet : bullet_list)
		{
			if (!chicken->check_alive() || bullet.can_remove())
				continue;

			const Vector2& pos_bullet = bullet.get_position();
			const Vector2& pos_chicken = chicken->get_position();
			static const Vector2 size_chicken = { 30, 40 };

			if (checkPointToRect(pos_bullet.x, pos_bullet.y,
				pos_chicken.x - size_chicken.x / 2,
				pos_chicken.x + size_chicken.x / 2,
				pos_chicken.y - size_chicken.y / 2,
				pos_chicken.y + size_chicken.y / 2))
			{
				score += 1;
				bullet.on_hit();
				chicken->on_hurt();
			}
		}

		if (!chicken->check_alive())
			continue;

		if (chicken->get_position().y >= _H_)
		{
			chicken->make_invalid();
			Mix_PlayChannel(-1, sound_hurt, 0);
			hp -= 1;
		}
	}

	animation_barrel_fire.set_interval(max(0.01f, barrel_speed * (1000 - score) / 1000));

	bullet_list.erase(std::remove_if(bullet_list.begin(), bullet_list.end(),
		[](const Bullet& bullet)				// T date ָ��vector��Ԫ�ص����ͺͱ���������
		{
			return bullet.can_remove();
		}),
		bullet_list.end()
	);

	chicken_list.erase(std::remove_if(chicken_list.begin(), chicken_list.end(),
		[](Chicken* chicken)				// T date ָ��vector��Ԫ�ص����ͺͱ���������
		{
			return chicken->can_remove() ? (delete chicken, true) : false;
		}),
		chicken_list.end()
	);

	std::sort(chicken_list.begin(), chicken_list.end(), 
		[](const Chicken* chicken_1, const Chicken* chicken_2)
		{return chicken_1->get_position().y < chicken_2->get_position().y;});

	// �������ڿ����߼�
	if (!is_cool_down)
	{
		camera->shake(3.0f, 0.1f);
		animation_barrel_fire.on_update(delta);
	}

	// ������˲���߼�
	if (is_cool_down && is_fire_key_down)
	{
		animation_barrel_fire.reset();
		is_cool_down = false;

		static const float length_barrel = 105;                  // �ڹܳ���
		static const Vector2 pos_barrel_center = { 640, 610 };   // �ڹ�ê������λ��

		bullet_list.emplace_back(angle_barrel);                  // �����µ��ӵ�����
		Bullet& bullet = bullet_list.back();
		double angle_bullet = angle_barrel + getIntRand(-5,5);  // �� 10�� ��Χ�����ƫ��
		double radians = getRadiansByAngle(angle_bullet);
		Vector2 direction = { (float)std::cos(radians), (float)sin(radians) };
		bullet.set_position(pos_barrel_center + direction * length_barrel);

		switch (getIntRand(0, 2))
		{
		case 0: Mix_PlayChannel(-1, sound_fire_1, 0); break;
		case 1: Mix_PlayChannel(-1, sound_fire_2, 0); break;
		case 2: Mix_PlayChannel(-1, sound_fire_3, 0); break;
		}
	}

	camera->on_update(delta);

	// �����Ϸ�Ƿ����
	if (hp <= 0)
	{
		is_quit = true;
		Mix_HaltMusic();
		Mix_PlayMusic(music_loss, 0);
		std::string msg = u8"��Ϸ���յ÷֣�" + std::to_string(score);
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, u8"��Ϸ����", msg.c_str(), window);
	}
}

void on_render(const Camera& camera)
{
	int w_bg, h_bg;
	SDL_QueryTexture(tex_background, nullptr, nullptr, &w_bg, &h_bg);
	const SDL_FRect rect_bg = { (_W_ - w_bg) / 2,(_H_ - h_bg) / 2,(float)w_bg,(float)h_bg };
	camera.render_texture(tex_background, nullptr, &rect_bg, 0, nullptr);

	for (Chicken* chicken : chicken_list)
	{
		chicken->on_render(camera);
	}

	for (Bullet bullet : bullet_list)
	{
		bullet.on_render(camera);
	}

	int w_pj, h_pj;
	SDL_QueryTexture(tex_battery, nullptr, nullptr, &w_pj, &h_pj);
	const SDL_FRect rect_bj = { pos_battery.x - w_pj / 2,pos_battery.y - h_pj / 2,(float)w_pj,(float)h_pj };
	camera.render_texture(tex_battery, nullptr, &rect_bj, 0, nullptr);

	int w_pt, h_pt;
	SDL_QueryTexture(tex_barrel_idle, nullptr, nullptr, &w_pt, &h_pt);
	const SDL_FRect rect_bt = { pos_barrel.x, pos_barrel.y, (float)w_pt, (float)h_pt };
	if (is_cool_down)
	{
		camera.render_texture(tex_barrel_idle, nullptr, &rect_bt, angle_barrel, &center_barrel);
	}
	else
	{
		animation_barrel_fire.set_rotation(angle_barrel);
		animation_barrel_fire.on_render(camera);
	}

	int w_hp, h_hp;
	SDL_QueryTexture(tex_heart, nullptr, nullptr, &w_hp, &h_hp);
	for (size_t i = 0; i < hp; i++)
	{
		const SDL_Rect rect_hp = { 15 + w_hp * i,15,(float)w_hp,(float)h_hp };
		SDL_RenderCopy(renderer, tex_heart, nullptr, &rect_hp);
	}
	if (font)
	{
		std::string str_score = "SCORE: " + std::to_string(score);
		SDL_Surface* suf_score_bg = TTF_RenderUTF8_Blended(font, str_score.c_str(), { 55, 55, 55, 255 });
		SDL_Surface* suf_score_fg = TTF_RenderUTF8_Blended(font, str_score.c_str(), { 255, 255, 255, 255 });
		SDL_Texture* tex_score_bg = SDL_CreateTextureFromSurface(renderer, suf_score_bg);
		SDL_Texture* tex_score_fg = SDL_CreateTextureFromSurface(renderer, suf_score_fg);
		SDL_Rect rect_dst_score = { _W_ - suf_score_bg->w - 15, 15, suf_score_bg->w, suf_score_bg->h };
		SDL_RenderCopy(renderer, tex_score_bg, nullptr, &rect_dst_score);
		rect_dst_score.x -= 2; rect_dst_score.y -= 2;
		SDL_RenderCopy(renderer, tex_score_fg, nullptr, &rect_dst_score);
		SDL_DestroyTexture(tex_score_bg); SDL_DestroyTexture(tex_score_fg);
		SDL_FreeSurface(suf_score_bg); SDL_FreeSurface(suf_score_fg);
	}

	int w_zx, h_zx;
	SDL_QueryTexture(tex_crosshair, nullptr, nullptr, &w_zx, &h_zx);
	const SDL_FRect rect_zx = { pos_crosshair.x - w_zx / 2,pos_crosshair.y - h_zx / 2,(float)w_zx,(float)h_zx };
	camera.render_texture(tex_crosshair, nullptr, &rect_zx, 0, nullptr);
}

void mainloop()
{
	using namespace std::chrono;

	SDL_Event event;

	const nanoseconds frame_duration(1000000000 / _FPS_);
	steady_clock::time_point last_tick = steady_clock::now();

	while (!is_quit)
	{
		// ������Ϣ
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				is_quit = true;
				break;
			case SDL_MOUSEMOTION:
			{
				pos_crosshair.x = (float)event.motion.x;
				pos_crosshair.y = (float)event.motion.y;
				Vector2 dir = pos_crosshair - pos_battery;
				angle_barrel = getAngleByRadians(std::atan2(dir.y, dir.x));
				break;
			}
			case SDL_MOUSEBUTTONDOWN:
				is_fire_key_down = true;
				break;
			case SDL_MOUSEBUTTONUP:
				is_fire_key_down = false;
				break;
			}
		}

		steady_clock::time_point frome_start = steady_clock::now();
		duration<float> delta = duration<float>(frome_start - last_tick);
		// ��������
		on_update(delta.count());

		// ��Ⱦ��ͼ
		on_render(*camera);

		SDL_RenderPresent(renderer);

		last_tick = frome_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frome_start);
		if (sleep_duration > nanoseconds(0))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}
}