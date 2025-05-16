#include "Atlas.h"


/*
构造函数
@path 资源路径
@num 资源数量
*/
Atlas::Atlas(LPCTSTR path, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

/*
构造函数
@path 资源路径
@type 类型
@num 资源数量
*/
Atlas::Atlas(LPCTSTR path, unsigned int type, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, type, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
}

Atlas::~Atlas()
{
	for (size_t i = 0; i < frame_list.size(); ++i)
	{
		delete frame_list[i];
		frame_list[i] = nullptr;
	}
	frame_list.clear();
}

/*获取资源列表*/
vector <IMAGE*> Atlas::getFrameList()
{
	return frame_list;
}