#pragma once

#include "game.h"

/*��Ϸ������*/
class GameMgr
{
public:
	static GameMgr* instance();
	
	template <typename T, typename... Args>
	std::shared_ptr<T> create_game(GameType type, Args&&... args)
	{
		std::shared_ptr<T> game = std::make_shared<T>(std::forward<Args>(args)...);
		game->on_init();
		game_pool[type] = game;
		return game;
	}

	/*��ʼ��*/
	void init();
	/*�˳���Ϸ*/
	void deinit();
	/*��ȡ��ǰ��Ϸ*/
	std::shared_ptr<Game> get_current_game();
	/*��ȡ��ǰ��Ϸ����*/
	GameType get_current_type();
	/*��Ϸ�л�*/
	void exchange_game(GameType type);
	/*�����л�*/
	void exchange_scene(SceneType type);

	/*��Ϸ��ʼ��*/
	void on_enter();
	/*��������*/
	void on_update(float delta);
	/*������Ⱦ��ͼ*/
	void on_render();
	/*�����������*/
	void on_input(const SDL_Event& event);
	/*��ȡ��Ϸ����*/
	bool get_is_run();
	/*������Ϸ����*/
	void set_is_run(bool run);

private:
	GameMgr() = default;
	~GameMgr() = default;

private:
	static GameMgr* manager;

	bool is_run = true;

	GameType current_type = GameType::START;

	std::unordered_map<GameType, std::shared_ptr<Game>> game_pool;
};
