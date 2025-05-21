#pragma once
#include "Player.h"


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
    }
    ~SunflowerPlayer() = default;

   /* virtual void on_update(int delta)
    {

    }

    virtual void on_draw(const Camera& camera)
    {

    }

    virtual void on_input(const ExMessage& msg)
    {

    }*/

private:
};

