#pragma once
#include "bullet.h"

class BulletZmdj :
    public Bullet
{
public:
    BulletZmdj() = default;
    ~BulletZmdj() = default;

    BulletZmdj(const std::string& id) : Bullet(id) {}
    BulletZmdj(const std::string& id, int num) : Bullet(id, num) {}

    DEFINE_TYPE_NAME(BulletZmdj);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
protected:
    TreeNode_WP img;
};

