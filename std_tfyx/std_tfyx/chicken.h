#pragma once

#include "animation.h"

#include <SDL_mixer.h>

extern Atlas atlas_explosion;

extern Mix_Chunk* sound_explosion;


class Chicken
{
public:
	Chicken()
	{
        ani_run.set_loop(true);
        ani_run.set_interval(0.1f);

        ani_explosion.set_loop(false);
        ani_run.set_interval(0.08f);
        ani_explosion.add_frame(&atlas_explosion);
        ani_explosion.set_on_finished([&]()
            {
                valid = false;
            });

        position.x = getIntRand(40, 1240);
        position.y = -50;
	}
    ~Chicken() = default;


    /*设置位置*/
    void set_position(const Vector2& pos)
    {
        position = pos;
    }

    /*获取位置*/
    const Vector2& get_position() const
    {
        return position;
    }

    void on_update(float delta)
    {
        if (valid)
        {
            position.y += speed * delta;
        }

        ani_current = (alive ? &ani_run : &ani_explosion);
        ani_current->set_position(position);
        ani_current->on_update(delta);
    }

    void on_render(const Camera& camera) const
    {
        ani_current->on_render(camera);
    }

    void on_hurt()
    {
        alive = false;
        Mix_PlayChannel(-1, sound_explosion, 0);
    }

    void make_invalid()
    {
        valid = false;
    }

    bool check_alive()
    {
        return alive;
    }

    bool can_remove()
    {
        return !valid;
    }

protected:
    Animation ani_run;
    float speed = 10.0f;

private:
	Animation ani_explosion;
    Animation* ani_current = nullptr;

    bool valid = true;                  // 是否可以删除
    bool alive = true;                  // 是否存活
	Vector2 position;                   // 位置
};