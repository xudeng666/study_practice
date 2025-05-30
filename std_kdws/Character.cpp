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
// ֻ����ҿ��ƵĽ�ɫ���м�����ƣ����Ի�������
void Character::on_input(const ExMessage& msg) {}

void Character::on_update(float delta)
{
    state_machine.on_update(delta);
    // �����ɫλ��//
    if (hp <= 0)
        velocity.x = 0;//��ɫ������������ٶ�Ϊ0
    if (enable_gravity)
        velocity.y += GRAVITY * delta;

    position += velocity * delta;

    if (position.y >= FLOOR_Y) // �����վ�ڵ���
    {
        position.y = FLOOR_Y;
        velocity.y = 0;
    }
    // �ƶ���������Ļ��
    if (position.x <= 0) position.x = 0;
    if (position.x >= getwidth()) position.x = (float)getwidth();
    // �����ɫλ��//

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
    // ���������ڣ������޵���˸���ɼ�ʱ���������ƣ���Ⱦ��
    if (!current_animation || (is_invulnerable && is_blink_invisible)) return;

    (is_facing_left ? current_animation->left : current_animation->right).on_draw();
}

void Character::on_hurt() {}//һ�������ܻ�������Ч����������

void Character::switch_state(const std::string& id)
{
    state_machine.switch_to(id);
}

void Character::set_animation(const std::string& id)
{
    current_animation = &animation_pool[id];
    //�л�״̬��״̬ʱһ�����л�����������ҲҪ���þ�������Ҷ�������״̬
    current_animation->left.reset();
    current_animation->right.reset();
}