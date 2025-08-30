#pragma once

#include "game_ani.h"
#include "game_collision_box.h"

// 角色基类
class Character:public GameObj
{
public:
    Character();
    virtual ~Character();

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_hurt();

    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;

    /// <summary>
    /// 受击刷新血量
    /// </summary>
    void decrease_hp();
    /// <summary>
    /// 获取血量
    /// </summary>
    /// <returns></returns>
    int get_hp() const;
    /// <summary>
    /// 开关重力模拟
    /// </summary>
    /// <param name="flag"></param>
    void set_gravity_enabled(bool flag);
    /// <summary>
    /// 获取攻击碰撞箱
    /// </summary>
    /// <returns></returns>
    GameCollisionBox* get_hit_box();
    /// <summary>
    /// 获取受击碰撞箱
    /// </summary>
    /// <returns></returns>
    GameCollisionBox* get_hurt_box();
    /// <summary>
    /// 设定无敌状态
    /// </summary>
    /// <returns></returns>
    void make_invulnerable();
    /// <summary>
    /// 切换状态
    /// </summary>
    /// <param name="id">状态ID</param>
    void switch_state(const std::string& id);
    /// <summary>
    /// 设置动画
    /// </summary>
    /// <param name="id">动画ID</param>
    void set_animation(const Ani_Res& res);


protected:
    int hp = 10;                                            // 角色生命值
    Vector2 velocity;                                       // 角色速度
    bool is_facing_left = true;                             // 当前角色是否朝向左
    //StateMachine state_machine;                           // 角色逻辑状态机
    bool enable_gravity = false;                            // 启用重力模拟
    bool is_invulnerable = false;                           // 当前是否无敌
    Timer timer_invulnerable_blink;                         // 无敌闪烁状态定时器
    Timer timer_invulnerable_status;                        // 无敌状态定时器
    bool is_blink_invisible = false;                        // 当前是否处于闪烁的不可见帧
    GameCollisionBox* hit_box = nullptr;                    // 攻击碰撞箱
    GameCollisionBox* hurt_box = nullptr;                   // 受击碰撞箱
    GameAni* current_ani = nullptr;                         // 当前角色动画
    std::unordered_map < std::string, Ani_Res > ani_pool;   // 角色动画池 
};