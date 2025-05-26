#pragma once
#include "Vector2.h"
#include "PlayerID.h"
#include "Camera.h"

#include <functional>
#include <graphics.h>

extern bool is_debug;

/*子弹基类*/
class Bullet
{
public:
    Bullet() = default;
    ~Bullet() = default;
    /*设置伤害值*/
    void set_damage(int val)
    {
        damage = val;
    }
    /*获取伤害值*/
    int get_damage()
    {
        return damage;
    }
    /*设置位置*/
    void set_position(float x, float y)
    {
        position.x = x, position.y = y;
    }
    /*获取位置*/
    const Vector2& get_position() const
    {
        return position;
    }
    /*获取中心位置*/
    Vector2 get_center_position()
    {
        return { position.x + size.x / 2,position.x + size.y / 2 };
    }
    /*设置位置*/
    void set_size(float x, float y)
    {
        size.x = x, size.y = y;
    }
    /*获取位置*/
    const Vector2& get_size() const
    {
        return size;
    }
    /*设置速度*/
    void set_velocity(float x, float y)
    {
        velocity.x = x, velocity.y = y;
    }
    /*获取速度*/
    const Vector2& get_velocity() const
    {
        return velocity;
    }
    /*设置敌对id*/
    void set_collide_target(PlayerID target)
    {
        target_id = target;
    }
    /*获取敌对id*/
    PlayerID get_collide_target() const
    {
        return target_id;
    }
    /*设置回调函数*/
    void set_callback(std::function<void()> callback)
    {
        this->callback = callback;
    }
    /*设置是否有效*/
    void set_valid(bool flag)
    {
        valid = flag;
    }
    /*获取是否有效*/
    bool get_valid()const
    {
        return valid;
    }
    /*设置是否可移除*/
    void set_can_remove(bool flag)
    {
        can_remove = flag;
    }
    /*获取是否可移除*/
    bool check_can_remove()const
    {
        return can_remove;
    }
    /*子弹碰撞*/
    virtual void on_collide()
    {
        if (callback)
        {
            callback();
        }
    }
    /*
    * 子弹碰撞检测
    *@pos   碰撞对象位置
    *@size  碰撞对象大小
    */
    virtual bool check_cllide(const Vector2& pos,const Vector2& size)
    {
        return checkPointToRect<float>(position.x + this->size.x / 2, position.y + this->size.y / 2, 
            pos.x, pos.x + size.x, pos.y, pos.y + size.y);
    }

    virtual void on_update(int delta)
    {
    }

    virtual void on_draw(const Camera& camera)const
    {
        if (is_debug)
        {
            setlinecolor(RGB(255, 0, 0));
            setfillcolor(RGB(255, 0, 0));
            rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
            solidcircle(position.x + size.x / 2, position.y + size.y / 2, 5);
        }
    }
protected:
    Vector2 size;                      // 子弹尺寸
    Vector2 position;                  // 子弹位置
    Vector2 velocity;                  // 子弹速度
    int damage = 10;                   // 子弹伤害
    bool valid = true;                 // 子弹是否有效
    bool can_remove = false;           // 子弹是否可以被移除
    std::function<void()> callback;    // 子弹碰撞回调函数
    PlayerID target_id = PlayerID::P1; // 子弹瞄准玩家ID

protected:
    /*检测子弹飞出屏幕*/
    bool check_out_screen()
    {
        return (position.x + size.x < -10
            || position.x > getwidth() + 10
            || position.y + size.y < -10
            || position.y > getheight() + 10);
    }

};

