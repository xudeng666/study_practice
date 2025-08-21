#pragma once

#include "scene.h"
#include "game_btn.h"

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
    // �˳���ť
    GameBtn* btn_exit = nullptr;
    // Ѫ��
    // ����
    // �ӵ��б�
    // �ӵ���
    // �����б�
    // ����
};

