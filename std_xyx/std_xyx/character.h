#pragma once

#include "game_ani.h"
#include "game_collision_box.h"

// ��ɫ����
class Character:public GameObj
{
public:
    Character();
    virtual ~Character();

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_hurt();

    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;

    /// <summary>
    /// �ܻ�ˢ��Ѫ��
    /// </summary>
    void decrease_hp();
    /// <summary>
    /// ��ȡѪ��
    /// </summary>
    /// <returns></returns>
    int get_hp() const;
    /// <summary>
    /// ��������ģ��
    /// </summary>
    /// <param name="flag"></param>
    void set_gravity_enabled(bool flag);
    /// <summary>
    /// ��ȡ������ײ��
    /// </summary>
    /// <returns></returns>
    GameCollisionBox* get_hit_box();
    /// <summary>
    /// ��ȡ�ܻ���ײ��
    /// </summary>
    /// <returns></returns>
    GameCollisionBox* get_hurt_box();
    /// <summary>
    /// �趨�޵�״̬
    /// </summary>
    /// <returns></returns>
    void make_invulnerable();
    /// <summary>
    /// �л�״̬
    /// </summary>
    /// <param name="id">״̬ID</param>
    void switch_state(const std::string& id);
    /// <summary>
    /// ���ö���
    /// </summary>
    /// <param name="id">����ID</param>
    void set_animation(const Ani_Res& res);


protected:
    int hp = 10;                                            // ��ɫ����ֵ
    Vector2 velocity;                                       // ��ɫ�ٶ�
    bool is_facing_left = true;                             // ��ǰ��ɫ�Ƿ�����
    //StateMachine state_machine;                           // ��ɫ�߼�״̬��
    bool enable_gravity = false;                            // ��������ģ��
    bool is_invulnerable = false;                           // ��ǰ�Ƿ��޵�
    Timer timer_invulnerable_blink;                         // �޵���˸״̬��ʱ��
    Timer timer_invulnerable_status;                        // �޵�״̬��ʱ��
    bool is_blink_invisible = false;                        // ��ǰ�Ƿ�����˸�Ĳ��ɼ�֡
    GameCollisionBox* hit_box = nullptr;                    // ������ײ��
    GameCollisionBox* hurt_box = nullptr;                   // �ܻ���ײ��
    GameAni* current_ani = nullptr;                         // ��ǰ��ɫ����
    std::unordered_map < std::string, Ani_Res > ani_pool;   // ��ɫ������ 
};