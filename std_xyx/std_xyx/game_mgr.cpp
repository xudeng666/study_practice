#include "game_mgr.h"
#include "game_start.h"
#include "game_xcz.h"

#include <assert.h>

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
	create_game<GameStart>(GameType::START, "GameStart");

	current_type = GameType::START;

	on_enter();
}

void GameMgr::deinit()
{
	game_pool.clear();
	delete manager;
	manager = nullptr;
}

std::shared_ptr<Game> GameMgr::get_current_game()
{
	return game_pool[current_type];
}

GameType GameMgr::get_current_type()
{
	return current_type;
}

/*��Ϸ�л�*/
void GameMgr::exchange_game(GameType type)
{
	if (type == current_type) return;
	// ֻ����ӿ�ʼ��Ϸ������Ϸ�����л�
	if (type != GameType::START && current_type != GameType::START)
	{
		return;
	}
	// �˳���ǰ��Ϸ
	auto last_game = get_current_game();
	if (last_game) {
		last_game->on_exit();			// ������Ϸ���˳��߼����ͷų�������Դ��
		game_pool.erase(current_type);	// ����Ϸ��ɾ������Ϸ
	}
	current_type = type;
	switch (current_type)
	{
	case GameType::START:
		create_game<GameStart>(current_type, "GameStart");
		break;
	case GameType::XCZ:
		create_game<GameXcz>(current_type, "GameXcz");
		break;
	/*case GameType::KDWS:
		create_game<GameKdws>(current_type, "GameKdws");
		break;
	case GameType::DLD:
		create_game<GameDld>(current_type, "GameDld");
		break;
	case GameType::ZMDJ:
		create_game<GameZmdj>(current_type, "GameZmdj");
		break;
	case GameType::PHF:
		create_game<GamePhf>(current_type, "GamePhf");
		break;*/
	default:
		assert(false && "δ֪�� GameType���޷���������");
		break;
	}
	get_current_game()->on_enter();
}

/*�����л�*/
void GameMgr::exchange_scene(SceneType type)
{
	get_current_game()->exchange_scene(type);
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