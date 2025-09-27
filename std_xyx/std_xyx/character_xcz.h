#pragma once
#include "character.h"

/// <summary>
/// 幸存者角色基类
/// </summary>
class CharacterXcz :
    public Character
{
public:
    CharacterXcz() = default;
    virtual ~CharacterXcz() = default;

    CharacterXcz(const std::string& id) : Character(id) {}
    CharacterXcz(const std::string& id, int num) : Character(id, num) {}

    DEFINE_TYPE_NAME(CharacterXcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hurt() override;
    /// <summary>
    /// 受到攻击
    /// </summary>
    virtual void on_hit() override;
    /// <summary>
    /// 移动
    /// </summary>
    virtual void on_move(float delta);
    /// <summary>
    /// 设置角色朝向
    /// </summary>
    /// <param name="is_left">是否向左</param>
    virtual void set_face(bool is_left);
    /// <summary>
    /// 设置动画帧间隔时长（依据动画移动速度）
    /// </summary>
    void set_interval();
    /// <summary>
    /// 设置移动状态
    /// </summary>
    /// <param name="sub">下标0123</param>
    /// <param name="flg">移动/停止 true/false</param>
    void set_move_status(int sub, bool flg);
    /// <summary>
    /// 设置角色步长
    /// </summary>
    /// <param name="val"></param>
    void set_step_length(float val);
    /// <summary>
    /// 设置角色速度
    /// </summary>
    /// <param name="val"></param>
    void set_speed(float val);

protected:
    // 脚底阴影
    TreeNode_WP img_shade;
    // 移动按钮状态（上下左右-0123）
    bool move_status[4];
    // 步长
    float step_length = 48;
    // 移动速度(像素/秒)
    float speed = 50;
};