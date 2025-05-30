#pragma once
#include "Vector2.h"
#include "Collision_layer.h"
#include <functional>

class CollisionManager;

/**
*@brief		碰撞箱
*@note		构造和析构私有，是因为不能随意创建碰撞箱。不被碰撞管理器管理的碰撞箱没有意义
*@author 	xd  
*@date 		20-5-9  
*/
class CollisionBox
{
	friend class CollisionManager;
private:
    // 碰撞箱的坐标锚点为中心点
	Vector2 position;
	Vector2 size;
	// 是否启用碰撞检测
	bool enabled = true;
	// 碰撞后的回调函数
	std::function<void()> call_back;
	// 自身碰撞层
	CollisionLayer layer_src = CollisionLayer::None;
	// 目标碰撞层
	CollisionLayer layer_dst = CollisionLayer::None;
private:
	CollisionBox() = default;
	~CollisionBox() = default;
public:
    /**
    *@note 碰撞检测逻辑归碰撞管理器管，所以此处主要提供set接口即可
    */
    /// <summary>
    /// 设置碰撞箱启用状态
    /// </summary>
    /// <param name="flag"></param>
    void set_enabled(bool flag)
    {
        enabled = flag;
    }
    /// <summary>
    /// 设置自身碰撞层
    /// </summary>
    /// <param name="layer"></param>
    void set_layer_src(CollisionLayer layer)
    {
        layer_src = layer;
    }
    /// <summary>
    /// 设置目标碰撞层
    /// </summary>
    /// <param name="layer"></param>
    void set_layer_dst(CollisionLayer layer)
    {
        layer_dst = layer;
    }

    void set_call_back(std::function<void()> call_back)
    {
        this->call_back = call_back;
    }

    void set_size(const Vector2& size)
    {
        this->size = size;
    }

    const Vector2& get_size() const
    {
        return size;
    }

    void set_position(const Vector2& pos)
    {
        position = pos;
    }
};

