#pragma once
#include "Vector2.h"
#include "PlayerID.h"
#include "Camera.h"

#include <functional>
#include <graphics.h>

extern bool is_debug;

/*�ӵ�����*/
class Bullet
{
public:
    Bullet() = default;
    ~Bullet() = default;
    /*�����˺�ֵ*/
    void set_damage(int val)
    {
        damage = val;
    }
    /*��ȡ�˺�ֵ*/
    int get_damage()
    {
        return damage;
    }
    /*����λ��*/
    void set_position(float x, float y)
    {
        position.x = x, position.y = y;
    }
    /*��ȡλ��*/
    const Vector2& get_position() const
    {
        return position;
    }
    /*��ȡ����λ��*/
    Vector2 get_center_position()
    {
        return { position.x + size.x / 2,position.x + size.y / 2 };
    }
    /*����λ��*/
    void set_size(float x, float y)
    {
        size.x = x, size.y = y;
    }
    /*��ȡλ��*/
    const Vector2& get_size() const
    {
        return size;
    }
    /*�����ٶ�*/
    void set_velocity(float x, float y)
    {
        velocity.x = x, velocity.y = y;
    }
    /*��ȡ�ٶ�*/
    const Vector2& get_velocity() const
    {
        return velocity;
    }
    /*���õж�id*/
    void set_collide_target(PlayerID target)
    {
        target_id = target;
    }
    /*��ȡ�ж�id*/
    PlayerID get_collide_target() const
    {
        return target_id;
    }
    /*���ûص�����*/
    void set_callback(std::function<void()> callback)
    {
        this->callback = callback;
    }
    /*�����Ƿ���Ч*/
    void set_valid(bool flag)
    {
        valid = flag;
    }
    /*��ȡ�Ƿ���Ч*/
    bool get_valid()const
    {
        return valid;
    }
    /*�����Ƿ���Ƴ�*/
    void set_can_remove(bool flag)
    {
        can_remove = flag;
    }
    /*��ȡ�Ƿ���Ƴ�*/
    bool check_can_remove()const
    {
        return can_remove;
    }
    /*�ӵ���ײ*/
    virtual void on_collide()
    {
        if (callback)
        {
            callback();
        }
    }
    /*
    * �ӵ���ײ���
    *@pos   ��ײ����λ��
    *@size  ��ײ�����С
    */
    virtual bool check_cllide(const Vector2& pos,const Vector2& size)
    {
        return checkPointToRect<float>(position.x + this->size.x / 2, position.y + this->size.y / 2, 
            pos.x, pos.x + size.x, pos.y, pos.y + size.y);
    }

    virtual void on_update(int delta)
    {
    }

    virtual void on_draw(const Camera& camera)const
    {
        if (is_debug)
        {
            setlinecolor(RGB(255, 0, 0));
            setfillcolor(RGB(255, 0, 0));
            rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
            solidcircle(position.x + size.x / 2, position.y + size.y / 2, 5);
        }
    }
protected:
    Vector2 size;                      // �ӵ��ߴ�
    Vector2 position;                  // �ӵ�λ��
    Vector2 velocity;                  // �ӵ��ٶ�
    int damage = 10;                   // �ӵ��˺�
    bool valid = true;                 // �ӵ��Ƿ���Ч
    bool can_remove = false;           // �ӵ��Ƿ���Ա��Ƴ�
    std::function<void()> callback;    // �ӵ���ײ�ص�����
    PlayerID target_id = PlayerID::P1; // �ӵ���׼���ID

protected:
    /*����ӵ��ɳ���Ļ*/
    bool check_out_screen()
    {
        return (position.x + size.x < -10
            || position.x > getwidth() + 10
            || position.y + size.y < -10
            || position.y > getheight() + 10);
    }

};

