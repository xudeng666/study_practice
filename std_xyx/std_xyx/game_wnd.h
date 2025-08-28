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

	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	/// <param name="texture">������Դָ��</param>
	/// <param name="rect_src">����rect</param>
	/// <param name="rect_dst">��������Frect</param>
	/// <param name="angle">�Ƕ�</param>
	/// <param name="center">��ת���ĵ�</param>
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src,const SDL_FRect* rect_dst, double angle, const SDL_FPoint* center)const;

	/// <summary>
	/// ��Ⱦ����
	/// </summary>
	/// <param name="texture">������Դָ��</param>
	/// <param name="rect_src">����rect</param>
	/// <param name="rect_dst">��������rect</param>
	void render_texture(SDL_Texture* texture, const SDL_Rect* rect_src, const SDL_Rect* rect_dst) const;

	/// <summary>
	/// ���ƾ��α߿�
	/// </summary>
	/// <param name="rect">��Χ</param>
	void render_line_rect(SDL_Rect* rect);

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

