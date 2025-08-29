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
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // ��չ��תСд

			std::string keyStr = relative(p, resRoot).string();				// ·�������»����滻
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
					std::cout << "ͼƬ��Դ����ʧ��: " << p << "������" << IMG_GetError() << std::endl;
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
						std::cout << "������Դ����ʧ��: " << p << "������" << Mix_GetError() << std::endl;
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
						std::cout << "��Ч��Դ����ʧ��: " << p << "������" << Mix_GetError() << std::endl;
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
			std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // ��չ��תСд

			std::string keyStr = p.stem().u8string();	// �����ļ�������·��

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
						std::cout << "������Դ����ʧ��: " << p << "������" << TTF_GetError() << std::endl;
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
	// �ͷű�������
	for (auto& [name, music] : music_pool) {
		Mix_FreeMusic(music);
	}
	music_pool.clear();

	// �ͷ���Ч
	for (auto& [name, audio] : audio_pool) {
		Mix_FreeChunk(audio);
	}
	audio_pool.clear();

	// �ͷ�����
	for (auto& [name, tex] : texture_pool) {
		SDL_DestroyTexture(tex);
	}
	texture_pool.clear();

	// �ͷ�����
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
	//std::cout << "��ȡ���֣�" << name << std::endl;
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
	// �������һ�� '.' ��λ��
	size_t dotPos = filename.find_last_of('.');

	// ���ҵ� '.' �Ҳ��ڿ�ͷ�����⴦�� ".bashrc" ���������ļ�ʱ���ؿգ�
	if (dotPos != std::string::npos && dotPos > 0) {
		return filename.substr(0, dotPos);  // ��ȡ�� '.' ֮ǰ
	}

	// δ�ҵ� '.' �� '.' �ڿ�ͷ������ԭ�ַ���
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
