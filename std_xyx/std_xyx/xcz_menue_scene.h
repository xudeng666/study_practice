#pragma once
#include "scene.h"
#include "game_btn.h"

class XczMenueScene :
    public Scene
{
public:
    XczMenueScene();
    ~XczMenueScene();

    void on_enter();
    void on_update(float delta);
    void on_input(const SDL_Event& event);
    void on_render();
    void on_exit();

private:
    GameImg* bg = nullptr;
    GameBtn* btn_start = nullptr;
    GameBtn* btn_end = nullptr;
};

