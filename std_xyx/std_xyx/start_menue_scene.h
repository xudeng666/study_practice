#pragma once

#include "scene.h"
#include "game_btn.h"

class StartMenueScene :
    public Scene
{
public:
    StartMenueScene();
    ~StartMenueScene();

    void on_enter() override;
    void on_exit() override;

private:
    GameImg* bg = nullptr;
    GameBtn* btn_xcz = nullptr;
    GameBtn* btn_kdws = nullptr;
    GameBtn* btn_dld = nullptr;
    GameBtn* btn_zmdj = nullptr;
    GameBtn* btn_phf = nullptr;
    GameBtn* btn_exit = nullptr;
};

