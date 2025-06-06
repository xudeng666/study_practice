#pragma once
#include "Sword.h"
#include "Barb.h"
#include "Character.h"

class Enemy :
    public Character
{
public:
    Enemy();
    ~Enemy();

    void on_update(float delta) override;
    void on_draw() override;
    /// <summary>
    /// �ܻ�
    /// </summary>
    void on_hurt() override;
    /// <summary>
    /// ���ó���
    /// </summary>
    /// <param name="flag">true��/false��</param>
    void set_facing_left(bool flag)
    {
        is_facing_left = flag;
    }
    /// <summary>
    /// ��ȡ����
    /// </summary>
    /// <returns>true��/false��</returns>
    bool get_facing_left() const
    {
        return is_facing_left;
    }
    /// <summary>
    /// ���ÿ��г��
    /// </summary>
    /// <param name="flag">true/false</param>
    void set_dashing_in_air(bool flag)
    {
        is_dashing_in_air = flag;
    }
    /// <summary>
    /// ���õ�����״̬
    /// </summary>
    /// <param name="flag"></param>
    void set_dashing_on_floor(bool flag)
    {
        is_dashing_on_floor = flag;
    }
    /// <summary>
    /// �Ƿ������
    /// </summary>
    /// <returns></returns>
    bool get_dashing_on_floor() const
    {
        return is_dashing_on_floor;
    }
    /// <summary>
    /// ��Ϊ��˿״̬
    /// </summary>
    /// <param name="flag"></param>
    void set_throwing_silk(bool flag)
    {
        is_throwing_silk = flag;
        collision_box_silk->set_enabled(flag);
    }
    /// <summary>
    /// �Ƿ���˿
    /// </summary>
    /// <returns></returns>
    bool get_throwing_silk() const
    {
        return is_throwing_silk;
    }
    /// <summary>
    /// �ٻ�����
    /// </summary>
    void throw_barbs();
    /// <summary>
    /// �ӽ�
    /// </summary>
    void throw_sword();
    /// <summary>
    /// ���
    /// </summary>
    void on_dash();
    /// <summary>
    /// �ٻ�˿��
    /// </summary>
    void on_throw_silk();

private:
    bool is_throwing_silk = false;//�Ƿ��˿
    bool is_dashing_in_air = false;//�Ƿ���г��
    bool is_dashing_on_floor = false;//�Ƿ������

    Animation animation_silk;//����˿�߶���
    AnimationGroup animation_dash_in_air_vfx;//���г�̶�����
    AnimationGroup animation_dash_on_floor_vfx;//�����̶�����
    Animation* current_dash_animation = nullptr;//��ǰ����

    std::vector<Barb*> barb_list;
    std::vector<Sword*> sword_list;
    CollisionBox* collision_box_silk = nullptr;// ˿����ײ��
};

