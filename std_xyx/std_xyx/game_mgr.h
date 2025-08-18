#pragma once

#include "game.h"
#include "game_type.h"

/*��Ϸ������*/
class GameMgr
{
public:
	static GameMgr* instance();
	/*��ʼ��*/
	void init();
	/*�˳���Ϸ*/
	void deinit();
	/*��ȡ��ǰ��Ϸ*/
	Game* get_current_game();
	/*��ȡ��ǰ��Ϸ����*/
	GameType get_current_type();
	/*��Ϸ�л�*/
	void exchange_scene(GameType type);
	/*��Ϸ��ʼ��*/
	void on_enter();
	/*��������*/
	void on_update(int delta);
	/*������Ⱦ��ͼ*/
	void on_render();
	/*�����������*/
	void on_input(const SDL_Event& event);
	/*��ȡ��Ϸ����*/
	bool get_is_run();
	/*������Ϸ����*/
	void set_is_run(bool run);
	/*��ȡ�����*/
	Camera* get_camera();
	/*��ȡ��Ⱦ��*/
	SDL_Renderer* get_renderer();

private:
	GameMgr() = default;
	~GameMgr() = default;

private:
	static GameMgr* manager;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	Camera* camera = nullptr;

	bool is_run = true;

	GameType current_type = GameType::START;

	std::unordered_map<GameType, Game*> game_pool;
};

