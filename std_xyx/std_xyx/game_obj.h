#pragma once

#include <SDL.h>

#include "game_type.h"
#include "camera.h"

/*��Ϸ�������*/
class GameObj
{
public:
    GameObj() = default;
    GameObj(const Vector2 pos) : position(pos) {}
    ~GameObj() = default;

    virtual void on_update(float delta) {}
    virtual void on_render() {}
    virtual void on_cursor_down() {}
    virtual void on_cursor_up() {}
    virtual void on_cursor_hover(bool is_hover) {}
    /*�������*/
    void on_input(const SDL_Event& event);
    /*��������*/
    void set_position(const Vector2& pos);
    /*��ȡ����*/
    const Vector2& get_position() const;
    /*���óߴ�*/
    void set_size(const SDL_Point& size);
    /*��ȡ�ߴ�*/
    const SDL_Point& get_size() const;
    /*����ê��*/
    void set_anchor_mode(const AnchorMode mode);
    /*��ȡê��*/
    const AnchorMode get_anchor_mode() const;
    /*��������*/
    void set_center(const SDL_FPoint& pos);
    /*���ýǶ�*/
    void set_rotation(double val);
    /*���õ������״̬*/
    void set_enabled(bool enable);
    /*��ȡ�������״̬*/
    bool get_enabled();
    /*���õ������*/
    void set_rect(SDL_Rect* rect);

protected:
    // ��ת�Ƕ�
    double angle = 0;
    /*������򿪹�״̬*/
    bool click_enabled = false;
	/*����*/
	Vector2 position;
	/*�ߴ�*/
    SDL_Point size = { 0 };
    // ���ĵ�
    SDL_FPoint center = { 0 };
	/*ê��*/
    AnchorMode anchor_mode = AnchorMode::CENTER;
    /*�������*/
    SDL_Rect click_rect = { 0 };
};