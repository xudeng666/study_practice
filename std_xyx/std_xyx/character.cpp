#include "character.h"
#include "collision_mgr.h"


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

void Character::decrease_hp()
{
    if (is_invulnerable) return;

    hp -= 1;
    if (hp > 0)
        make_invulnerable();
    on_hurt();
}

int Character::get_hp() const
{
    return hp;
}

void Character::set_gravity_enabled(bool flag)
{
    enable_gravity = flag;
}

GameCollisionBox* Character::get_hit_box()
{
    return hit_box;
}

GameCollisionBox* Character::get_hurt_box()
{
    return hurt_box;
}

void Character::make_invulnerable()
{
    is_invulnerable = true;
    timer_invulnerable_status.restart();
}

void Character::switch_state(const std::string& id)
{}

void Character::set_animation(const Ani_Res& res)
{
    current_ani->set_res_name(res);
}