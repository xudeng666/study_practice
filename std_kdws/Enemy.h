#pragma once
#include "Sword.h"
#include "Barb.h"
#include "Character.h"

class Enemy :
    public Character
{
public:
    Enemy();
    ~Enemy();

    void on_update(float delta) override;
    void on_draw() override;
    /// <summary>
    /// 受击
    /// </summary>
    void on_hurt() override;
    /// <summary>
    /// 设置朝向
    /// </summary>
    /// <param name="flag">true左/false右</param>
    void set_facing_left(bool flag)
    {
        is_facing_left = flag;
    }
    /// <summary>
    /// 获取朝向
    /// </summary>
    /// <returns>true左/false右</returns>
    bool get_facing_left() const
    {
        return is_facing_left;
    }
    /// <summary>
    /// 设置空中冲刺
    /// </summary>
    /// <param name="flag">true/false</param>
    void set_dashing_in_air(bool flag)
    {
        is_dashing_in_air = flag;
    }
    /// <summary>
    /// 设置地面冲刺状态
    /// </summary>
    /// <param name="flag"></param>
    void set_dashing_on_floor(bool flag)
    {
        is_dashing_on_floor = flag;
    }
    /// <summary>
    /// 是否地面冲刺
    /// </summary>
    /// <returns></returns>
    bool get_dashing_on_floor() const
    {
        return is_dashing_on_floor;
    }
    /// <summary>
    /// 设为舞丝状态
    /// </summary>
    /// <param name="flag"></param>
    void set_throwing_silk(bool flag)
    {
        is_throwing_silk = flag;
        collision_box_silk->set_enabled(flag);
    }
    /// <summary>
    /// 是否舞丝
    /// </summary>
    /// <returns></returns>
    bool get_throwing_silk() const
    {
        return is_throwing_silk;
    }
    /// <summary>
    /// 召唤刺球
    /// </summary>
    void throw_barbs();
    /// <summary>
    /// 扔剑
    /// </summary>
    void throw_sword();
    /// <summary>
    /// 冲刺
    /// </summary>
    void on_dash();
    /// <summary>
    /// 召唤丝线
    /// </summary>
    void on_throw_silk();

private:
    bool is_throwing_silk = false;//是否挥丝
    bool is_dashing_in_air = false;//是否空中冲刺
    bool is_dashing_on_floor = false;//是否地面冲刺

    Animation animation_silk;//挥舞丝线动画
    AnimationGroup animation_dash_in_air_vfx;//空中冲刺动画组
    AnimationGroup animation_dash_on_floor_vfx;//地面冲刺动画组
    Animation* current_dash_animation = nullptr;//当前动画

    std::vector<Barb*> barb_list;
    std::vector<Sword*> sword_list;
    CollisionBox* collision_box_silk = nullptr;// 丝线碰撞箱
};

