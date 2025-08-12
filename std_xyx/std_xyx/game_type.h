#pragma once

#include <string>

// 游戏类型
enum class GameType
{
	NONE = 0,	// 无
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
	case GameType::NONE:	return "";		break;
	case GameType::XCZ:		return "xcz";	break;
	case GameType::KDWS:	return "kdws";	break;
	case GameType::DLD:		return "dld";	break;
	case GameType::ZMDJ:	return "zmdj";	break;
	case GameType::PHF:		return "phf";	break;
	}
}