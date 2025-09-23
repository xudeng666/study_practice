#pragma once

#include "character_xcz.h"
#include "bullet_xcz.h"

#include <vector>

class Player_xcz :public CharacterXcz
{
public:
    Player_xcz() = default;
    virtual ~Player_xcz() override;

    Player_xcz(const std::string& id) : CharacterXcz(id) {}
    Player_xcz(const std::string& id, int num) : CharacterXcz(id, num) {}

    DEFINE_TYPE_NAME(Player_xcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_move(float delta) override;
    virtual void set_face(bool is_left) override;
    /// <summary>
    /// 添加子弹
    /// </summary>
    /// <param name="num">子弹数量</param>
    void add_bullet(const int num);
    /// <summary>
    /// 减少子弹数量
    /// </summary>
    /// <param name="num"></param>
    void reduce_bullet(const int num);
    /*获取子弹数量*/
    int get_bullet_num();
    /*设置子弹数量*/
    void set_bullet_num(const int num);
    /*子弹旋转移动*/
    void move_bullet(float delta);

private:
    std::vector<TreeNode_WP> bullet_list;
    // 子弹数量
    int bul_num = 0;
    // 子弹飞行半径
    int bul_radius = 120;
    // 子弹角度
    float bul_degrees = 0;
    // 子弹角速度(度/秒)
    float angle_speed = 90;
};

INIT_TYPE_NAME(Player_xcz);