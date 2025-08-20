#pragma once
#include "scene.h"
class XczGameScene :
    public Scene
{
public:
    XczGameScene();
    ~XczGameScene();

    void on_enter()override;
    void on_update(float delta)override;
    void on_input(const SDL_Event& event)override;
    void on_render()override;
    void on_exit()override;

private:
    SDL_Texture* bg = nullptr;
    // 主角
    // 子弹列表
    // 怪物列表
    // 分数
};

