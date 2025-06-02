#pragma once
#include "Timer.h"
#include "StateNode.h"
/**
* 敌人状态
*@date 		2025-6-2
*/
/// <summary>
/// 瞄准状态
/// 空中冲刺的前置，悬停0.5秒后切换冲刺
/// </summary>
class EnemyAimState:
	public StateNode
{
public:
    EnemyAimState();
    ~EnemyAimState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    Timer timer;
};
/// <summary>
/// 空中冲刺状态
/// </summary>
class EnemyDashInAirState : public StateNode
{
public:
    EnemyDashInAirState() = default;
    ~EnemyDashInAirState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;
private:
    /// <summary>
    /// 冲刺速度
    /// </summary>
    const float SPEED_DASH = 1500.0f;
};
/// <summary>
/// 地面冲刺状态
/// </summary>
class EnemyDashOnFloorState : public StateNode
{
public:
    EnemyDashOnFloorState();
    ~EnemyDashOnFloorState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    /// <summary>
    /// 冲刺速度
    /// </summary>
    const float SPEED_DASH = 1000.0f;
private:
    Timer timer;
};
/// <summary>
/// 死亡状态
/// </summary>
class EnemyDeadState : public StateNode
{
public:
    EnemyDeadState() = default;
    ~EnemyDeadState() = default;

    void on_enter() override;
};
/// <summary>
/// 下落状态
/// </summary>
class EnemyFallState : public StateNode
{
public:
    EnemyFallState() = default;
    ~EnemyFallState() = default;

    void on_enter() override;
    void on_update(float delta) override;
};
/// <summary>
/// 闲置状态
/// </summary>
class EnemyIdleState : public StateNode
{
public:
    EnemyIdleState();
    ~EnemyIdleState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;
private:
    Timer timer;
};
/// <summary>
/// 跳跃状态
/// </summary>
class EnemyJumpState : public StateNode
{
public:
    EnemyJumpState() = default;
    ~EnemyJumpState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    const float SPEED_JUMP = 1000.0f;
};
/// <summary>
/// 奔跑状态
/// </summary>
class EnemyRunState : public StateNode
{
public:
    EnemyRunState() = default;
    ~EnemyRunState() = default;

    void on_enter() override;
    void on_update(float delta) override;
    void on_exit() override;
private:
    const float MIN_DIS = 350.0f;//和角色横向距离，小于这个值则切换状态不再奔跑
    const float SPEED_RUN = 500.0f;//跑动速度
};
/// <summary>
/// 蹲下状态
/// 地面冲刺前置，0.5秒后切换冲刺
/// </summary>
class EnemySquatState : public StateNode
{
public:
    EnemySquatState();
    ~EnemySquatState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    Timer timer;
};
/// <summary>
/// 释放刺球
/// </summary>
class EnemyThrowBarbState : public StateNode
{
public:
    EnemyThrowBarbState();
    ~EnemyThrowBarbState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    Timer timer;
};
/// <summary>
/// 释放丝线
/// </summary>
class EnemyThrowSilkState : public StateNode
{
public:
    EnemyThrowSilkState();
    ~EnemyThrowSilkState() = default;

    void on_enter() override;
    void on_update(float delta) override;
public:
    Timer timer;
};
/// <summary>
/// 扔剑状态
/// </summary>
class EnemyThrowSwordState : public StateNode
{
public:
    EnemyThrowSwordState();
    ~EnemyThrowSwordState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    Timer timer_throw;//扔剑动作定时器
    Timer timer_switch;//扔剑状态持续定时器
};