#pragma once
#include "vector2.h"
#include "animation.h"
#include "CollisionBox.h"
#include "StateMachine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

/**
*@brief 	人物基类
*@author	xd
*@date 		2025-5-29
*/
class Character
{
protected:
    /*动画组*/
    struct AnimationGroup
    {
        Animation left;
        Animation right;
    };
protected:
    const float FLOOR_Y = 620;                                      // 地板的竖直方向坐标
    const float GRAVITY = 980 * 2;                                  // 重力大小

protected:
    int hp = 10;                                                    // 角色生命值
    Vector2 position;                                               // 角色脚底位置
    Vector2 velocity;                                               // 角色速度
    float logic_height = 0;                                         // 角色的逻辑高度
    bool is_facing_left = true;                                     // 当前角色是否朝向左
    StateMachine state_machine;                                     // 角色逻辑状态机
    bool enable_gravity = true;                                     // 启用重力模拟
    bool is_invulnerable = false;                                   // 当前是否无敌
    Timer timer_invulnerable_blink;                                 // 无敌闪烁状态定时器
    Timer timer_invulnerable_status;                                // 无敌状态定时器
    bool is_blink_invisible = false;                                // 当前是否处于闪烁的不可见帧
    CollisionBox* hit_box = nullptr;                                // 攻击碰撞箱
    CollisionBox* hurt_box = nullptr;                               // 受击碰撞箱
    AnimationGroup* current_animation = nullptr;                    // 当前角色动画
    std::unordered_map<std::string, AnimationGroup> animation_pool; // 角色动画池 
public:
    Character();
    ~Character();
    /// <summary>
    /// 受到攻击，刷新血量
    /// </summary>
    void decrease_hp();

    int get_hp() const
    {
        return hp;
    }

    void set_position(const Vector2& position)
    {
        this->position = position;
    }

    const Vector2& get_position() const
    {
        return position;
    }

    void set_velocity(const Vector2& velocity)
    {
        this->velocity = velocity;
    }
    const Vector2& get_velocity() const
    {
        return velocity;
    }

    /**
    *@brief 	获取居中坐标
    */
    Vector2 get_logic_center() const
    {
        return Vector2(position.x, position.y - logic_height / 2);
    }
    /// <summary>
    /// 开关重力模拟
    /// </summary>
    /// <param name="flag"></param>
    void set_gravity_enabled(bool flag)
    {
        enable_gravity = flag;
    }
    /// <summary>
    /// 获取攻击碰撞箱
    /// </summary>
    /// <returns></returns>
    CollisionBox* get_hit_box()
    {
        return hit_box;
    }
    /// <summary>
    /// 获取受击碰撞箱
    /// </summary>
    /// <returns></returns>
    CollisionBox* get_hurt_box()
    {
        return hurt_box;
    }

    /**
    *@brief 	是否在地面上
    *@return 	true/false
    */
    bool is_on_floor() const
    {
        return position.y >= FLOOR_Y;
    }
    /**
    *@brief 	获取地面高度
    */
    float get_floor_y() const
    {
        return FLOOR_Y;
    }
    /*设定无敌状态*/
    void make_invulnerable()
    {
        is_invulnerable = true;
        timer_invulnerable_status.restart();
    }

    virtual void on_input(const ExMessage& msg);
    virtual void on_update(float delta);
    virtual void on_draw();

    virtual void on_hurt();
    /*切换状态*/
    void switch_state(const std::string& id);
    /*设置动画*/
    void set_animation(const std::string& id);
};