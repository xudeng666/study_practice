#pragma once
#include "utils.h"
#include "Atlas.h"
#include "Camera.h"

#pragma comment(lib,"WINMM.lib")
#pragma comment(lib,"MSIMG32.LIB")

/*矩形*/
struct Rect
{
	int x, y;
	int w, h;
};
/**
* 绘制图片（能展示透明信息）
* @param x		绘制坐标
* @param y		绘制坐标
* @param img	绘制图片指针
*/
inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(const Camera& camera, int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	const Vector2& pos = camera.get_position();
	x = (int)(x - pos.x);
	y = (int)(y - pos.y);
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void putimage_alpha(int dst_x, int dst_y, int dst_w, int dst_h, IMAGE* img, int src_x, int src_y)
{
	int w = dst_w > 0 ? dst_w : img->getwidth();
	int h = dst_h > 0 ? dst_h : img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), dst_x, dst_y, w, h,
		GetImageHDC(img), src_x, src_y, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


inline void putimage_alpha_ex(IMAGE* img, const Rect* r_d, const Rect* r_s = nullptr)
{
	AlphaBlend(GetImageHDC(GetWorkingImage()), r_d->x, r_d->y, r_d->w, r_d->h,
		GetImageHDC(img), r_s ? r_s->x : 0, r_s ? r_s->y : 0, r_s ? r_s->w : img->getwidth(), r_s ? r_s->h : img->getheight(),
		{ AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

inline void line(const Camera& camera, int x1, int y1, int x2, int y2 )
{
	const Vector2& pos = camera.get_position();
	line((int)(x1 - pos.x), (int)(y1 - pos.y), (int)(x2 - pos.x), (int)(y2 - pos.y));
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0"), id, is_loop ? _T("repeat") : _T(""));
	mciSendString(str_cmd, NULL, 0, NULL);
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	mciSendString(str_cmd, NULL, 0, NULL);
}