#pragma once
#include "utils.h"
#include "Atlas.h"
#include "Camera.h"

#pragma comment(lib,"MSIMG32.LIB")

/*
* 图集水平翻转
* @src	原始图集
* @dst	新图集
*/
inline void hor_flip_Atlas(Atlas& src, Atlas& dts)
{
	dts.img_list_clear();
	for (int i = 0; i < src.get_imglist_size(); ++i)
	{
		IMAGE* p = new IMAGE();
		hor_flip_img(src.getImageByIndex(i), p);
		dts.add_imgList(p);
	}
}

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

inline void line(const Camera& camera, int x1, int y1, int x2, int y2 )
{
	const Vector2& pos = camera.get_position();
	line((int)(x1 - pos.x), (int)(y1 - pos.y), (int)(x2 - pos.x), (int)(y2 - pos.y));
}