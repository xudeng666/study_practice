#pragma once

#include "camera.h"

class GameWnd
{
public:
    static GameWnd* instance();

    // 获取窗口尺寸
    std::pair<int, int> getSize() const;
    // 修改窗口标题
    void set_title(const std::string& title);
    // 获取渲染器
    SDL_Renderer* get_renderer();
    // 获取相机
    Camera* get_camera();

private:
    GameWnd();
    ~GameWnd();
private:
    static GameWnd* game_wnd;
    // 窗口
    SDL_Window* window = nullptr;
    // 渲染器
    SDL_Renderer* renderer = nullptr;
    // 相机
    Camera* camera = nullptr;

    int width = 1280;
    int height = 720;
};

