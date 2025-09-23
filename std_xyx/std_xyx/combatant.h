#pragma once

#include "game_collision_box.h"

/*战斗对象基类*/
class Combatant
{
public:
    Combatant();
    virtual ~Combatant();

    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hurt();
    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hit();

    /*设置碰撞受击函数*/
    void set_on_hurt_fun(std::function<void()> call_back);
    /*设置碰撞攻击函数*/
    void set_on_hit_fun(std::function<void()> call_back);

    TreeNode_SP get_hit_box();
    /// <summary>
    /// 获取受击碰撞箱
    /// </summary>
    /// <returns></returns>
    TreeNode_SP get_hurt_box();

protected:
    TreeNode_WP hit_box;                    // 攻击碰撞箱
    TreeNode_WP hurt_box;                   // 受击碰撞箱
    std::function<void()> on_hurt_fun = nullptr;	        // 受击回调函数
    std::function<void()> on_hit_fun = nullptr;	            // 攻击回调函数
};

