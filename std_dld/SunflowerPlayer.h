#pragma once
#include "Player.h"
#include "SunBullet.h"


extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;

class SunflowerPlayer :
    public Player
{
public:
    SunflowerPlayer()
    {
        ani_idle_left.set_atlas(&atlas_sunflower_idle_left);
        ani_idle_right.set_atlas(&atlas_sunflower_idle_right);
        ani_run_left.set_atlas(&atlas_sunflower_run_left);
        ani_run_right.set_atlas(&atlas_sunflower_run_right);

        ani_idle_left.set_interval(75);
        ani_idle_right.set_interval(75);
        ani_run_left.set_interval(75);
        ani_run_right.set_interval(75);

        size.x = 96;
        size.y = 96;
    }
    ~SunflowerPlayer() = default;


private:
    /*
    * 发射子弹
    *@speed 子弹的飞行速度
    */
    void spawn_bullet(const Vector2& velocity)
    {
        Bullet* bullet = new SunBullet();

        Vector2 bullet_position, bullet_velocity;
        const Vector2& bullet_size = bullet->get_size();
        bullet_position.x = is_face_right
            ? position.x + size.x - bullet_size.x / 2
            : position.x - bullet_size.x / 2;
        bullet_position.y = position.y;
        bullet_velocity.x = is_face_right ? velocity.x : -velocity.x;
        bullet_velocity.y = velocity.y;

        bullet->set_position(bullet_position.x, bullet_position.y);
        bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

        bullet->set_callback([&]() {mp += 25;});
    }
};

