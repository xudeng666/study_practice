#pragma once

#include "character_xcz.h"
#include "bullet_xcz.h"

#include <vector>

class Player_xcz :public CharacterXcz
{
public:
    Player_xcz();
    virtual ~Player_xcz() override;

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_move(float delta) override;
    virtual void set_face(bool is_left) override;
    /// <summary>
    /// ����ӵ�
    /// </summary>
    /// <param name="num">�ӵ�����</param>
    void add_bullet(const int num);
    /// <summary>
    /// �����ӵ�����
    /// </summary>
    /// <param name="num"></param>
    void reduce_bullet(const int num);
    /*��ȡ�ӵ�����*/
    int get_bullet_num();
    /*�����ӵ�����*/
    void set_bullet_num(const int num);
    /*�ӵ���ת�ƶ�*/
    void move_bullet(float delta);

private:
    std::vector<BulletXcz*> bullet_list;
    // �ӵ�����
    int bul_num = 0;
    // �ӵ����а뾶
    int bul_radius = 120;
    // �ӵ��Ƕ�
    float bul_degrees = 0;
    // �ӵ����ٶ�(��/��)
    float angle_speed = 90;
};

