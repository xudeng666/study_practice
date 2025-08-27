#include "game_wnd.h"

static GameWnd* game_wnd = nullptr;

GameWnd* GameWnd::instance()
{
    if (!game_wnd)
    {
        game_wnd = new GameWnd();
    }
    return game_wnd;
}

std::pair<int, int> GameWnd::getSize() const
{
    return { width, height };
}

void GameWnd::set_title(const std::string& title)
{
    SDL_SetWindowTitle(window, title.c_str());
}

SDL_Renderer* GameWnd::get_renderer()
{
    return renderer;
}

Camera* GameWnd::get_camera()
{
    return camera;
}

GameWnd::GameWnd()
{
    window = SDL_CreateWindow(u8"–°”Œœ∑", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    camera = new Camera(renderer);
}

GameWnd::~GameWnd()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete camera;
}