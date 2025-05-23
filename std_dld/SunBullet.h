#pragma once

#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun;								// �չ⶯��ͼ��
extern Atlas atlas_sun_explode;						// �չⱬը����ͼ��

extern Camera main_camera;

/*̫���ӵ�*/
class SunBullet :
    public Bullet
{
public:
    SunBullet()
    {
        size.x = size.y = 96;
        damage = 20;

        ani_sun.set_atlas(&atlas_sun);
        ani_sun.set_interval(50);

        ani_exp.set_atlas(&atlas_sun_explode);
        ani_exp.set_interval(50);
        ani_exp.set_loop(false);
        ani_exp.set_callback([&]() {can_remove = true;});

        IMAGE* img_sun = ani_sun.get_frame();
        IMAGE* img_exp = ani_exp.get_frame();
        exp_render_set.x = (img_sun->getwidth() - img_exp->getwidth()) / 2.0f;
        exp_render_set.y = (img_sun->getheight() - img_exp->getheight()) / 2.0f;

    }
    ~SunBullet() = default;

    void on_collide()
    {
        Bullet::on_collide();

        main_camera.shake(5, 250);

        mciSendString(_T("play sun_explode from 0"), nullptr, 0, nullptr);


    }

    void on_update(int delta)
    {
        if (can_remove)
        {
            return;
        }
        if (valid)
        {
            velocity.y += gravity * delta;
            position += velocity * (float)delta;
            currentAni = &ani_sun;
        }
        else
        {
            currentAni = &ani_exp;
        }
        currentAni->on_updata(delta);

        if (check_out_screen())
        {
            can_remove = true;
        }
    }

    void on_draw(const Camera& camera)const
    {
        Bullet::on_draw(camera);
        if (can_remove)
        {
            return;
        }
        Vector2 pos = position;
        if (!valid)
        {
            pos += exp_render_set;
        }
        currentAni->on_draw(camera, (int)pos.x, (int)pos.y);
    }

private:
    const float gravity = 1e-3f;    // ����

private:
    Animation ani_exp;      // ��ը����
    Animation ani_sun;      // Ĭ�϶���
    Vector2 exp_render_set; // ��ը��������Ⱦƫ��

    Animation* currentAni = nullptr;	// ��ǰ����
};



