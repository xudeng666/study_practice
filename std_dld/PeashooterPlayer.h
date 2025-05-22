#pragma once
#include "Player.h"
#include "PeaBullet.h"

extern Atlas atlas_peashooter_idle_left;
extern Atlas atlas_peashooter_idle_right;
extern Atlas atlas_peashooter_run_left;
extern Atlas atlas_peashooter_run_right;
extern Atlas atlas_peashooter_attack_ex_left;			// 豌豆射手朝向左的特殊攻击动画图集
extern Atlas atlas_peashooter_attack_ex_right;			// 豌豆射手朝向右的特殊攻击动画图集
extern Camera main_camera;

class PeashooterPlayer :
    public Player
{
public:
    PeashooterPlayer()
    {
        ani_idle_left.set_atlas(&atlas_peashooter_idle_left);
        ani_idle_right.set_atlas(&atlas_peashooter_idle_right);
        ani_run_left.set_atlas(&atlas_peashooter_run_left);
        ani_run_right.set_atlas(&atlas_peashooter_run_right);
        ani_attack_ex_left.set_atlas(&atlas_peashooter_attack_ex_left);
        ani_attack_ex_right.set_atlas(&atlas_peashooter_attack_ex_right);

        ani_idle_left.set_interval(75);
        ani_idle_right.set_interval(75);
        ani_run_left.set_interval(75);
        ani_run_right.set_interval(75);
        ani_attack_ex_left.set_interval(75);
        ani_attack_ex_right.set_interval(75);

        size.x = 96;
        size.y = 96;

        timer_attack_ex.set_wait_time(attack_ex_time);
        timer_attack_ex.set_one_shot(true);
        timer_attack_ex.set_callback([&]() {is_attack_ex = false;});

        timer_spawn_attack_ex.set_wait_time(100);
        timer_spawn_attack_ex.set_callback([&]() {spawn_bullet(speed_bullet_ex);});

        attack_cd = 100;
    }
    ~PeashooterPlayer() = default;


    /*普通攻击*/
    void on_attack()
    {
        if (is_attack_ex || !can_attack)
            return;
        spawn_bullet(speed_bullet);

        TCHAR path_file[256];
        _stprintf_s(path_file, _T("play pea_shoot_%d from 0"), getIntRand(1, 2));// 随机破碎声音
        mciSendString(path_file, nullptr, 0, nullptr);
    }

    /*特殊攻击*/
    void on_attack_ex()
    {
        is_attack_ex = true;
        timer_attack_ex.restart();

        is_face_right ? ani_attack_ex_right.reset() : ani_attack_ex_left.reset();
        //spawn_bullet(speed_bullet_ex);

        mciSendString(_T("play pea_shoot_ex from 0"), nullptr, 0, nullptr);
    }

    void on_update(int delta)
    {
        Player::on_update(delta);

        if (is_attack_ex)
        {
            main_camera.shake(5, 100);
            timer_attack_ex.on_update(delta);
            timer_spawn_attack_ex.on_update(delta);
        }
    }

    void on_input(const ExMessage& mag)
    {
        Player::on_input(mag);
    }

    void on_draw(const Camera& camera)
    {
        Player::on_draw(camera);
    }




private:
    /*
    * 发射子弹
    *@speed 子弹的飞行速度
    */
    void spawn_bullet(float speed)
    {
        Bullet* bullet = new PeaBullet();

        Vector2 bullet_position, bullet_velocity;
        const Vector2& bullet_size = bullet->get_size();
        bullet_position.x = is_face_right
            ? position.x + size.x - bullet_size.x / 2
            : position.x - bullet_size.x / 2;
        bullet_position.y = position.y;
        bullet_velocity.x = is_face_right ? speed : -speed;
        bullet_velocity.y = 0;

        bullet->set_position(bullet_position.x, bullet_position.y);
        bullet->set_velocity(bullet_velocity.x, bullet_velocity.y);

        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

        bullet->set_callback([&]() {mp += 25;});

        bullet_list.push_back(bullet);
    }
private:
    // 普通子弹速度
    const float speed_bullet = 0.75f;
    // 特殊子弹速度
    const float speed_bullet_ex = 1.5f;
    /*特攻持续时长*/
    const float attack_ex_time = 2500;

    /*特攻状态定时器*/
    Timer timer_attack_ex;
    /*特攻状态攻击定时器*/
    Timer timer_spawn_attack_ex;
};

