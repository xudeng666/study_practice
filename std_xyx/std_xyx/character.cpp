#include "character.h"
#include "collision_mgr.h"
#include "game_wnd.h"


Character::Character()
{
    current_ani = new GameAni();
    current_ani->set_ID("ani");
    hit_box = CollisionMgr::instance()->creatCollisionBox();
    hurt_box = CollisionMgr::instance()->creatCollisionBox();
    
    add_children(current_ani);
}

Character::~Character()
{
    CollisionMgr::instance()->destroyCollisionBox(hit_box);
    CollisionMgr::instance()->destroyCollisionBox(hurt_box);
}

void Character::on_enter()
{
    // 初始化
}

void Character::on_exit()
{
    // 反初始化
}

void Character::on_input(const SDL_Event& event)
{
    // 基类留空 只有玩家角色可操控
}

void Character::on_update(float delta)
{
    //state_machine.on_update(delta);
    
}

void Character::on_render()
{
    
}

void Character::on_hurt()
{
}

void Character::set_velocity(const Vector2& vel)
{
    velocity = vel;
}

const Vector2& Character::get_velocity() const
{
    return velocity;
}

void Character::decrease_hp(int val)
{
    hp -= val;
    on_hurt();
}

int Character::get_hp() const
{
    return hp;
}

GameCollisionBox* Character::get_hit_box()
{
    return hit_box;
}

GameCollisionBox* Character::get_hurt_box()
{
    return hurt_box;
}

void Character::set_animation(const Ani_Res& res)
{
    current_ani->set_res_name(res);
}

void Character::lock_in_screen()
{
    if (!check_out_of_screen) return;

    SDL_FRect p = get_FRect();
    if ((velocity.x + p.x) < 0 || (velocity.x + p.x + p.w) > GameWnd::instance()->get_width())
    {
        velocity.x = 0;
    }

    if ((velocity.y + p.y) < 0 || (velocity.y + p.y + p.h) > GameWnd::instance()->get_height())
    {
        velocity.y = 0;
    }
}