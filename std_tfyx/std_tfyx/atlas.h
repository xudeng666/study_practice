#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <string>

class Atlas
{
public:
	Atlas() = default;

	~Atlas()
	{
		for (SDL_Texture* texture : tex_list)
		{
			SDL_DestroyTexture(texture);
		}
	}
	/// <summary>
	/// ������Դ
	/// </summary>
	/// <param name="renderer">��Ⱦ��ָ��</param>
	/// <param name="path">·��</param>
	/// <param name="num">����</param>
	void load(SDL_Renderer* renderer, const char* path, int num)
	{
		for (int i = 0; i < num; i++)
		{
			char path_file[256];
			sprintf_s(path_file, path, i + 1);
			// ��ͼƬ����Ϊ����
			SDL_Texture* texture = IMG_LoadTexture(renderer, path_file);
			tex_list.push_back(texture);
		}
	}

	void clear()
	{
		for (SDL_Texture* texture : tex_list)
		{
			SDL_DestroyTexture(texture);
		}
	}

	int get_size()const
	{
		return (int)tex_list.size();
	}
	/// <summary>
	/// ��ȡ�������
	/// </summary>
	/// <param name="idx">�±�</param>
	/// <returns></returns>
	SDL_Texture* get_texture(int idx)
	{
		if (idx < 0 || idx >= tex_list.size())
		{
			return nullptr;
		}
		return tex_list[idx];
	}
	/// <summary>
	/// ��Ӷ�������ͼ��
	/// </summary>
	/// <param name="texture">�������ָ��</param>
	void add_texture(SDL_Texture* texture)
	{
		tex_list.push_back(texture);
	}
private:
	// ͼƬ�����б�
	std::vector<SDL_Texture*> tex_list;

};
