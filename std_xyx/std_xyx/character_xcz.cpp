#include "character_xcz.h"


CharacterXcz::CharacterXcz()
{
    img_shade = new GameImg();
    add_children(img_shade);
    add_children(current_ani);
}

CharacterXcz::~CharacterXcz()
{
    Character::~Character();
}

void CharacterXcz::on_enter()
{
    // 初始化
}

void CharacterXcz::on_exit()
{
    // 反初始化
}

void CharacterXcz::on_input(const SDL_Event& event)
{
    // 基类留空 只有玩家角色可操控
}

void CharacterXcz::on_update(float delta)
{
    //state_machine.on_update(delta);

}

void CharacterXcz::on_render()
{

}

void CharacterXcz::on_hurt()
{
}

void CharacterXcz::on_move(float delta)
{
    float x1 = move_status[2] ? -1 : 0;
    float x2 = move_status[3] ? 1 : 0;
    float y1 = move_status[0] ? -1 : 0;
    float y2 = move_status[1] ? 1 : 0;
    Vector2 t = { x1 + x2, y1 + y2 };
    t = t.normalize();
    velocity = t* speed* delta;
    lock_in_screen();
    if (velocity.x != 0)
    {
        set_face(velocity.x < 0);
    }
    position += velocity;
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
