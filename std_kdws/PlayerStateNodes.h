#pragma once
#include "Timer.h"
#include "StateNode.h"
/// <summary>
/// 角色攻击状态节点
/// </summary>
class PlayerAttackState :
    public StateNode
{
public:
    PlayerAttackState();
    ~PlayerAttackState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;

private:
    Timer timer;

private:
    /// <summary>
    /// 更新攻击碰撞箱位置
    /// </summary>
    void update_hit_box_position();
};
/// <summary>
/// 角色死亡状态节点
/// </summary>
class PlayerDeadState :
    public StateNode
{
public:
    PlayerDeadState();
    ~PlayerDeadState() = default;

    void on_enter() override;
    void on_update(float delta) override;

private:
    Timer timer;
};
/// <summary>
/// 角色坠落状态节点
/// </summary>
class PlayerFallState :
    public StateNode
{
public:
    PlayerFallState() = default;
    ~PlayerFallState() = default;

    void on_enter() override;
    void on_update(float delta) override;
};
/// <summary>
/// 角色闲置状态节点
/// </summary>
class PlayerIdleState :
    public StateNode
{
public:
    PlayerIdleState() = default;
    ~PlayerIdleState() = default;

    void on_enter() override;
    void on_update(float delta) override;
};
/// <summary>
/// 角色跳跃状态节点
/// </summary>
class PlayerJumpState :
    public StateNode
{
public:
    PlayerJumpState() = default;
    ~PlayerJumpState() = default;

    void on_enter() override;
    void on_update(float delta) override;
};
/// <summary>
/// 角色翻滚状态节点
/// </summary>
class PlayerRollState :
    public StateNode
{
public:
    PlayerRollState();
    ~PlayerRollState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;

private:
    Timer timer;
};
/// <summary>
/// 角色奔跑状态节点
/// </summary>
class PlayerRunState :
    public StateNode
{
public:
    PlayerRunState() = default;
    ~PlayerRunState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;
};

