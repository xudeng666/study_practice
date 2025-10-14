#pragma once
#include "bullet_xcz.h"

class BulletBox :
    public GameObj
{
public:
    BulletBox() = default;
    virtual ~BulletBox() override;

    //virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    //virtual void on_render() override;

    /// <summary>
    /// ����ӵ�
    /// </summary>
    /// <param name="num">�������</param>
    void add_bullet(int num);
    /// <summary>
    /// �����ӵ�����
    /// </summary>
    /// <param name="num">��������</param>
    void reduce_bullet(int num);
    /*��ȡ�ӵ�����*/
    int get_bullet_num();
    /*�����ӵ�����*/
    void set_bullet_num(const int num);
    /*�ӵ���ת�ƶ�*/
    void move_bullet(float delta);

private:
    // ��ʾ�ӵ�����
    int bul_num = 0;
    // �ӵ����а뾶
    int bul_radius = 120;
    // �ӵ����нǶ�
    float bul_degrees = 0;
    // �ӵ����ٶ�(��/��)
    float angle_speed = 90;
};

