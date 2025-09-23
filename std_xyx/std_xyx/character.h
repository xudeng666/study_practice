#pragma once

#include "game_ani.h"
#include "combatant.h"

// 角色基类
class Character:public GameObj, public Combatant
{
public:
    Character() = default;
    virtual ~Character();

    Character(const std::string& id) : GameObj(id) {}
    Character(const std::string& id, int num) : GameObj(id, num) {}

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hurt();
    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hit();


    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;

    /// <summary>
    /// 受击掉血
    /// </summary>
    /// <param name="val">伤害值</param>
    void decrease_hp(int val);
    /// <summary>
    /// 获取血量
    /// </summary>
    /// <returns></returns>
    int get_hp() const;
    /// <summary>
    /// 设置血量
    /// </summary>
    /// <param name="val"></param>
    void set_hp(const int val);
    /// <summary>
    /// 设置动画
    /// </summary>
    /// <param name="id">动画ID</param>
    void set_animation(const Ani_Res& res);
    /// <summary>
    /// 角色屏幕范围锁定
    /// </summary>
    void lock_in_screen();
    /// <summary>
    /// 获取存活状态
    /// </summary>
    /// <returns></returns>
    bool get_alive() const;
    /// <summary>
    /// 获取删除状态
    /// </summary>
    /// <returns></returns>
    bool get_valid() const;


protected:
    bool valid = true;                                      // 是否可以删除
    bool alive = true;                                      // 是否存活
    bool check_out_of_screen = true;                        // 是否启用超出屏幕范围判定
    int hp = 10;                                            // 角色生命值
    Vector2 velocity;                                       // 角色速度
    TreeNode_WP current_ani;                                // 当前角色动画
    std::unordered_map < std::string, Ani_Res > ani_pool;   // 角色动画池
};