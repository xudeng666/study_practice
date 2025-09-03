#pragma once
#include "character_xcz.h"
class Enemy_xcz :public CharacterXcz
{
public:
    Enemy_xcz();
    virtual ~Enemy_xcz() override;

    virtual void on_enter() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_hurt() override;
    virtual void set_face(bool is_left) override;

    // ��Ӹ�����Ŀ�꣨��ң�����ĺ���
    // ��Ӹ���Ŀ�꣬Ѱ·�ĺ���
};

