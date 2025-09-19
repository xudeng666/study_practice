#include "character.h"
#include "game_wnd.h"


Character::~Character()
{
    ani_pool.clear();
}

void Character::on_init()
{
    auto node = TreeNode::create(std::make_unique<GameAni>("current_ani"));
    current_ani = node;
    self_node.lock()->add_children(std::move(node));
}

void Character::on_enter()
{
    // 初始化
    GameObj::on_enter();
}

void Character::on_exit()
{
    // 反初始化
    GameObj::on_exit();
}

void Character::on_input(const SDL_Event& event)
{
    // 基类留空 只有玩家角色可操控
    GameObj::on_input(event);
}

void Character::on_update(float delta)
{
    GameObj::on_update(delta);
}

void Character::on_render()
{
    GameObj::on_render();
}

void Character::on_hurt()
{
    //std::cout << ID << "     on_hurt" << std::endl;
    Combatant::on_hurt();
}

void Character::on_hit()
{
    //std::cout << ID << "     on_hit" << std::endl;
    Combatant::on_hit();
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
    alive = hp > 0;
    on_hurt();
}

void Character::set_hp(const int val)
{
    hp = val;
}

int Character::get_hp() const
{
    return hp;
}

void Character::set_animation(const Ani_Res& res)
{
    GameAni* ani = dynamic_cast<GameAni*>(current_ani.lock()->get_obj());
    ani->set_res_name(res);
}

void Character::lock_in_screen()
{
    if (!check_out_of_screen) return;

    SDL_FRect p = get_FRect();
    if ((velocity.x + p.x + p.w) < 0 || (velocity.x + p.x) > GameWnd::instance()->get_width())
    {
        velocity.x = 0;
    }

    if ((velocity.y + p.y + p.h) < 0 || (velocity.y + p.y) > GameWnd::instance()->get_height())
    {
        velocity.y = 0;
    }
}

bool Character::get_alive() const
{
    return alive;
}

bool Character::get_valid() const
{
    return valid;
}
