#pragma once
#include <vector>
#include <graphics.h>

/*图集类*/
class Atlas
{
public:
	Atlas() = default;
	~Atlas()
	{
		clear();
	}

	void load(LPCTSTR path, int num)
	{
		clear();
		img_list.resize(num);
		TCHAR path_file[256];
		for (int i = 0; i < num; ++i)
		{
			_stprintf_s(path_file, path, i + 1);
			img_list[i] = new IMAGE();
			loadimage(img_list[i], path_file);
		}
	}

	void clear()
	{
		for (int i = 0; i < img_list.size();++i)
		{
			delete img_list[i];
			img_list[i] = nullptr;
		}
		img_list.clear();
	}

	void set_size(int num)
	{
		img_list.resize(num);
	}
	int get_size()
	{
		return (int)img_list.size();
	}
	/*
	* 获取当前帧图片
	* @index 当前帧索引
	*/
	IMAGE* getImage(int index)
	{
		if (index < 0 || index >= img_list.size())
		{
			return nullptr;
		}
		return img_list[index];
	}

	void add_image(IMAGE* img)
	{
		img_list.push_back(img);
	}

private:
	std::vector<IMAGE*> img_list;
};

