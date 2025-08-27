#pragma once

#include <forward_list>

//#include <SDL.h>

#include "res_mgr.h"
#include "game_type.h"

/*��Ϸ�������*/
class GameObj
{
public:
    GameObj() = default;
    GameObj(const Vector2 pos) : position(pos) {}
    ~GameObj() = default;

    virtual void on_enter();
    virtual void on_exit();
    virtual void on_input(const SDL_Event& event);
    virtual void on_update(float delta);
    virtual void on_render();
    virtual void on_cursor_down() {}
    virtual void on_cursor_up() {}
    virtual void on_cursor_hover(bool is_hover) {}
    /*����ID*/
    void set_ID(const std::string id);
    /*��ȡID*/
    std::string get_ID();
    /*��������*/
    void set_position(const Vector2& pos);
    /*��ȡ����*/
    const Vector2& get_position() const;
    /*���óߴ�*/
    virtual void set_size(const SDL_Point& size);
    /*��ȡ�ߴ�*/
    const SDL_Point& get_size() const;
    /*������ʾ״̬*/
    void set_display(bool display);
    /*��ȡ��ʾ״̬*/
    const bool get_display() const;
    /*����ê��*/
    void set_anchor_mode(const AnchorMode mode);
    /*��ȡê��*/
    const AnchorMode get_anchor_mode() const;
    /*���ø��ڵ�ê��*/
    void set_parent_anchor_mode(const AnchorMode mode);
    /*��ȡ���ڵ�ê��*/
    const AnchorMode get_parent_anchor_mode() const;
    /*������ת����*/
    void set_center(const SDL_FPoint& pos);
    /*���ýǶ�*/
    void set_rotation(double val);
    /*���õ������״̬*/
    void set_click_enabled(bool enable);
    /*��ȡ�������״̬*/
    bool get_click_enabled();
    /*��ȡ��������*/
    SDL_FRect get_FRect();
    /*��ȡ��������*/
    SDL_Rect get_Rect();
    /*��ȡ����ê������*/
    Vector2 get_anchor_position(const AnchorMode mode);

protected:
    std::string ID;
    // ��ת�Ƕ�
    double angle = 0.0;
    /*������򿪹�״̬*/
    bool click_enabled = true;
    // �Ƿ���ʾ
    bool is_display = true;
	/*��Ը��ڵ�����*/
    Vector2 position = { 0.0f, 0.0f };
    // ������� ��ʱ�������г�
    // SDL_FRect click_rect;
	/*�ߴ�*/
    SDL_Point size = { 0, 0 };
    // ���ĵ�
    SDL_FPoint center = { 0.0f, 0.0f };
	/*����ê��*/
    AnchorMode anchor_mode = AnchorMode::TOPLEFT;
    /*��ê��*/
    AnchorMode parent_anchor_mode = AnchorMode::TOPLEFT;

protected:
    // ���ڵ�
    GameObj* parent = nullptr;
    // �ӽڵ�
    std::list<GameObj*> children;

public:
    /*���ø��ڵ�*/
    void set_parent(GameObj* p);
    /*��ȡ���ڵ�*/
    GameObj* get_parent();
    /*��ȡ�ӽڵ�����*/
    std::list<GameObj*> get_children();
    /*����ӽڵ�*/
    void add_children(GameObj* obj);
    
};