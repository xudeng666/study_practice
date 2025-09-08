#include "combatant.h"
#include "collision_mgr.h"


Combatant::Combatant()
{
    hit_box = CollisionMgr::instance()->creatCollisionBox();
    hurt_box = CollisionMgr::instance()->creatCollisionBox();
}

Combatant::~Combatant()
{
    CollisionMgr::instance()->destroyCollisionBox(hit_box);
    CollisionMgr::instance()->destroyCollisionBox(hurt_box);
}

void Combatant::on_hurt()
{
    if (on_hurt_fun)
    {
        on_hurt_fun();
    }
}

void Combatant::on_hit()
{
    if (on_hit_fun)
    {
        on_hit_fun();
    }
}

void Combatant::set_on_hurt_fun(std::function<void()> call_back)
{
    if (call_back)
    {
        on_hurt_fun = call_back;
    }
}

void Combatant::set_on_hit_fun(std::function<void()> call_back)
{
    if (call_back)
    {
        on_hit_fun = call_back;
    }
}

GameCollisionBox* Combatant::get_hit_box()
{
    return hit_box;
}

GameCollisionBox* Combatant::get_hurt_box()
{
    return hurt_box;
}