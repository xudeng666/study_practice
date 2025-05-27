#pragma once
#include <vector>
#include <graphics.h>

/*ͼ����*/
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

		TCHAR path_file[256];
		for (int i = 0; i < num; ++i)
		{
			_stprintf_s(path_file, path, i + 1);
			IMAGE* p = new IMAGE();
			loadimage(p, path_file);
			img_list.push_back(p);
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

	int get_size()
	{
		return (int)img_list.size();
	}
	/*
	* ��ȡ��ǰ֡ͼƬ
	* @index ��ǰ֡����
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

