#pragma once

#include "game_collision_box.h"

/*ս���������*/
class Combatant
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

    TreeNode_SP get_hit_box();
    /// <summary>
    /// ��ȡ�ܻ���ײ��
    /// </summary>
    /// <returns></returns>
    TreeNode_SP get_hurt_box();

protected:
    TreeNode_WP hit_box;                    // ������ײ��
    TreeNode_WP hurt_box;                   // �ܻ���ײ��
    std::function<void()> on_hurt_fun = nullptr;	        // �ܻ��ص�����
    std::function<void()> on_hit_fun = nullptr;	            // �����ص�����
};

