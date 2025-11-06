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
    void open_fire(float delta);

private:
    TreeNode_WP barrel_ani;         // 炮身(开火)
    TreeNode_WP barrel_img;         // 炮身(停火)
    TreeNode_WP barrel;             // 炮身

    Vector2 pos_battery;            // 炮台中心坐标
    float barrel_speed = 0.04f;		// 炮管射速
    float length_barrel = 105;      // 炮管长度
    bool is_cool_down = true;		// 是否冷却结束
    bool is_fire_key_down = false;	// 开火键是否按下
};

