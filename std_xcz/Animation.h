#pragma once
#include <vector>
#include <graphics.h>


#pragma comment(lib, "MSIMG32.LIB")

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
	Animation(LPCTSTR path, int num, double speed)
	{
		ani_speed = speed;
		TCHAR path_file[256];
		for (size_t i = 0; i < num; ++i)
		{
			_stprintf_s(path_file, path, i);
			IMAGE* frame = new IMAGE();
			loadimage(frame, path_file);
			frame_list.push_back(frame);
		}
	}

	~Animation()
	{
		for (size_t i = 0; i < frame_list.size(); ++i)
		{
			delete frame_list[i];
			frame_list[i] = nullptr;
		}
	}
	/*
	动画播放
	@x	x坐标位置
	@y	y坐标位置
	*/
	void play(int x, int y)
	{
		int t = ani_fx ? idx_frame + frame_list.size() / 2 : idx_frame;
		putimage_alpha(x, y, frame_list[t]);
	}

	/*
	* 设置播放数据
	@isMove 是否移动
	*/
	void DrawPlayer(bool isMove)
	{
		DWORD t_time = GetTickCount();

		if ((t_time - timer) >= 1000 / ani_speed)
		{
			timer = t_time;
			idx_frame++;
		}
		int t = frame_list.size() / 2 - 1;
		idx_frame = isMove ? (idx_frame % t) : t;
	}

	void setAniSpeed(double speed)
	{
		ani_speed = speed;
	}

	void setFx(bool isLeft)
	{
		ani_fx = isLeft;
	}
private:
	std::vector<IMAGE*> frame_list;
	// 动画播放速度
	double ani_speed = 0;
	// 动画计时器
	int timer = 0;
	// 动画帧索引
	int idx_frame = 0;
	// 朝向 true 向左 false 向右
	bool ani_fx = false;
};

