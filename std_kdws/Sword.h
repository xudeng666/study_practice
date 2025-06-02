#pragma once

#include "animation.h"
#include "CollisionBox.h"
/*������*/
class Sword
{
public:
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="position">λ��</param>
    /// <param name="move_left">�Ƿ�����</param>
    Sword(const Vector2& position, bool move_left);
    ~Sword();

    void on_update(float delta);
    void on_draw();
    /// <summary>
    /// �Ƿ���Ч
    /// </summary>
    /// <returns>true/false</returns>
    bool check_valid() const
    {
        return is_valid;
    }

private:
    //�ƶ��ٶ�
    const float SPEED_MOVE = 1250.0f;

private:
    Vector2 position;   // λ��
    Vector2 velocity;   // �ٶ�
    Animation animation;    // ����
    bool is_valid = true;   // �Ƿ���Ч����Ч���Ƴ���
    CollisionBox* collision_box = nullptr;  // ��ײ��
};

