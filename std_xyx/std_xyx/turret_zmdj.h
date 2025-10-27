#pragma once
#include "game_ani.h"

/*炮塔类*/
class TurretZmdj : public GameImg
{
public:
    TurretZmdj() = default;
    virtual ~TurretZmdj() = default;

    TurretZmdj(const std::string& id) : GameImg(id) {}
    TurretZmdj(const std::string& id, int num) : GameImg(id, num) {}

    DEFINE_TYPE_NAME(TurretZmdj);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;

private:
    TreeNode_WP barrel_fire;        // 炮身(开火)
    TreeNode_WP barrel;             // 炮身
    TreeNode_WP crosshair;          // 准心

    float barrel_speed = 0.04f;		// 炮管射速
};

