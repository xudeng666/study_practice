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
    // �˳���ť
    GameBtn* btn_exit = nullptr;
    // Ѫ��
    GameBar* hp_bar = nullptr;
    // ����
    // �ӵ��б�
    // �����б�
    // �����б�
    // ����
    int score = 0;
    // Ѫ��
    int hp = 10;
};

