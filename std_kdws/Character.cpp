#include "Character.h"
#include "CollisionManager.h"

Character::Character()
{
    hit_box = CollisionManager::instance()->creatCollisionBox();
    hurt_box = CollisionManager::instance()->creatCollisionBox();

    timer_invulnerable_status.set_wait_time(1.0f);
    timer_invulnerable_status.set_one_shot(true);
    timer_invulnerable_status.set_call_back([&]()
        {
            is_invulnerable = false;
        });

    timer_invulnerable_blink.set_wait_time(0.075f);
    timer_invulnerable_blink.set_one_shot(false);
    timer_invulnerable_blink.set_call_back([&]()
        {
            is_blink_invisible = !is_blink_invisible;
        });
}

Character::~Character()
{
    CollisionManager::instance()->destroyCollisionBox(hit_box);
    CollisionManager::instance()->destroyCollisionBox(hurt_box);
}

void Character::decrease_hp()
{
    if (is_invulnerable) return;

    hp -= 1;
    if (hp > 0)
        make_invulnerable();
    on_hurt();
}
// 只有玩家控制的角色才有键鼠控制，所以基类留空
void Character::on_input(const ExMessage& msg) {}

void Character::on_update(float delta)
{
    state_machine.on_update(delta);
    // 计算角色位置//
    if (hp <= 0)
        velocity.x = 0;//角色死亡，则横向速度为0
    if (enable_gravity)
        velocity.y += GRAVITY * delta;

    position += velocity * delta;

    if (position.y >= FLOOR_Y) // 落地则站在地面
    {
        position.y = FLOOR_Y;
        velocity.y = 0;
    }
    // 移动限制在屏幕内
    if (position.x <= 0) position.x = 0;
    if (position.x >= getwidth()) position.x = (float)getwidth();
    // 计算角色位置//

    hurt_box->set_position(get_logic_center());

    timer_invulnerable_status.on_update(delta);

    if (is_invulnerable)
        timer_invulnerable_blink.on_update(delta);

    if (!current_animation) return;

    Animation& animation = (is_facing_left
        ? current_animation->left : current_animation->right);
    animation.on_update(delta);
    animation.set_position(position);
}

void Character::on_draw()
{
    // 动画不存在，或者无敌闪烁不可见时，跳过绘制（渲染）
    if (!current_animation || (is_invulnerable && is_blink_invisible)) return;

    (is_facing_left ? current_animation->left : current_animation->right).on_draw();
}

void Character::on_hurt() {}//一般用于受击播放音效，基类留空

void Character::switch_state(const std::string& id)
{
    state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id)
{
    current_animation = &animation_pool[id];
    //切换状态机状态时一般会会切换动画，所以也要重置具体的左右动画对象状态
    current_animation->left.reset();
    current_animation->right.reset();
}