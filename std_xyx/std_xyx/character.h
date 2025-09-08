#pragma once

#include "game_ani.h"
#include "combatant.h"

// ��ɫ����
class Character:public GameObj, public Combatant
{
public:
    Character();
    virtual ~Character();

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hurt();
    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hit();


    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;

    /// <summary>
    /// �ܻ���Ѫ
    /// </summary>
    /// <param name="val">�˺�ֵ</param>
    void decrease_hp(int val);
    /// <summary>
    /// ��ȡѪ��
    /// </summary>
    /// <returns></returns>
    int get_hp() const;
    /// <summary>
    /// ����Ѫ��
    /// </summary>
    /// <param name="val"></param>
    void set_hp(const int val);
    /// <summary>
    /// ���ö���
    /// </summary>
    /// <param name="id">����ID</param>
    void set_animation(const Ani_Res& res);
    /// <summary>
    /// ��ɫ��Ļ��Χ����
    /// </summary>
    void lock_in_screen();


protected:
    bool check_out_of_screen = true;                        // �Ƿ����ó�����Ļ��Χ�ж�
    int hp = 10;                                            // ��ɫ����ֵ
    Vector2 velocity;                                       // ��ɫ�ٶ�
    GameAni* current_ani = nullptr;                         // ��ǰ��ɫ����
    std::unordered_map < std::string, Ani_Res > ani_pool;   // ��ɫ������ 
};