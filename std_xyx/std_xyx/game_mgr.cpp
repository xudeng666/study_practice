#include "game_mgr.h"

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

	GameMgr::instance()->get_current_game()->on_load();
}

void GameMgr::deinit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	delete camera;
}

/*���õ�ǰ��Ϸ*/
void GameMgr::set_current_game(Game* game)
{
	current_game = game;
	current_game->on_enter();
}

Game* GameMgr::get_current_game()
{
	switch (current_type)
	{
	case GameType::START:	return start_game;	break;
	case GameType::XCZ:		return xcz_game;	break;
	case GameType::KDWS:	return kdws_game;	break;
	case GameType::DLD:		return dld_game;	break;
	case GameType::ZMDJ:	return zmdj_game;	break;
	case GameType::PHF:		return phf_game;	break;
	}
	return nullptr;
}


GameType GameMgr::get_current_type()
{
	return current_type;
}

/*��Ϸ�л�*/
void GameMgr::exchange_scene(GameType type)
{
	if (type == current_type) return;

	if (type != GameType::START && current_type != GameType::START)
	{
		return;
	}

	current_type = type;
	// �˳���ǰ��Ϸ
	current_game->on_exit();

	current_game = get_current_game();

	current_game->on_enter();
}

/*��������*/
void GameMgr::on_update(int delta)
{
	current_game->on_update(delta);
}
/*������Ⱦ��ͼ*/
void GameMgr::on_render()
{
	current_game->on_render();
}
/*�����������*/
void GameMgr::on_input(const SDL_Event& event)
{
	current_game->on_input(event);
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