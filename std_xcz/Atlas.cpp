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
	frame_num = num;
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
	frame_num = num;
}

/*
构造函数
@path 资源路径
@ice_path	冰雪资源路径
@type 类型
@num 资源数量
*/
Atlas::Atlas(LPCTSTR path, LPCTSTR ice_path, unsigned int type, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, type, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
	frame_num = num;
	img_ice = new IMAGE();
	loadimage(img_ice, ice_path);
}

/*
构造函数
@path 资源路径
@ice_path	冰雪资源路径
@num 资源数量
*/
Atlas::Atlas(LPCTSTR path, LPCTSTR ice_path, int num)
{
	TCHAR path_file[256];
	for (size_t i = 0; i < num; ++i)
	{
		_stprintf_s(path_file, path, i);
		IMAGE* frame = new IMAGE();
		loadimage(frame, path_file);
		frame_list.push_back(frame);
	}
	frame_num = num;
	img_ice = new IMAGE();
	loadimage(img_ice, ice_path);
}

Atlas::~Atlas()
{
	for (size_t i = 0; i < frame_list.size(); ++i)
	{
		delete frame_list[i];
		frame_list[i] = nullptr;
	}
	frame_list.clear();
	delete img_ice;
	img_ice = nullptr;
}

/*获取资源列表*/
vector <IMAGE*> Atlas::getFrameList()
{
	return frame_list;
}
/*
获取图片
@index 下标
*/
IMAGE* Atlas::getFrameByIndex(unsigned int index)
{
	return frame_list[index];
}

/*
获取资源总数
*/
unsigned int Atlas::getFrameNum()
{
	return frame_num;
}

/*
获取动画尺寸
@w	赋值变量w
@h	赋值变量h
*/
void Atlas::getFrameSize(int& w, int& h)
{
	w = frame_list[0]->getwidth();
	h = frame_list[0]->getheight();
}

/*生成反向资源*/
void Atlas::greatRightDirect()
{
	unsigned int n = getFrameNum();
	for (int i = 0; i < n; ++i)
	{
		int w = frame_list[i]->getwidth();
		int h = frame_list[i]->getheight();
		IMAGE* p = new IMAGE();
		Resize(p, w, h);
		DWORD* color_buf_0 = GetImageBuffer(frame_list[i]);
		DWORD* color_buf_1 = GetImageBuffer(p);
		for (int j = 0; j < w * h;++j)
		{
			color_buf_1[j] = color_buf_0[j / w * w + (w - j % w) - 1];
		}
		frame_list.push_back(p);
	}
}

/*生成白色剪影资源*/
void Atlas::greatWhitePix()
{
	unsigned int n = frame_num * 2;
	for (int i = 0; i < n; ++i)
	{
		int w = frame_list[i]->getwidth();
		int h = frame_list[i]->getheight();
		IMAGE* p = new IMAGE();
		Resize(p, w, h);
		DWORD* color_buf_0 = GetImageBuffer(frame_list[i]);
		DWORD* color_buf_1 = GetImageBuffer(p);
		for (int j = 0; j < w * h;++j)
		{
			if (color_buf_0[j] & 0xFF000000 >> 24)
			{
				color_buf_1[j] = 0xFFFFFFFF;
			}
		}
		frame_list.push_back(p);
	}
}

/*生成冰雪特效资源*/
void Atlas::greatIcePix()
{
	unsigned int n = frame_num * 2;
	double alpha = 0.5;
	for (int i = 0; i < n; ++i)
	{
		int w = frame_list[i]->getwidth();
		int h = frame_list[i]->getheight();
		IMAGE* p = new IMAGE();
		Resize(p, w, h);
		Resize(img_ice, w, h);
		DWORD* color_buf_0 = GetImageBuffer(frame_list[i]);
		DWORD* color_buf_1 = GetImageBuffer(p);
		DWORD* color_buf_2 = GetImageBuffer(img_ice);
		for (int j = 0; j < w * h;++j)
		{
			if (color_buf_0[j] & 0xFF000000 >> 24)
			{
				BYTE r = (BYTE)(GetBValue(color_buf_0[j]) * alpha + GetBValue(color_buf_2[j]) * (1 - alpha));
				BYTE g = (BYTE)(GetGValue(color_buf_0[j]) * alpha + GetBValue(color_buf_2[j]) * (1 - alpha));
				BYTE b = (BYTE)(GetRValue(color_buf_0[j]) * alpha + GetBValue(color_buf_2[j]) * (1 - alpha));
				color_buf_1[j] = (RGB(r, g, b)) | (((DWORD)(BYTE)(255)) << 24);
			}
		}
		frame_list.push_back(p);
	}
}