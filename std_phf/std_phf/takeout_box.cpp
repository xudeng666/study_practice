#include "takeout_box.h"

#include "res_mgr.h"
#include "cursor_mgr.h"

void TakeoutBox::on_cursor_up()
{
    // 如果当前位置是空的快餐盒
    if (meal == Meal::TakeoutBox)
    {
        switch (CursorMgr::instance()->get_picked())
        {
        case Meal::BraisedChicken_Box:
            meal = Meal::BraisedChicken_Cold;
            CursorMgr::instance()->set_picked(Meal::None);
            break;
        case Meal::MeatBall_Box:
            meal = Meal::MeatBall_Cold;
            CursorMgr::instance()->set_picked(Meal::None);
            break;
        case Meal::RedCookedPork_Box:
            meal = Meal::RedCookedPork_Cold;
            CursorMgr::instance()->set_picked(Meal::None);
            break;
        }
    }
    // 否则如果当前位置没有物品并且光标抓取了可放置的物品
    else if (meal == Meal::None && can_place(CursorMgr::instance()->get_picked()))
    {
        meal = CursorMgr::instance()->get_picked();
        CursorMgr::instance()->set_picked(Meal::None);
    }
}

void TakeoutBox::on_cursor_down()
{
    if (CursorMgr::instance()->get_picked() == Meal::None)
    {
        CursorMgr::instance()->set_picked(meal);
        meal = Meal::None;
    }
}

void TakeoutBox::on_render(SDL_Renderer* renderer)
{
    std::string str = "";
    switch (meal)
    {
    case Meal::None:                    break;
    case Meal::BraisedChicken_Hot:      str = "bc_hot";     break;
    case Meal::BraisedChicken_Cold:     str = "bc_cold";    break; 
    case Meal::MeatBall_Hot:            str = "mb_hot";     break; 
    case Meal::MeatBall_Cold:           str = "mb_cold";    break; 
    case Meal::RedCookedPork_Hot:       str = "rcp_hot";    break; 
    case Meal::RedCookedPork_Cold:      str = "rcp_cold";   break; 
    case Meal::TakeoutBox:              str = "tb";         break; 
    }

    if (str != "")
    {
        SDL_Texture* texture = ResMgr::instance()->find_texture(str);
        SDL_Rect rect_texture = { rect.x, rect.y, 0, 0 };
        SDL_QueryTexture(texture, nullptr, nullptr, &rect_texture.w, &rect_texture.h);
        SDL_RenderCopy(renderer, texture, nullptr, &rect_texture);
    }
}

bool TakeoutBox::can_place(Meal target)
{
    return target == Meal::BraisedChicken_Hot || target == Meal::BraisedChicken_Cold
        || target == Meal::MeatBall_Hot || target == Meal::MeatBall_Cold
        || target == Meal::RedCookedPork_Hot || target == Meal::RedCookedPork_Cold
        || target == Meal::TakeoutBox;
}