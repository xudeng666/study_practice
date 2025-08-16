#pragma once

#include <string>
#include "SDL.h"

// 游戏类型
enum class GameType
{
	START = 0,	// 游戏开始
	XCZ,		// 提瓦特幸存者
	KDWS,		// 空洞武士
	DLD,		// 大乱斗
	ZMDJ,		// 致命打鸡
	PHF			// 拼好饭
};

inline std::string getStrByGameType(GameType type)
{
	switch (type)
	{
	case GameType::START:	return "start";	break;
	case GameType::XCZ:		return "xcz";	break;
	case GameType::KDWS:	return "kdws";	break;
	case GameType::DLD:		return "dld";	break;
	case GameType::ZMDJ:	return "zmdj";	break;
	case GameType::PHF:		return "phf";	break;
	}
}

/*锚点模式*/
enum class AnchorMode
{
	TOPLEFT = 0,	// 左上
	TOPCENTER,		// 上中
	TOPRIGHT,		// 右上
	LEFTCENTER,		// 左中
	CENTER,			// 正中
	RIGHTCENTER,	// 右中
	BOTTOMLEFT,		// 左下
	BOTTOMCENTER,	// 下中
	BOTTOMRIGHT		// 右下
};

/// <summary>
/// 获取绘制FRect
/// </summary>
/// <param name="src">游戏FRect</param>
/// <param name="mode">锚点类型</param>
/// <returns>SDL_FRect</returns>
inline SDL_FRect get_dst_rect(SDL_FRect& src, AnchorMode mode)
{
	float x = 0;
	float y = 0;

	switch (mode)
	{
	case AnchorMode::TOPLEFT:
		x = src.x;
		y = src.y;
		break;
	case AnchorMode::TOPCENTER:
		x = src.x - src.w / 2;
		y = src.y;
		break;
	case AnchorMode::TOPRIGHT:
		x = src.x - src.w;
		y = src.y;
		break;
	case AnchorMode::LEFTCENTER:
		x = src.x;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::CENTER:
		x = src.x - src.w / 2;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::RIGHTCENTER:
		x = src.x - src.w;
		y = src.y - src.h / 2;
		break;
	case AnchorMode::BOTTOMLEFT:
		x = src.x;
		y = src.y - src.h;
		break;
	case AnchorMode::BOTTOMCENTER:
		x = src.x - src.w / 2;
		y = src.y - src.h;
		break;
	case AnchorMode::BOTTOMRIGHT:
		x = src.x - src.w;
		y = src.y - src.h;
		break;
	}

	return { x, y, (float)src.w, (float)src.h };
}

/*场景类型*/
enum class SceneType
{
	MENUE = 0,	// 菜单场景
	SELECTOR,	// 选择场景
	GAME,		// 游戏场景
};

/*按钮状态*/
enum class ButtonState {
	PRESSED = 0,	// 按下
	NORMAL,			// 正常
	HOVER,			// 悬停
	DISABLED		// 禁用状态（灰化、不可交互）
};