#include "game_mgr.h"
#include "game_start.h"

#include <iostream>

GameMgr* GameMgr::manager = nullptr;

GameMgr* GameMgr::instance()
{
	if (!manager)
	{
		manager = new GameMgr();
	}
	return manager;
}

void GameMgr::init()
{
	window = SDL_CreateWindow(u8"С��Ϸ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _WIN_W_, _WIN_H_, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	camera = new Camera(renderer);

	game_pool[GameType::START] = new GameStart();
	/*game_pool[GameType::XCZ] = new GameStart();
	game_pool[GameType::KDWS] = new GameStart();
	game_pool[GameType::DLD] = new GameStart();
	game_pool[GameType::ZMDJ] = new GameStart();
	game_pool[GameType::PHF] = new GameStart();*/

	current_type = GameType::START;

	on_enter();
}

void GameMgr::deinit()
{
	// �ͷ���Ϸ�б�
	for (auto& [name, game] : game_pool) {
		delete game;
	}
	game_pool.clear();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete camera;
}

Game* GameMgr::get_current_game()
{
	return game_pool[current_type];
}

GameType GameMgr::get_current_type()
{
	return current_type;
}

/*��Ϸ�л�*/
void GameMgr::exchange_scene(GameType type)
{
	if (type == current_type) return;
	// ֻ����ӿ�ʼ��Ϸ������Ϸ�����л�
	if (type != GameType::START && current_type != GameType::START)
	{
		return;
	}
	// �˳���ǰ��Ϸ
	get_current_game()->on_exit();

	current_type = type;

	on_enter();
}

/*��Ϸ��ʼ��*/
void GameMgr::on_enter()
{
	get_current_game()->on_enter();
}

/*��������*/
void GameMgr::on_update(float delta)
{
	get_current_game()->on_update(delta);
}
/*������Ⱦ��ͼ*/
void GameMgr::on_render()
{
	get_current_game()->on_render();
}
/*�����������*/
void GameMgr::on_input(const SDL_Event& event)
{
	get_current_game()->on_input(event);
}
/*��ȡ��Ϸ����*/
bool GameMgr::get_is_run()
{
	return is_run;
}
/*������Ϸ����*/
void GameMgr::set_is_run(bool run)
{
	is_run = run;
}
/*��ȡ�����*/
Camera* GameMgr::get_camera()
{
	return camera;
}
/*��ȡ��Ⱦ��*/
SDL_Renderer* GameMgr::get_renderer()
{
	return renderer;
}