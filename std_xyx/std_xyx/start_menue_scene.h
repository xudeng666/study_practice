#pragma once

#include "scene.h"
#include "game_btn.h"

class StartMenueScene :
    public Scene
{
public:
    StartMenueScene();
    ~StartMenueScene();

    void on_enter();
    void on_update(float delta);
    void on_input(const SDL_Event & event);
    void on_render();
    void on_exit();

private:
    GameImg* bg = nullptr;
    GameBtn* btn_xcz = nullptr;
    GameBtn* btn_kdws = nullptr;
    GameBtn* btn_dld = nullptr;
    GameBtn* btn_zmdj = nullptr;
    GameBtn* btn_phf = nullptr;
    GameBtn* btn_exit = nullptr;
};

