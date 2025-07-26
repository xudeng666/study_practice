#pragma once
#include "vector2.h"
#include "camera.h"

#include <SDL.h>

extern SDL_Texture* tex_bullet;

/*�ӵ���*/
class Bullet
{
public:
    Bullet(double val)
    {
        angle = val;
        double radians = getRadiansByAngle(angle);
        velocity.x = (float)std::cos(radians) * speed;
        velocity.y = (float)std::sin(radians) * speed;
    }

    ~Bullet() = default;

    /*����λ��*/
    void set_position(const Vector2& pos)
    {
        position = pos;
    }

    /*��ȡλ��*/
    const Vector2& get_position() const
    {
        return position;
    }

    /*��ȡ����λ��*/
    Vector2 get_center_position()
    {
        return { position.x + size.x / 2,position.y + size.y / 2 };
    }

    /*���óߴ�*/
    void set_size(const Vector2& pos)
    {
        size = pos;
    }

    /*��ȡ�ߴ�*/
    const Vector2& get_size() const
    {
        return size;
    }

    /*�����ٶ�*/
    void set_velocity(const Vector2& pos)
    {
        velocity = pos;
    }

    /*��ȡ�ٶ�*/
    const Vector2& get_velocity() const
    {
        return velocity;
    }

    /*�����Ƿ���Ч*/
    void on_hit()
    {
        valid = false;
    }
    /*�Ƿ���Ƴ�*/
    bool can_remove()const
    {
        return !valid;
    }

    void on_update(float delta)
    {
        position += velocity * delta;
        if (check_out_screen())
        {
            valid = false;
        }
    }

    void on_render(const Camera& camera)const
    {
        const SDL_FRect dst = { position.x - size.x / 2,position.y - size.y / 2,size.x,size.y };
        camera.render_texture(tex_bullet, nullptr, &dst, angle, nullptr);
    }
protected:
    Vector2 size = { 8.0,4.0 };         // �ӵ��ߴ�
    Vector2 position;                   // �ӵ�λ��
    Vector2 velocity;                   // �ӵ��ٶ�
    double angle = 0;                   // �ӵ���ת�Ƕ�
    bool valid = true;                  // �ӵ��Ƿ���Ч
    float speed = 1000.0f;               // �ٶȲ���

protected:
    /*����ӵ��ɳ���Ļ*/
    bool check_out_screen()
    {
        return (position.x + size.x < -10
            || position.x > _W_ + 10
            || position.y + size.y < -10
            || position.y > _H_ + 10);
    }

};

