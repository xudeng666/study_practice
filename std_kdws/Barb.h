#pragma once

#include "animation.h"
#include "CollisionBox.h"
/*
* 刺球类
*/
class Barb
{
public:
    Barb();
    ~Barb();

    void on_update(float delta);
    void on_draw();

    void set_position(const Vector2& position)
    {
        base_position = position;
        current_position = position;
    }

    bool check_valid() const
    {
        return is_valid;
    }
private:
    /*持球状态*/
    enum class Stage
    {
        Idle,//默认-上下浮动
        Aim,//瞄准
        Dash,//冲刺
        Break//破碎
    };

private:
    const float SPEED_DASH = 1500.0f;//速度

private:
    Timer timer_idle;//默认状态计时器
    Timer timer_aim;// 瞄准状态计时器
    int diff_period = 0;//随机值，控制浮动的周期偏移
    bool is_valid = true;//是否有效
    float total_delta_time = 0;//记录持球当下寿命（生成以来的时间）

    Vector2 velocity;
    Vector2 base_position;//基础位置
    Vector2 current_position;//当前位置（两个位置是为了控制浮动和瞄准（抖动）效果）

    Animation animation_loose;// 动画-正常
    Animation animation_break;// 动画-破碎
    Animation* current_animation = nullptr;//当前动画

    Stage stage = Stage::Idle;//当前状态
    CollisionBox* collision_box = nullptr;//碰撞体

private:
    void on_break();//刺球破碎处理
};
