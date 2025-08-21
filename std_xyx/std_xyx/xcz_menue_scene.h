#pragma once
#include "scene.h"
#include "game_btn.h"

class XczMenueScene :
    public Scene
{
public:
    XczMenueScene();
    ~XczMenueScene();

    void on_enter()override;
    void on_update(float delta)override;
    void on_input(const SDL_Event& event)override;
    void on_render()override;
    void on_exit()override;

private:
    GameImg* bg = nullptr;
    GameBtn* btn_start = nullptr;
    GameBtn* btn_end = nullptr;
};

