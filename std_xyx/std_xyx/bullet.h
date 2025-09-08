#pragma once
#include "game_img.h"
#include "combatant.h"

/*子弹基类*/
class Bullet :public GameImg, public Combatant
{
public:
    Bullet();
    ~Bullet();

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;
    /*获取移动速度*/
    void set_speed(const float val);
    /*获取移动速度*/
    const float get_speed() const;
    /*设置伤害值*/
    void set_damage(const int val);
    /*获取伤害值*/
    const int get_damage() const;
    /*设置是否有效*/
    void set_valid(bool flag);
    /*获取是否有效*/
    bool get_valid()const;
    /*设置是否可移除*/
    void set_can_remove(bool flag);
    /*获取是否可移除*/
    bool check_can_remove()const;

protected:
    float speed_move = 0.0f;                // 子弹移动速度
    Vector2 velocity;                       // 子弹速度
    int damage = 1;                        // 子弹伤害
    bool valid = true;                      // 子弹是否有效
    bool can_remove = false;                // 子弹是否可以被移除
};

