#pragma once
#include "bullet_xcz.h"

class BulletBox :
    public GameObj
{
public:
    BulletBox() = default;
    virtual ~BulletBox() override;

    //virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    //virtual void on_render() override;

    /// <summary>
    /// 添加子弹
    /// </summary>
    /// <param name="num">添加数量</param>
    void add_bullet(int num);
    /// <summary>
    /// 减少子弹数量
    /// </summary>
    /// <param name="num">减少数量</param>
    void reduce_bullet(int num);
    /*获取子弹数量*/
    int get_bullet_num();
    /*设置子弹数量*/
    void set_bullet_num(const int num);
    /*子弹旋转移动*/
    void move_bullet(float delta);

private:
    // 显示子弹数量
    int bul_num = 0;
    // 子弹飞行半径
    int bul_radius = 120;
    // 子弹飞行角度
    float bul_degrees = 0;
    // 子弹角速度(度/秒)
    float angle_speed = 90;
};

