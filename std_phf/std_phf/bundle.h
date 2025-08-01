#pragma once

#include "region.h"

#include "res_mgr.h"
#include "cursor_mgr.h"

#include <string>

/*ŒÔ∆∑∂—ª˘¿‡*/
class Bundle :
    public Region
{
public:
    Bundle(const SDL_Rect rect, Meal meal, const std::string& tex_name) : Region(rect), meal(meal), tex_name(tex_name){}
    ~Bundle() = default;

    void on_cursor_up() override;
    void on_cursor_down() override;
    void on_render(SDL_Renderer* renderer) override;

    void set_meal(const Meal& meal)
    {
        this->meal = meal;
    }

    const Meal& get_meal() const
    {
        return meal;
    }

    void set_tex_name(const std::string& tex_name)
    {
        this->tex_name = tex_name;
    }

    const std::string& get_tex_name() const
    {
        return tex_name;
    }

protected:
    Meal meal;
    std::string tex_name;
};

/*ø…¿÷∂—*/
class ColaBundle :
    public Bundle
{
public:
    ColaBundle(int x, int y) :
        Bundle({ x, y, 120, 124 }, Meal::Cola, std::string("cola_bundle")) {
    }
    ~ColaBundle() = default;
};

/*¿◊±Ã∂—*/
class SpriteBundle :
    public Bundle
{
public:
    SpriteBundle(int x, int y) :
        Bundle({ x, y, 120, 124 }, Meal::Sprite, std::string("sprite_bundle")) {
    }
    ~SpriteBundle() = default;
};

/*≤Õ∫–∂—*/
class TbBundle :
    public Bundle
{
public:
    TbBundle(int x, int y) :
        Bundle({ x, y, 112, 96 }, Meal::TakeoutBox, std::string("tb_bundle")) {
    }
    ~TbBundle() = default;
};

/*»‚ÕË∂—*/
class MbBoxBundle :
    public Bundle
{
public:
    MbBoxBundle(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::MeatBall_Box, std::string("mb_box_bundle")) {
    }
    ~MbBoxBundle() = default;
};

/*ª∆ÏÀº¶∂—*/
class BcBoxBundle :
    public Bundle
{
public:
    BcBoxBundle(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::BraisedChicken_Box, std::string("bc_box_bundle")) {
    }
    ~BcBoxBundle() = default;
};

/*∫Ï…’»‚∂—*/
class RcpBoxBundle :
    public Bundle
{
public:
    RcpBoxBundle(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::RedCookedPork_Box, std::string("rcp_box_bundle")) {
    }
    ~RcpBoxBundle() = default;
};

