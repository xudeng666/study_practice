#pragma once
#include <vector>
#include <graphics.h>

/*
*资源类型
* @PLAYER	角色资源
* @ENEMY_1	敌人资源1
* @ENEMY_2	敌人资源2
* @ENEMY_3	敌人资源3
* @ENEMY_4	敌人资源4
*/
enum FRAME_TYPE
{
	FRAME_TYPE_PLAYER = 0,
	FRAME_TYPE_ENEMY_1,
	FRAME_TYPE_ENEMY_2,
	FRAME_TYPE_ENEMY_3,
	FRAME_TYPE_ENEMY_4,
	FRAME_TYPE_COUNT
};

using namespace std;

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")

/*渲染图片并识别透明区域*/
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0,255,AC_SRC_ALPHA });
}

/*图集类*/
class Atlas
{
public:
	/*
	构造函数
	*@path 资源路径
	*@num 资源数量
	*/
	Atlas(LPCTSTR path, int num);
	/*
	构造函数
	@path 资源路径
	@type 类型
	@num 资源数量
	*/
	Atlas(LPCTSTR path, unsigned int type, int num);

	~Atlas();
	/*获取资源列表*/
	vector <IMAGE*> getFrameList();

	/*
	获取图片
	@index 下标
	*/
	IMAGE* getFrameByIndex(unsigned int index)
	{
		return frame_list[index];
	}

	/*
	获取资源总数
	*/
	unsigned int getFrameNum()
	{
		return frame_list.size();
	}

	/*
	获取动画尺寸
	@w	赋值变量w
	@h	赋值变量h
	*/
	void getFrameSize(int& w, int& h)
	{
		w = frame_list[0]->getwidth();
		h = frame_list[0]->getheight();
	}

private:
	vector <IMAGE*> frame_list;
};

