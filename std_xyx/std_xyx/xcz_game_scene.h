#pragma once

#include "scene.h"
#include "game_btn.h"
#include "game_bar.h"

class XczGameScene :
    public Scene
{
public:
    XczGameScene();
    ~XczGameScene();

    void on_enter();
    void on_update(float delta);
    void on_input(const SDL_Event& event);
    void on_render();
    void on_exit();

private:
    GameBtn* bg = nullptr;
    // 退出按钮
    GameBtn* btn_exit = nullptr;
    // 血条
    GameBar* hp_bar = nullptr;
    // 主角
    // 子弹列表
    // 怪物列表
    // 动画列表
    // 分数
    int score = 0;
    // 血量
    int hp = 10;
};

