#pragma once
#include "game_img.h"
#include "combatant.h"

/*�ӵ�����*/
class Bullet :public GameObj, public Combatant
{
public:
    Bullet() = default;
    virtual ~Bullet() = default;

    void set_velocity(const Vector2& vel);
    const Vector2& get_velocity() const;
    /*��ȡ�ƶ��ٶ�*/
    void set_speed(const float val);
    /*��ȡ�ƶ��ٶ�*/
    const float get_speed() const;
    /*�����˺�ֵ*/
    void set_damage(const int val);
    /*��ȡ�˺�ֵ*/
    const int get_damage() const;
    /*�����Ƿ���Ч*/
    void set_valid(bool flag);
    /*��ȡ�Ƿ���Ч*/
    bool get_valid()const;
    /*�����Ƿ���Ƴ�*/
    void set_can_remove(bool flag);
    /*��ȡ�Ƿ���Ƴ�*/
    bool check_can_remove()const;

protected:
    float speed_move = 0.0f;                // �ӵ��ƶ��ٶ�
    Vector2 velocity;                       // �ӵ��ٶ�
    int damage = 1;                        // �ӵ��˺�
    bool valid = true;                      // �ӵ��Ƿ���Ч
    bool can_remove = false;                // �ӵ��Ƿ���Ա��Ƴ�
};

