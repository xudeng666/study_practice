#include "res_mgr.h"

#include <SDL_image.h>
#include <filesystem>
#include <iostream>

ResMgr* ResMgr::manager = nullptr;

ResMgr* ResMgr::instance()
{
	if (!manager)
	{
		manager = new ResMgr();
	}
	return manager;
}

void ResMgr::load(SDL_Renderer* renderer, GameType type)
{
	using namespace std::filesystem;

	const std::string resRoot = "resources/" + getStrByGameType(type);

	for (const auto& entry:recursive_directory_iterator(resRoot))
	{
		if (entry.is_regular_file())
		{
			if (!entry.is_regular_file()) continue;

			const path& p = entry.path();

			std::string ext = p.extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // 扩展名转小写

			std::string keyStr = p.stem().u8string();						// 路径正文下划线替换
			std::replace(keyStr.begin(), keyStr.end(), '/', '_');
			std::replace(keyStr.begin(), keyStr.end(), '\\', '_');

			if (ext == ".png")
			{
				SDL_Texture* texture = IMG_LoadTexture(renderer, p.u8string().c_str());
				if (texture)
				{
					texture_pool[keyStr] = texture;
				}
				else
				{
					std::cout << "图片资源加载失败: " << p << "，错误：" << IMG_GetError() << std::endl;
				}
			}
			else if (ext == ".mp3" || ext == ".wav")
			{
				if (keyStr.find("music") != std::string::npos)
				{
					Mix_Music* music = Mix_LoadMUS(p.u8string().c_str());
					if (music)
					{
						music_pool[keyStr] = music;
					}
					else
					{
						std::cout << "音乐资源加载失败: " << p << "，错误：" << Mix_GetError() << std::endl;
					}
				}
				else
				{
					Mix_Chunk* audio = Mix_LoadWAV(p.u8string().c_str());
					if (audio)
					{
						audio_pool[keyStr] = audio;
					}
					else
					{
						std::cout << "音效资源加载失败: " << p << "，错误：" << Mix_GetError() << std::endl;
					}
				}
			}
		}
	}
}

void ResMgr::releaseAll()
{
	// 释放背景音乐
	for (auto& [name, music] : music_pool) {
		Mix_FreeMusic(music);
	}
	music_pool.clear();

	// 释放音效
	for (auto& [name, audio] : audio_pool) {
		Mix_FreeChunk(audio);
	}
	audio_pool.clear();

	// 释放纹理
	for (auto& [name, tex] : texture_pool) {
		SDL_DestroyTexture(tex);
	}
	texture_pool.clear();
}

Mix_Chunk* ResMgr::find_audio(const std::string& name)
{
	return audio_pool[name];
}

Mix_Music* ResMgr::find_music(const std::string& name)
{
	return music_pool[name];
}

SDL_Texture* ResMgr::find_texture(const std::string& name)
{
	return texture_pool[name];
}
