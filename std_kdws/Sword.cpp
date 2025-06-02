#include "Sword.h"
#include "ResourceManager.h"
#include "CollisionManager.h"

Sword::Sword(const Vector2& position, bool move_left)
{
    animation.set_interval(0.1f);
    animation.set_loop(true);
    animation.set_anchor_mode(Animation::AnchorMode::CENTER);
    animation.add_frame(ResourceManager::instance()->find_atlas(
        move_left ? "sword_left" : "sword_right"));

    collision_box = CollisionManager::instance()->creatCollisionBox();
    collision_box->set_layer_src(CollisionLayer::None);
    collision_box->set_layer_dst(CollisionLayer::Player);
    collision_box->set_size({ 195, 10 });

    this->position = position;
    this->velocity = { move_left ? -SPEED_MOVE : SPEED_MOVE, 0 };
}

Sword::~Sword()
{
    CollisionManager::instance()->destroyCollisionBox(collision_box);
}

void Sword::on_update(float delta)
{
    position += velocity * delta;
    animation.set_position(position);
    collision_box->set_position(position);

    animation.on_update(delta);

    if (position.x <= -200 || position.x >= getwidth() + 200)// ·É³öÆÁÄ»ÍâÊ§Ğ§
        is_valid = false;
}

void Sword::on_draw()
{
    animation.on_draw();
}