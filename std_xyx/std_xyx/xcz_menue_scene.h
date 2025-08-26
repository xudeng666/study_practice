#pragma once
#include "scene.h"
#include "game_btn.h"

class XczMenueScene :
    public Scene
{
public:
    XczMenueScene();
    ~XczMenueScene();

    void on_enter() override;
    void on_exit() override;

private:
    GameImg* bg = nullptr;
    GameBtn* btn_start = nullptr;
    GameBtn* btn_end = nullptr;
};

