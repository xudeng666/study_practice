#pragma once
#include "util.h"
#include "Atlas.h"
#include <string>
#include <graphics.h>
#include <unordered_map>

class ResourceManager
{
private:
	static ResourceManager* manager;

	void load();

	Atlas* find_atlas(const std::string& id)const;
	IMAGE* find_image(const std::string& id)const;
public:
	static ResourceManager* instance();

	std::unordered_map<std::string, Atlas*> atlas_pool;
	std::unordered_map<std::string, IMAGE*> image_pool;
private:
	ResourceManager();
	~ResourceManager();
	/**
	* @brief 图片资源水平转换
	* @param src 原始图片
	* @param dst 转换图片
	* @param num 转换数量
	*/
	void hor_flip_img(IMAGE* src, IMAGE* dst, int num = 1);
	/**
	* @brief 图片资源水平转换
	* @param src 原始索引
	* @param dst 转换索引
	* @param num 转换数量
	*/
	void hor_flip_img(const std::string& src, const std::string& dst, int num = 1);
	/**
	* @brief 图集资源水平转换
	* @param src 原始索引
	* @param dst 转换索引
	*/
	void hor_flip_atlas(const std::string& src, const std::string& dst);
};

