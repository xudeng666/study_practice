#pragma once

#include "camera.h"

class GameWnd
{
public:
    static GameWnd* instance();

    // 获取窗口宽
    int get_width() const;
    // 获取窗口高
    int get_height() const;
    // 获取屏幕中心点坐标
    Vector2 get_center() const;
    // 修改窗口标题
    void set_title(const std::string& title);
    // 获取渲染器
    SDL_Renderer* get_renderer();
    // 获取相机
    Camera* get_camera();

	/// <summary>
	/// 渲染纹理
	/// </summary>
	/// <param name="texture">纹理资源指针</param>
	/// <param name="rect_src">纹理rect</param>
	/// <param name="rect_dst">绘制区域Frect</param>
	/// <param name="angle">角度</param>
	/// <param name="center">旋转中心点</param>
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src,const SDL_FRect* rect_dst, double angle, const SDL_FPoint* center)const;

	/// <summary>
	/// 渲染纹理
	/// </summary>
	/// <param name="texture">纹理资源指针</param>
	/// <param name="rect_src">纹理rect</param>
	/// <param name="rect_dst">绘制区域rect</param>
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_Rect* rect_dst) const;

	/// <summary>
	/// 绘制矩形边框
	/// </summary>
	/// <param name="rect">范围</param>
	void render_line_rect(SDL_Rect* rect);

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

    int width = _WIN_W_;
    int height = _WIN_H_;
};

