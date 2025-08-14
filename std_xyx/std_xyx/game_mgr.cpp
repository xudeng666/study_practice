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

/*���õ�ǰ��Ϸ*/
void GameMgr::set_current_game(Game* game)
{
	current_game = game;
	current_game->on_enter();
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
	// ��Ϸ�л�
	switch (current_type)
	{
	case GameType::START:	current_game = start_game;	break;
	case GameType::XCZ:		current_game = xcz_game;	break;
	case GameType::KDWS:	current_game = kdws_game;	break;
	case GameType::DLD:		current_game = dld_game;	break;
	case GameType::ZMDJ:	current_game = zmdj_game;	break;
	case GameType::PHF:		current_game = phf_game;	break;
	}
	// ����Ϸ��ʼ��
	current_game->on_enter();
}

/*��������*/
void GameMgr::on_update(int delta)
{
	current_game->on_update(delta);
}
/*������Ⱦ��ͼ*/
void GameMgr::on_render(const Camera* camera)
{
	current_game->on_render(camera);
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
bool GameMgr::set_is_run(bool run)
{
	is_run = run;
}