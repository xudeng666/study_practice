#pragma once

#include "camera.h"

class GameWnd
{
public:
    static GameWnd* instance();

    // ��ȡ���ڳߴ�
    std::pair<int, int> getSize() const;
    // �޸Ĵ��ڱ���
    void set_title(const std::string& title);
    // ��ȡ��Ⱦ��
    SDL_Renderer* get_renderer();
    // ��ȡ���
    Camera* get_camera();

private:
    GameWnd();
    ~GameWnd();
private:
    static GameWnd* game_wnd;
    // ����
    SDL_Window* window = nullptr;
    // ��Ⱦ��
    SDL_Renderer* renderer = nullptr;
    // ���
    Camera* camera = nullptr;

    int width = 1280;
    int height = 720;
};

