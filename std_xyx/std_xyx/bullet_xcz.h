#pragma once
#include "bullet.h"

class BulletXcz :public Bullet
{
public:
    BulletXcz();
    ~BulletXcz();

    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
protected:
};

