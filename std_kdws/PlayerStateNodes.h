#pragma once
#include "Timer.h"
#include "StateNode.h"
/// <summary>
/// ��ɫ����״̬�ڵ�
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
    /// ���¹�����ײ��λ��
    /// </summary>
    void update_hit_box_position();
};
/// <summary>
/// ��ɫ����״̬�ڵ�
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
/// ��ɫ׹��״̬�ڵ�
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
/// ��ɫ����״̬�ڵ�
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
/// ��ɫ��Ծ״̬�ڵ�
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
/// ��ɫ����״̬�ڵ�
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
/// ��ɫ����״̬�ڵ�
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

