#pragma once
#include "Timer.h"
#include "StateNode.h"
/**
* ����״̬
*@date 		2025-6-2
*/
/// <summary>
/// ��׼״̬
/// ���г�̵�ǰ�ã���ͣ0.5����л����
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
/// ���г��״̬
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
    /// ����ٶ�
    /// </summary>
    const float SPEED_DASH = 1500.0f;
};
/// <summary>
/// ������״̬
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
    /// ����ٶ�
    /// </summary>
    const float SPEED_DASH = 1000.0f;
private:
    Timer timer;
};
/// <summary>
/// ����״̬
/// </summary>
class EnemyDeadState : public StateNode
{
public:
    EnemyDeadState() = default;
    ~EnemyDeadState() = default;

    void on_enter() override;
};
/// <summary>
/// ����״̬
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
/// ����״̬
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
/// ��Ծ״̬
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
/// ����״̬
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
    const float MIN_DIS = 350.0f;//�ͽ�ɫ������룬С�����ֵ���л�״̬���ٱ���
    const float SPEED_RUN = 500.0f;//�ܶ��ٶ�
};
/// <summary>
/// ����״̬
/// ������ǰ�ã�0.5����л����
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
/// �ͷŴ���
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
/// �ͷ�˿��
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
/// �ӽ�״̬
/// </summary>
class EnemyThrowSwordState : public StateNode
{
public:
    EnemyThrowSwordState();
    ~EnemyThrowSwordState() = default;

    void on_enter() override;
    void on_update(float delta) override;
private:
    Timer timer_throw;//�ӽ�������ʱ��
    Timer timer_switch;//�ӽ�״̬������ʱ��
};