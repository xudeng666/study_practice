#pragma once

#include "character_xcz.h"

#include <vector>

class Player_xcz :public CharacterXcz
{
public:
    Player_xcz() = default;
    virtual ~Player_xcz() = default;

    Player_xcz(const std::string& id) : CharacterXcz(id) {}
    Player_xcz(const std::string& id, int num) : CharacterXcz(id, num) {}

    DEFINE_TYPE_NAME(Player_xcz);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void on_input(const SDL_Event& event) override;
    virtual void on_update(float delta) override;
    virtual void on_render() override;
    virtual void on_move(float delta) override;
    virtual void set_face(bool is_left) override;
private:
    /*同步玩家坐标*/
    void update_pos();
private:
    /*同步玩家坐标定时器*/
    Timer timer_update_pos;
};