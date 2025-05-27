#pragma once
#include "Bullet.h"
#include "Animation.h"

extern IMAGE img_pea;									// Õ„∂πÕº∆¨
extern Atlas atlas_pea_break;							// Õ„∂π∆∆ÀÈ∂Øª≠ÕººØ

/*Õ„∂π◊”µØ*/
class PeaBullet :
    public Bullet
{
public:
    PeaBullet()
    {
        size.x = size.y = 64;
        damage = 10;
        ani_break.set_atlas(&atlas_pea_break);
        ani_break.set_interval(100);
        ani_break.set_loop(false);
        ani_break.set_callback([&]() {can_remove = true;});

    }
    ~PeaBullet() = default;

    void on_collide()
    {
        Bullet::on_collide();

        TCHAR path_file[256];
        _stprintf_s(path_file, _T("play pea_break_%d from 0"), getIntRand(1, 3));// ÀÊª˙∆∆ÀÈ…˘“Ù
        mciSendString(path_file, nullptr, 0, nullptr);

        
    }

    void on_update(int delta)
    {
        if (can_remove)
        {
            return;
        }
        position += velocity * (float)delta;
        if (!valid)
        {
            ani_break.on_updata(delta);
        }

        if (check_out_screen())
        {
            can_remove = true;
        }
    }

    void on_draw(const Camera& camera)const
    {
        if (can_remove)
        {
            return;
        }
        if (valid)
        {
            putimage_alpha(camera, (int)position.x, (int)position.y, &img_pea);
        }
        else
        {
            ani_break.on_draw(camera, position.x, position.y);
        }
        Bullet::on_draw(camera);
    }

private:
    Animation ani_break;    // ∆∆ÀÈ∂Øª≠
};

