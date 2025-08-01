#include "bundle.h"

void Bundle::on_cursor_up()
{
    if (CursorMgr::instance()->get_picked() == meal)
        CursorMgr::instance()->set_picked(Meal::None);
}

void Bundle::on_cursor_down()
{
    if (CursorMgr::instance()->get_picked() == Meal::None)
        CursorMgr::instance()->set_picked(meal);
}

void Bundle::on_render(SDL_Renderer* renderer)
{
    SDL_Texture* texture = ResMgr::instance()->find_texture(tex_name);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
