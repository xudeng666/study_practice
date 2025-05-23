#pragma once
#include "PlayerID.h"
#include "util.h"
#include <graphics.h>

class StatusBar
{
public:
	StatusBar() = default;
	~StatusBar() = default;

	// 设置头像
	void set_head(IMAGE* img)
	{
		img_head = img;
	}

	// 设置位置
	void set_position(int x, int y)
	{
		position.x = x;
		position.y = y;
	}

	// 设置血量
	void set_hp(int val)
	{
		hp = val;
	}

	// 设置能量
	void set_mp(int val)
	{
		mp = val;
	}

	void on_draw()
	{
		putimage_alpha(position.x,position.y, img_head);

		// 绘制阴影
		setfillcolor(RGB(5, 5, 5));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);
		setfillcolor(RGB(67, 47, 47));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3, position.y + 33, 8, 8);
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3, position.y + 68, 8, 8);

		float hp_w = width * max(0, hp) / 100.f;
		float mp_w = width * min(100, mp) / 100.f;
		setfillcolor(RGB(197, 61, 67));
		solidroundrect(position.x + 100, position.y + 10, position.x + 100 + hp_w + 3, position.y + 33, 8, 8);
		setfillcolor(RGB(83, 131, 195));
		solidroundrect(position.x + 100, position.y + 45, position.x + 100 + mp_w + 3, position.y + 68, 8, 8);

	}

private:
	const int width = 275;

private:
	int hp = 0;
	int mp = 0;
	POINT position = { 0 };
	IMAGE* img_head = nullptr;
};

