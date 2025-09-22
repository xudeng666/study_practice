#include "game_mgr.h"
#include "game_start.h"
#include "game_xcz.h"

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
	game_pool[GameType::START] = create_game<GameStart>("GameStart");
	game_pool[GameType::XCZ] = create_game<GameXcz>("GameXcz");
	/*game_pool[GameType::KDWS] = create_game<GameKdws>("GameKdws");
	game_pool[GameType::DLD] = create_game<GameDld>("GameDld");
	game_pool[GameType::ZMDJ] = create_game<GameZmdj>("GameZmdj");
	game_pool[GameType::PHF] = create_game<GamePhf>("GamePhf");*/

	current_type = GameType::START;

	on_enter();
}

void GameMgr::deinit()
{
	game_pool.clear();
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
	get_current_game()->on_exit();

	current_type = type;

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