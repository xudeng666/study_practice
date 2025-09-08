#include "character_xcz.h"


CharacterXcz::CharacterXcz()
{
    img_shade = new GameImg();
    add_children(img_shade);
    add_children(current_ani);
    std::fill(move_status, move_status + 4, false);
}

CharacterXcz::~CharacterXcz()
{
    Character::~Character();
}

void CharacterXcz::on_enter()
{
    // 初始化 
    std::fill(move_status, move_status + 4, false);
    Character::on_enter();
}

void CharacterXcz::on_exit()
{
    // 反初始化
    std::fill(move_status, move_status + 4, false);
    Character::on_exit();
}

void CharacterXcz::on_input(const SDL_Event& event)
{
    // 基类留空 只有玩家角色可操控
    Character::on_input(event);
}

void CharacterXcz::on_update(float delta)
{
    Character::on_update(delta);
}

void CharacterXcz::on_render()
{
    Character::on_render();
}

void CharacterXcz::on_hurt()
{
    Character::on_hurt();
}

void CharacterXcz::on_hit()
{
    Character::on_hit();
}

void CharacterXcz::on_move(float delta)
{
}

void CharacterXcz::set_interval()
{
    float val = step_length / current_ani->get_res_num() / speed;
    current_ani->set_interval(val);
}

void CharacterXcz::set_move_status(int sub, bool flg)
{
    move_status[sub] = flg;
}

void CharacterXcz::set_step_length(float val)
{
    step_length = val;
}

void CharacterXcz::set_speed(float val)
{
    speed = val;
}

void CharacterXcz::set_face(bool is_left)
{
}
