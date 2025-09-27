#pragma once
#include "character_xcz.h"
class Enemy_xcz :public CharacterXcz
{
public:
    Enemy_xcz() = default;
    virtual ~Enemy_xcz() = default;

    Enemy_xcz(const std::string& id) : CharacterXcz(id) {}
    Enemy_xcz(const std::string& id, int num) : CharacterXcz(id, num) {}

    DEFINE_TYPE_NAME(Enemy_xcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_move(float delta);
    virtual void set_face(bool is_left) override;

    // 设置目标（玩家）坐标的函数
    void set_player_pos(Vector2 pos);
protected:
    Vector2 pos_player;
};