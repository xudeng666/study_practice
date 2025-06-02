#pragma once

#include "animation.h"
#include "CollisionBox.h"
/*
* ������
*/
class Barb
{
public:
    Barb();
    ~Barb();

    void on_update(float delta);
    void on_draw();

    void set_position(const Vector2& position)
    {
        base_position = position;
        current_position = position;
    }

    bool check_valid() const
    {
        return is_valid;
    }
private:
    /*����״̬*/
    enum class Stage
    {
        Idle,//Ĭ��-���¸���
        Aim,//��׼
        Dash,//���
        Break//����
    };

private:
    const float SPEED_DASH = 1500.0f;//�ٶ�

private:
    Timer timer_idle;//Ĭ��״̬��ʱ��
    Timer timer_aim;// ��׼״̬��ʱ��
    int diff_period = 0;//���ֵ�����Ƹ���������ƫ��
    bool is_valid = true;//�Ƿ���Ч
    float total_delta_time = 0;//��¼����������������������ʱ�䣩

    Vector2 velocity;
    Vector2 base_position;//����λ��
    Vector2 current_position;//��ǰλ�ã�����λ����Ϊ�˿��Ƹ�������׼��������Ч����

    Animation animation_loose;// ����-����
    Animation animation_break;// ����-����
    Animation* current_animation = nullptr;//��ǰ����

    Stage stage = Stage::Idle;//��ǰ״̬
    CollisionBox* collision_box = nullptr;//��ײ��

private:
    void on_break();//�������鴦��
};
