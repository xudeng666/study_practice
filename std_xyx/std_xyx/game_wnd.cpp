#include "game_wnd.h"

GameWnd* GameWnd::game_wnd = nullptr;

GameWnd* GameWnd::instance()
{
    if (!game_wnd)
    {
        game_wnd = new GameWnd();
    }
    return game_wnd;
}

int GameWnd::get_width() const
{
    return  width;
}

int GameWnd::get_height() const
{
    return  height;
}

Vector2 GameWnd::get_center() const
{
    return  Vector2(width / 2, height / 2);
}

Vector2 GameWnd::get_size() const
{
    return  Vector2(width, height);
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

void GameWnd::render_texture(SDL_Texture* texture, const SDL_Rect* rect_src,
	const SDL_FRect* rect_dst, double angle, const SDL_FPoint* center)const
{
	SDL_FRect dst = *rect_dst;
	dst.x -= camera->get_position().x;
	dst.y -= camera->get_position().y;

	SDL_RenderCopyExF(renderer, texture, rect_src, &dst, angle, center, SDL_RendererFlip::SDL_FLIP_NONE);
}

void GameWnd::render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_Rect* rect_dst) const
{
	SDL_Rect dst = *rect_dst;
	dst.x -= (int)camera->get_position().x;
	dst.y -= (int)camera->get_position().y;

	SDL_RenderCopy(renderer, texture, rect_src, &dst);
}

void GameWnd::render_line_rect(SDL_Rect* rect)
{
	SDL_RenderDrawRect(renderer, rect);
}

GameWnd::GameWnd()
{
    window = SDL_CreateWindow(u8"–°”Œœ∑", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    camera = new Camera();
}

GameWnd::~GameWnd()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    delete camera;
    camera = nullptr;
    delete game_wnd;
    game_wnd = nullptr;
}