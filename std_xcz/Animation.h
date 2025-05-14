#pragma once
#include <vector>
#include <graphics.h>


using namespace std;


#pragma comment(lib, "MSIMG32.LIB")
/*渲染图片并识别透明区域*/
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(nullptr), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0,255,AC_SRC_ALPHA });
}

/*
* 帧动画基类
*/
class Animation
{
public:
	/*
	构造函数
	@path 资源路径
	@num 资源数量
	@speed	播放速度
	*/
	Animation(LPCTSTR path, int num, double speed);

	~Animation();
	/*
	动画播放
	@x	x坐标位置
	@y	y坐标位置
	*/
	void play(int x, int y);

	/*
	* 设置播放数据 针对有停止帧
	@isMove 是否移动
	*/
	void DrawPlayer(bool isMove);
	/*
	* 设置播放数据
	*/
	void DrawPlayer();
	/*
	* 设置速度
	*/
	void setAniSpeed(double speed);
	/*
	* 设置方向
	*/
	void setFx(bool isLeft);

	/*
	获取动画尺寸
	@w	赋值变量w
	@h	赋值变量h
	*/
	void getAniSize(int& w, int& h)
	{
		w = frame_list[0]->getwidth();
		h = frame_list[0]->getheight();
	}
private:
	vector<IMAGE*> frame_list;
	// 动画播放速度
	double ani_speed = 0;
	// 动画计时器
	int timer = 0;
	// 动画帧索引
	int idx_frame = 0;
	// 朝向 true 向左 false 向右
	bool ani_fx = false;
};

