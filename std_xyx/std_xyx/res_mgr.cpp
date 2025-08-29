#include "res_mgr.h"
#include "game_wnd.h"
#include "game_mgr.h"

#include <filesystem>

ResMgr* ResMgr::manager = nullptr;

ResMgr* ResMgr::instance()
{
	if (!manager)
	{
		manager = new ResMgr();
	}
	return manager;
}

void ResMgr::load()
{
	using namespace std::filesystem;

	const std::string resRoot = "resources/" + get_str_of_type(GameMgr::instance()->get_current_type());

	for (const auto& entry:recursive_directory_iterator(resRoot))
	{
		if (entry.is_regular_file())
		{
			if (!entry.is_regular_file()) continue;

			const path& p = entry.path();

			std::string ext = p.extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // 扩展名转小写

			std::string keyStr = relative(p, resRoot).string();				// 路径正文下划线替换
			std::replace(keyStr.begin(), keyStr.end(), '/', '_');
			std::replace(keyStr.begin(), keyStr.end(), '\\', '_');
			keyStr = removeFileExtension(keyStr);

			/*std::cout << "p: " << p << std::endl
				<< "ext: " << ext << std::endl
				<< "keystr: " << keyStr << std::endl;*/

			if (ext == ".png")
			{
				SDL_Texture* texture = IMG_LoadTexture(GameWnd::instance()->get_renderer(), p.u8string().c_str());
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

void ResMgr::ttf_load(const std::string& name)
{
	using namespace std::filesystem;

	const std::string resRoot = "resources/" + get_str_of_type(GameMgr::instance()->get_current_type());

	for (const auto& entry:recursive_directory_iterator(resRoot))
	{
		if (entry.is_regular_file())
		{
			if (!entry.is_regular_file()) continue;

			const path& p = entry.path();

			std::string ext = p.extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // 扩展名转小写

			std::string keyStr = p.stem().u8string();	// 字体文件不考虑路径

			if (ext == ".ttf")
			{
				int size;
				std::string key;
				if (splitByLastChar(name, '_', key, size) && key == keyStr)
				{
					TTF_Font* font = TTF_OpenFont(p.u8string().c_str(), size);
					if (font)
					{
						ttf_pool[name] = font;
					}
					else
					{
						std::cout << "字体资源加载失败: " << p << "，错误：" << TTF_GetError() << std::endl;
					}
				}
			}
		}
	}
}


void ResMgr::res_traversal()
{
	for (auto& [name, music] : music_pool) {
		std::cout << "music:   " << name << std::endl;
	}
	for (auto& [name, audio] : audio_pool) {
		std::cout << "audio:   " << name << std::endl;
	}
	for (auto& [name, tex] : texture_pool) {
		std::cout << "image:   " << name << std::endl;
	}
	for (auto& [name, ttf] : ttf_pool) {
		std::cout << "ttf:   " << name << std::endl;
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

	// 释放字体
	for (auto& [name, ttf]:ttf_pool){
		TTF_CloseFont(ttf);
	}
	ttf_pool.clear();
}

Mix_Chunk* ResMgr::find_audio(const std::string& name)
{
	return audio_pool[name];
}

Mix_Music* ResMgr::find_music(const std::string& name)
{
	//std::cout << "获取音乐：" << name << std::endl;
	return music_pool[name];
}

SDL_Texture* ResMgr::find_texture(const std::string& name)
{
	// std::cout << name << texture_pool[name] << std::endl;
	return texture_pool[name];
}

TTF_Font* ResMgr::find_ttf(const std::string& name)
{
	//std::cout << "find_ttf A  "<< name << std::endl;
	if (!ttf_pool[name])
	{
		ttf_load(name);
	}
	return ttf_pool[name];
}

std::string ResMgr::removeFileExtension(const std::string& filename) {
	// 查找最后一个 '.' 的位置
	size_t dotPos = filename.find_last_of('.');

	// 若找到 '.' 且不在开头（避免处理 ".bashrc" 这类隐藏文件时返回空）
	if (dotPos != std::string::npos && dotPos > 0) {
		return filename.substr(0, dotPos);  // 截取到 '.' 之前
	}

	// 未找到 '.' 或 '.' 在开头，返回原字符串
	return filename;
}

std::string ResMgr::get_str_of_type(GameType type)
{
	switch (type)
	{
	case GameType::START:	return "start";	break;
	case GameType::XCZ:		return "xcz";	break;
	case GameType::KDWS:	return "kdws";	break;
	case GameType::DLD:		return "dld";	break;
	case GameType::ZMDJ:	return "zmdj";	break;
	case GameType::PHF:		return "phf";	break;
	}
}
