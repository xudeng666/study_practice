#pragma once

#include "animation.h"
#include "CollisionBox.h"
/*道具类*/
class Sword
{
public:
    /// <summary>
    /// 构造
    /// </summary>
    /// <param name="position">位置</param>
    /// <param name="move_left">是否向左</param>
    Sword(const Vector2& position, bool move_left);
    ~Sword();

    void on_update(float delta);
    void on_draw();
    /// <summary>
    /// 是否有效
    /// </summary>
    /// <returns>true/false</returns>
    bool check_valid() const
    {
        return is_valid;
    }

private:
    //移动速度
    const float SPEED_MOVE = 1250.0f;

private:
    Vector2 position;   // 位置
    Vector2 velocity;   // 速度
    Animation animation;    // 动画
    bool is_valid = true;   // 是否有效（无效则移除）
    CollisionBox* collision_box = nullptr;  // 碰撞箱
};

