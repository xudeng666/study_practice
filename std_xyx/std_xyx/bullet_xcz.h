#pragma once
#include "bullet.h"
#include "game_img.h"

class BulletXcz :public Bullet
{
public:
    BulletXcz() = default;
    ~BulletXcz() = default;

    DEFINE_TYPE_NAME(BulletXcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
protected:
    TreeNode_WP img;
};

INIT_TYPE_NAME(BulletXcz);