#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include <unordered_map>
#include <iostream>

#include "game_type.h"

/*资源管理器*/
class ResMgr
{
public:
	static ResMgr* instance();

	void load();
	Mix_Chunk* find_audio(const std::string& name);
	Mix_Music* find_music(const std::string& name);
	SDL_Texture* find_texture(const std::string& name);
	std::string removeFileExtension(const std::string& filename);
	std::string get_str_of_type(GameType type);
	// 释放所有资源
	void releaseAll();

private:
	ResMgr() = default;  // 私有构造
	~ResMgr() = default; // 私有析构

private:
	static ResMgr* manager;
	std::unordered_map<std::string, Mix_Chunk* > audio_pool;
	std::unordered_map<std::string, Mix_Music* > music_pool;
	std::unordered_map<std::string, SDL_Texture* > texture_pool;

};