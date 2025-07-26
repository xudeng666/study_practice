#pragma once
#include "vector2.h"
#include "camera.h"

#include <SDL.h>

extern SDL_Texture* tex_bullet;

/*子弹类*/
class Bullet
{
public:
    Bullet(double val)
    {
        angle = val;
        double radians = getRadiansByAngle(angle);
        velocity.x = (float)std::cos(radians) * speed;
        velocity.y = (float)std::sin(radians) * speed;
    }

    ~Bullet() = default;

    /*设置位置*/
    void set_position(const Vector2& pos)
    {
        position = pos;
    }

    /*获取位置*/
    const Vector2& get_position() const
    {
        return position;
    }

    /*获取中心位置*/
    Vector2 get_center_position()
    {
        return { position.x + size.x / 2,position.y + size.y / 2 };
    }

    /*设置尺寸*/
    void set_size(const Vector2& pos)
    {
        size = pos;
    }

    /*获取尺寸*/
    const Vector2& get_size() const
    {
        return size;
    }

    /*设置速度*/
    void set_velocity(const Vector2& pos)
    {
        velocity = pos;
    }

    /*获取速度*/
    const Vector2& get_velocity() const
    {
        return velocity;
    }

    /*设置是否有效*/
    void on_hit()
    {
        valid = false;
    }
    /*是否可移除*/
    bool can_remove()const
    {
        return !valid;
    }

    void on_update(float delta)
    {
        position += velocity * delta;
        if (check_out_screen())
        {
            valid = false;
        }
    }

    void on_render(const Camera& camera)const
    {
        const SDL_FRect dst = { position.x - size.x / 2,position.y - size.y / 2,size.x,size.y };
        camera.render_texture(tex_bullet, nullptr, &dst, angle, nullptr);
    }
protected:
    Vector2 size = { 8.0,4.0 };         // 子弹尺寸
    Vector2 position;                   // 子弹位置
    Vector2 velocity;                   // 子弹速度
    double angle = 0;                   // 子弹旋转角度
    bool valid = true;                  // 子弹是否有效
    float speed = 1000.0f;               // 速度参数

protected:
    /*检测子弹飞出屏幕*/
    bool check_out_screen()
    {
        return (position.x + size.x < -10
            || position.x > _W_ + 10
            || position.y + size.y < -10
            || position.y > _H_ + 10);
    }

};

