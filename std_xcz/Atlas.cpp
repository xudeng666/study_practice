#include "Atlas.h"


/*
���캯��
@path ��Դ·��
@num ��Դ����
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
���캯��
@path ��Դ·��
@type ����
@num ��Դ����
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

/*��ȡ��Դ�б�*/
vector <IMAGE*> Atlas::getFrameList()
{
	return frame_list;
}