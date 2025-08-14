#pragma once

#include <string>

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

std::string getStrByGameType(GameType type)
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

/*场景类型*/
enum class SceneType
{
	MENUE = 0,	// 菜单场景
	GAME,		// 游戏场景
	SELECTOR,	// 选择场景
};