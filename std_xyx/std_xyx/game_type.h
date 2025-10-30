#pragma once

#include <string>
#include <iostream>
#include <functional>
#include <type_traits>

// 游戏类型
enum class GameType
{
	NONE = 0,	// 空
	START,		// 游戏开始
	XCZ,		// 提瓦特幸存者
	KDWS,		// 空洞武士
	DLD,		// 大乱斗
	ZMDJ,		// 致命打鸡
	PHF			// 拼好饭
};

/*锚点模式*/
enum class AnchorMode	// 注意，这九个值强关联，不可修改
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

/*尺寸计算方式*/
enum class SizeType
{
	AUTO = 0,	// 自动		根据资源自适应大小
	PIXEL		// 像素		由输入的像素值决定
	// 和父节点宽相 乘 加
	// 和父节点高相 乘 加
	// 保持比例，宽和父节点对齐
	// 保持比例，高和父节点对齐
	// 其他，还没想好
};

/*场景类型*/
enum class SceneType
{
	MENU = 0,	// 菜单场景
	SELECTOR,	// 选择场景
	GAME,		// 游戏场景
};

/*纹理映射/采样模式*/
enum class TextureMapType
{
	AUTO = 0,	// 自动		完全显示纹理内容
	TILE,		// 平铺		根据尺寸，平铺裁剪
	STRETCH		// 拉伸		根据尺寸，拉伸填满
};

/*渲染层*/
enum RenderLayer
{
	BACKGROUND,	// 背景层	存放地图之类
	ENTITY,		// 实体体	游戏实体对象之类
	UI			// UI层
};

/*按钮状态*/
enum class ButtonState {
	PRESSED = 0,	// 
	NORMAL,			// 正常
	HOVER,			// 悬停
	DISABLED		// 禁用状态（灰化、不可交互）
};

/*碰撞层*/
enum class CollisionLayer
{
	NONE,		// 空
	BULLET,		// 子弹
	PLAYER_1,	// 玩家1
	PLAYER_2,	// 玩家2
	ENEMY,		// 敌人（怪）
};

/*对象节点类型*/
enum class NodeType
{
	ROOT,       // 根节点
	LAYER,		// 层级节点（背景/游戏/UI）
	GAMENODE    // 游戏对象节点
};

// 自定义事件类型
enum class EventType {

	COLLISION,			// 碰撞发生（单次触发）
	ADD_BULLET,			// 添加子弹
	REDUCE_BULLET,		// 减少子弹
	LAUNCH_BULLET,		// 发射子弹
	PLAYER_DIE,			// 角色死亡
	PLAYER_MOVE,		// 角色移动
	ENEMY_DIE,			// 敌人死亡
	ADD_ENEMY,			// 新增敌人
	REDUCE_ENEMY,		// 减少敌人
	COUNT				// 哨兵位,用于记录总枚举总数，不可使用，不可删除
};

// GameType 特化 std::hash
namespace std {
	template<> struct hash<GameType> {
		size_t operator()(const GameType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<GameType>>(type));
		}
	};
}

// SceneType 特化 std::hash
namespace std {
	template<> struct hash<SceneType> {
		size_t operator()(const SceneType& type) const noexcept {
			return hash<int>()(static_cast<underlying_type_t<SceneType>>(type));
		}
	};
}