#pragma once
#include "util.h"

extern bool is_debug;

/*∆ΩÃ®¿‡*/
class Platform
{
public:
    struct CollisionShape
    {
        float y;
        float left, right;
    };

public:
    CollisionShape shape;
    IMAGE* img = nullptr;
    POINT render_pos = { 0 };

public:
    Platform() = default;
    ~Platform() = default;

    void on_draw(const Camera& camera) const
    {
        putimage_alpha(camera, render_pos.x, render_pos.y, img);
        if (is_debug)
        {
            setlinecolor(RGB(255, 0, 0));
            line(camera, shape.left, shape.y, shape.right, shape.y);
        }
    }
};

