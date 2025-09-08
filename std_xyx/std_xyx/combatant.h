#pragma once

//#include "game_obj.h"
#include "game_collision_box.h"

/*ս���������*/
class Combatant// :public GameObj
{
public:
    Combatant();
    virtual ~Combatant();

    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hurt();
    /// <summary>
    /// �ܵ�����
    /// </summary>
    virtual void on_hit();

    /*������ײ�ܻ�����*/
    void set_on_hurt_fun(std::function<void()> call_back);
    /*������ײ��������*/
    void set_on_hit_fun(std::function<void()> call_back);

    GameCollisionBox* get_hit_box();
    /// <summary>
    /// ��ȡ�ܻ���ײ��
    /// </summary>
    /// <returns></returns>
    GameCollisionBox* get_hurt_box();


protected:
    GameCollisionBox* hit_box = nullptr;                    // ������ײ��
    GameCollisionBox* hurt_box = nullptr;                   // �ܻ���ײ��
    std::function<void()> on_hurt_fun = nullptr;	        // �ܻ��ص�����
    std::function<void()> on_hit_fun = nullptr;	            // �����ص�����
};

