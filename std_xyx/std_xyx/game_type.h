#pragma once

#include <string>
#include "SDL.h"

// 游戏类型
enum class GameType
{
	//NONE = -1,	// 空
	START = 0,	// 游戏开始
	XCZ,		// 提瓦特幸存者
	KDWS,		// 空洞武士
	DLD,		// 大乱斗
	ZMDJ,		// 致命打鸡
	PHF			// 拼好饭
};

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

/*碰撞层*/
enum class CollisionLayer
{
	NONE,	// 空
	BULLET,	// 子弹
	PLAYER,	// 玩家
	ENEMY,	// 敌人（怪）
};