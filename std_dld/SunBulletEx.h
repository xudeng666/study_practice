#pragma once

#include "Bullet.h"
#include "Animation.h"

extern Atlas atlas_sun_ex;								// �����չ⶯��ͼ��
extern Atlas atlas_sun_ex_explode;						// �����չⱬը����ͼ��
extern Atlas atlas_sun_text;							// ���ա� �ı�����ͼ�� 

extern Camera main_camera;

/*��̫���ӵ�*/
class SunBulletEx :
    public Bullet
{
public:
    SunBulletEx()
    {
        size.x = size.y = 288;
        damage = 20;

        ani_sun.set_atlas(&atlas_sun_ex);
        ani_sun.set_interval(50);

        ani_exp.set_atlas(&atlas_sun_ex_explode);
        ani_exp.set_interval(50);
        ani_exp.set_loop(false);
        ani_exp.set_callback([&]() {can_remove = true;});

        IMAGE* img_sun = ani_sun.get_frame();
        IMAGE* img_exp = ani_exp.get_frame();
        exp_render_set.x = (img_sun->getwidth() - img_exp->getwidth()) / 2.0f;
        exp_render_set.y = (img_sun->getheight() - img_exp->getheight()) / 2.0f;

    }
    ~SunBulletEx() = default;

    void on_collide()
    {
        Bullet::on_collide();

        main_camera.shake(20, 350);

        mciSendString(_T("play sun_explode_ex from 0"), nullptr, 0, nullptr);
    }
    /*
    * �ӵ���ײ���
    *@pos   ��ײ����λ��
    *@size  ��ײ�����С
    */
    bool check_cllide(const Vector2& pos, const Vector2& size)
    {
        return checkRectToRect<float>(position.x, position.x + this->size.x, position.y, position.y + this->size.y,
            pos.x, pos.x + size.x, pos.y, pos.y + size.y);
    }

    void on_update(int delta)
    {
        if (can_remove)
        {
            return;
        }
        if (valid)
        {
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
    Animation ani_exp;      // ��ը����
    Animation ani_sun;      // Ĭ�϶���
    Vector2 exp_render_set; // ��ը��������Ⱦƫ��

    Animation* currentAni = nullptr;	// ��ǰ����
};





