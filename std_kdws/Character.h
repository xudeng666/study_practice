#pragma once
#include "vector2.h"
#include "animation.h"
#include "CollisionBox.h"
#include "StateMachine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

/**
*@brief 	�������
*@author	xd
*@date 		2025-5-29
*/
class Character
{
protected:
    /*������*/
    struct AnimationGroup
    {
        Animation left;
        Animation right;
    };
protected:
    const float FLOOR_Y = 620;                                      // �ذ����ֱ��������
    const float GRAVITY = 980 * 2;                                  // ������С

protected:
    int hp = 10;                                                    // ��ɫ����ֵ
    Vector2 position;                                               // ��ɫ�ŵ�λ��
    Vector2 velocity;                                               // ��ɫ�ٶ�
    float logic_height = 0;                                         // ��ɫ���߼��߶�
    bool is_facing_left = true;                                     // ��ǰ��ɫ�Ƿ�����
    StateMachine state_machine;                                     // ��ɫ�߼�״̬��
    bool enable_gravity = true;                                     // ��������ģ��
    bool is_invulnerable = false;                                   // ��ǰ�Ƿ��޵�
    Timer timer_invulnerable_blink;                                 // �޵���˸״̬��ʱ��
    Timer timer_invulnerable_status;                                // �޵�״̬��ʱ��
    bool is_blink_invisible = false;                                // ��ǰ�Ƿ�����˸�Ĳ��ɼ�֡
    CollisionBox* hit_box = nullptr;                                // ������ײ��
    CollisionBox* hurt_box = nullptr;                               // �ܻ���ײ��
    AnimationGroup* current_animation = nullptr;                    // ��ǰ��ɫ����
    std::unordered_map<std::string, AnimationGroup> animation_pool; // ��ɫ������ 
public:
    Character();
    ~Character();
    /// <summary>
    /// �ܵ�������ˢ��Ѫ��
    /// </summary>
    void decrease_hp();

    int get_hp() const
    {
        return hp;
    }

    void set_position(const Vector2& position)
    {
        this->position = position;
    }

    const Vector2& get_position() const
    {
        return position;
    }

    void set_velocity(const Vector2& velocity)
    {
        this->velocity = velocity;
    }
    const Vector2& get_velocity() const
    {
        return velocity;
    }

    /**
    *@brief 	��ȡ��������
    */
    Vector2 get_logic_center() const
    {
        return Vector2(position.x, position.y - logic_height / 2);
    }
    /// <summary>
    /// ��������ģ��
    /// </summary>
    /// <param name="flag"></param>
    void set_gravity_enabled(bool flag)
    {
        enable_gravity = flag;
    }
    /// <summary>
    /// ��ȡ������ײ��
    /// </summary>
    /// <returns></returns>
    CollisionBox* get_hit_box()
    {
        return hit_box;
    }
    /// <summary>
    /// ��ȡ�ܻ���ײ��
    /// </summary>
    /// <returns></returns>
    CollisionBox* get_hurt_box()
    {
        return hurt_box;
    }

    /**
    *@brief 	�Ƿ��ڵ�����
    *@return 	true/false
    */
    bool is_on_floor() const
    {
        return position.y >= FLOOR_Y;
    }
    /**
    *@brief 	��ȡ����߶�
    */
    float get_floor_y() const
    {
        return FLOOR_Y;
    }
    /*�趨�޵�״̬*/
    void make_invulnerable()
    {
        is_invulnerable = true;
        timer_invulnerable_status.restart();
    }

    virtual void on_input(const ExMessage& msg);
    virtual void on_update(float delta);
    virtual void on_draw();

    virtual void on_hurt();
    /*�л�״̬*/
    void switch_state(const std::string& id);
    /*���ö���*/
    void set_animation(const std::string& id);
};