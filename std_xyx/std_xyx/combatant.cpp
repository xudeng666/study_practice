#include "combatant.h"
#include "collision_mgr.h"


Combatant::Combatant()
{
    hit_box = CollisionMgr::instance()->creatCollisionBox("hit_box");
    hurt_box = CollisionMgr::instance()->creatCollisionBox("hurt_box");
}

Combatant::~Combatant()
{
    //std::cout << "Destroying ~Combatant at: " << this << std::endl;
    CollisionMgr::instance()->destroyCollisionBox(hit_box.lock());
    CollisionMgr::instance()->destroyCollisionBox(hurt_box.lock());
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

TreeNode_SP Combatant::get_hit_box()
{
    return hit_box.lock();
}

TreeNode_SP Combatant::get_hurt_box()
{
    return hurt_box.lock();
}