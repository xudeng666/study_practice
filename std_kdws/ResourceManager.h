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
	* @brief ͼƬ��Դˮƽת��
	* @param src ԭʼͼƬ
	* @param dst ת��ͼƬ
	* @param num ת������
	*/
	void hor_flip_img(IMAGE* src, IMAGE* dst, int num = 1);
	/**
	* @brief ͼƬ��Դˮƽת��
	* @param src ԭʼ����
	* @param dst ת������
	* @param num ת������
	*/
	void hor_flip_img(const std::string& src, const std::string& dst, int num = 1);
	/**
	* @brief ͼ����Դˮƽת��
	* @param src ԭʼ����
	* @param dst ת������
	*/
	void hor_flip_atlas(const std::string& src, const std::string& dst);
};

