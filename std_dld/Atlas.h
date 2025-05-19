#pragma once
#include <vector>
#include <graphics.h>

/*ÕººØ¿‡*/
class Atlas
{
public:
	Atlas() = default;
	~Atlas()
	{
		img_list_clear();
	}

	void load_from_file(LPCTSTR path, int num)
	{
		img_list_clear();

		TCHAR path_file[256];
		for (int i = 0; i < num; ++i)
		{
			_stprintf_s(path_file, path, i + 1);
			IMAGE* p = new IMAGE();
			loadimage(p, path_file);
			img_list.push_back(p);
		}
	}

	void img_list_clear()
	{
		for (int i = 0; i < img_list.size();++i)
		{
			delete img_list[i];
			img_list[i] = nullptr;
		}
		img_list.clear();
	}

	int get_imglist_size()
	{
		return (int)img_list.size();
	}

	IMAGE* getImageByIndex(int index)
	{
		if (index < 0 || index >= img_list.size())
		{
			return nullptr;
		}
		return img_list[index];
	}

	void add_imgList(IMAGE* img)
	{
		img_list.push_back(img);
	}

private:
	std::vector<IMAGE*> img_list;
};

