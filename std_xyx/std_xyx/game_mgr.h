#pragma once

#include "game.h"
#include "game_type.h"

/*��Ϸ������*/
class GameMgr
{
public:
	static GameMgr* instance();
	/*���õ�ǰ��Ϸ*/
	void set_current_game(Game* game);
	/*��Ϸ�л�*/
	void exchange_scene(GameType type);
	/*��������*/
	void on_update(int delta);
	/*������Ⱦ��ͼ*/
	void on_render(const Camera* camera);
	/*�����������*/
	void on_input(const SDL_Event& event);
	/*��ȡ��Ϸ����*/
	bool get_is_run();
	/*������Ϸ����*/
	bool set_is_run(bool run);

private:
	GameMgr() = default;
	~GameMgr() = default;

private:
	static GameMgr* manager;

	bool is_run = true;

	GameType current_type = GameType::START;
	/*��ǰ��Ϸ*/
	Game* current_game = nullptr;

	Game* start_game = nullptr;
	Game* xcz_game = nullptr;
	Game* kdws_game = nullptr;
	Game* dld_game = nullptr;
	Game* zmdj_game = nullptr;
	Game* phf_game = nullptr;
};

