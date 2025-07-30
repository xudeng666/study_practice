#pragma once

#include "region.h"

#include "res_mgr.h"
#include "cursor_mgr.h"

/*��Ʒ�ѻ���*/
class Bundle :
    public Region
{
public:
    Bundle(SDL_Rect rect, Meal meal, const std::string& tex_name) : Region(rect), meal(meal), tex_name(tex_name) {}
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

/*���ֶ�*/
class ColaBundle :
    public Bundle
{
public:
    ColaBundle(int x, int y) :
        Bundle({ x, y, 120, 124 }, Meal::Cola, "cola_bundle") {
    }
    ~ColaBundle() = default;
};

/*�ױ̶�*/
class SpriteBundle :
    public Bundle
{
public:
    SpriteBundle(int x, int y) :
        Bundle({ x, y, 120, 124 }, Meal::Sprite, "sprite_bundle") {
    }
    ~SpriteBundle() = default;
};

/*�ͺж�*/
class TbBundle :
    public Bundle
{
public:
    TbBundle(int x, int y) :
        Bundle({ x, y, 112, 96 }, Meal::TakeoutBox, "tb_bundle") {
    }
    ~TbBundle() = default;
};

/*�����*/
class MbBoxBundl :
    public Bundle
{
public:
    MbBoxBundl(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::MeatBall_Box, "mb_box_bundle") {
    }
    ~MbBoxBundl() = default;
};

/*���˼���*/
class BcBoxBundl :
    public Bundle
{
public:
    BcBoxBundl(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::BraisedChicken_Box, "bc_box_bundle") {
    }
    ~BcBoxBundl() = default;
};

/*�������*/
class RcpBoxBundl :
    public Bundle
{
public:
    RcpBoxBundl(int x, int y) :
        Bundle({ x, y, 160, 88 }, Meal::RedCookedPork_Box, "rcp_box_bundle") {
    }
    ~RcpBoxBundl() = default;
};

