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
	/// 加载资源
	/// </summary>
	/// <param name="renderer">渲染器指针</param>
	/// <param name="path">路径</param>
	/// <param name="num">数量</param>
	void load(SDL_Renderer* renderer, const char* path, int num)
	{
		for (int i = 0; i < num; i++)
		{
			char path_file[256];
			sprintf_s(path_file, path, i + 1);
			// 将图片加载为纹理
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
	/// 获取纹理对象
	/// </summary>
	/// <param name="idx">下标</param>
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
	/// 添加额外纹理到图集
	/// </summary>
	/// <param name="texture">纹理对象指针</param>
	void add_texture(SDL_Texture* texture)
	{
		tex_list.push_back(texture);
	}
private:
	// 图片纹理列表
	std::vector<SDL_Texture*> tex_list;

};
