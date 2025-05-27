#pragma once
#include "Player.h"
#include "SunBullet.h"
#include "SunBulletEx.h"


extern Atlas atlas_sunflower_idle_left;
extern Atlas atlas_sunflower_idle_right;
extern Atlas atlas_sunflower_run_left;
extern Atlas atlas_sunflower_run_right;
extern Atlas atlas_sunflower_attack_ex_left;
extern Atlas atlas_sunflower_attack_ex_right;
extern Atlas atlas_sun_text;
extern Atlas atlas_sunflower_die_left;					// 龙日葵朝向左的死亡动画图集
extern Atlas atlas_sunflower_die_right;				// 龙日葵朝向右的死亡动画图集

extern Player* player_1;
extern Player* player_2;

class SunflowerPlayer :
    public Player
{
public:
    SunflowerPlayer(bool right = true) :Player(right)
    {
        ani_idle_left.set_atlas(&atlas_sunflower_idle_left);
        ani_idle_right.set_atlas(&atlas_sunflower_idle_right);
        ani_run_left.set_atlas(&atlas_sunflower_run_left);
        ani_run_right.set_atlas(&atlas_sunflower_run_right);
        ani_attack_ex_left.set_atlas(&atlas_sunflower_attack_ex_left);
        ani_attack_ex_right.set_atlas(&atlas_sunflower_attack_ex_right);
        ani_sun_text.set_atlas(&atlas_sun_text);
        ani_die_left.set_atlas(&atlas_sunflower_die_left);
        ani_die_right.set_atlas(&atlas_sunflower_die_right);

        ani_idle_left.set_interval(75);
        ani_idle_right.set_interval(75);
        ani_run_left.set_interval(75);
        ani_run_right.set_interval(75);
        ani_attack_ex_left.set_interval(100);
        ani_attack_ex_right.set_interval(100);
        ani_sun_text.set_interval(100);
        ani_die_left.set_interval(150);
        ani_die_right.set_interval(150);

        ani_die_left.set_loop(false);
        ani_die_right.set_loop(false);
        ani_attack_ex_left.set_loop(false);
        ani_attack_ex_right.set_loop(false);
        ani_sun_text.set_loop(false);
        
        ani_attack_ex_left.set_callback([&]()
            {
                is_attack_ex = false;
                is_sun_text_visible = false;
            }
        );
        ani_attack_ex_right.set_callback([&]()
            {
                is_attack_ex = false;
                is_sun_text_visible = false;
            }
        );

        size.x = 96;
        size.y = 96;
        attack_cd = 250;
    }
    ~SunflowerPlayer() = default;


    /*普通攻击*/
    void on_attack()
    {
        Bullet* bullet = new SunBullet();

        Vector2 bullet_position;
        const Vector2& bullet_size = bullet->get_size();
        bullet_position.x = position.x + (size.x - bullet_size.x) / 2;
        bullet_position.y = position.y;

        bullet->set_position(bullet_position.x, bullet_position.y);
        bullet->set_velocity(is_face_right ? velocity_sun.x : -velocity_sun.x, velocity_sun.y);

        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

        bullet->set_callback([&]() {mp += 35;});

        bullet_list.push_back(bullet);


    }

    /*特殊攻击*/
    void on_attack_ex()
    {
        is_attack_ex = true;
        is_sun_text_visible = true;

        is_face_right ? ani_attack_ex_right.reset() : ani_attack_ex_left.reset();

        Bullet* bullet = new SunBulletEx();
        Player* enemyer = (id == PlayerID::P1 ? player_2 : player_1);

        bullet->set_position(enemyer->getPosition().x + (enemyer->getSize().x - bullet->get_size().x) / 2, -bullet->get_size().y);
        bullet->set_velocity(0, speed_sun_ex);

        bullet->set_collide_target(id == PlayerID::P1 ? PlayerID::P2 : PlayerID::P1);

        bullet->set_callback([&]() {mp += 50;});

        bullet_list.push_back(bullet);

        mciSendString(_T("play sun_text from 0"), nullptr, 0, nullptr);
    }

    void on_update(int delta)
    {
        Player::on_update(delta);
        if (is_sun_text_visible)
        {
            ani_sun_text.on_updata(delta);
        }

    }

    void on_input(const ExMessage& mag)
    {
        Player::on_input(mag);

    }

    void on_draw(const Camera& camera)
    {
        Player::on_draw(camera);
        if (is_sun_text_visible)
        {
            Vector2 t_pos;
            IMAGE* img = ani_sun_text.get_frame();
            t_pos.x = position.x - (size.x - img->getwidth()) / 2;
            t_pos.y = position.y - img->getheight();
            ani_sun_text.on_draw(camera, t_pos.x, t_pos.y);
        }
    }

private:
    // 大炸弹下落速度
    const float speed_sun_ex = 0.15f;
    // 小炸弹抛设速度
    const Vector2 velocity_sun = { 0.25f,-0.5f };

private:
    Animation ani_sun_text;             //头顶动画
    bool is_sun_text_visible = false;   //是否显示头顶动画
};

