#pragma once
#include <graphics.h>

#pragma comment(lib,"MSIMG32.LIB")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(GetWorkingImage()), x, y, w, h, 
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

/*工具类文件*/

/*
* 图片水平翻转
* @src	原始图片
* @dst	新图片
*/
inline void hor_flip_img(IMAGE* src, IMAGE* dst)
{
	int w = src->getwidth();
	int h = src->getheight();
	dst->Resize(w, h);

	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	for (int i = 0; i < w * h; ++i)
	{
		dst_buf[i] = src_buf[i / w * w + (w - i % w) - 1];
	}
}

/*
* 水平翻转
* @src	原始图片
* @dst	新图片
* @rgb	设置剪影颜色（默认白色）
*/
inline void set_silh_img(IMAGE* src, IMAGE* dst, DWORD rgb = 0xFFFFFFFF)
{
	int w = src->getwidth();
	int h = src->getheight();
	dst->Resize(w, h);

	DWORD* src_buf = GetImageBuffer(src);
	DWORD* dst_buf = GetImageBuffer(dst);

	for (int i = 0; i < w * h; ++i)
	{
		if (src_buf[i] & 0xFF000000 >> 24)
		{
			dst_buf[i] = rgb;
		}
	}
}