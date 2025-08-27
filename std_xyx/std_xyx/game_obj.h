#pragma once

#include <forward_list>

//#include <SDL.h>

#include "res_mgr.h"
#include "game_type.h"

/*游戏对象基类*/
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
    /*设置ID*/
    void set_ID(const std::string id);
    /*获取ID*/
    std::string get_ID();
    /*设置坐标*/
    void set_position(const Vector2& pos);
    /*获取坐标*/
    const Vector2& get_position() const;
    /*设置尺寸*/
    virtual void set_size(const SDL_Point& size);
    /*获取尺寸*/
    const SDL_Point& get_size() const;
    /*设置显示状态*/
    void set_display(bool display);
    /*获取显示状态*/
    const bool get_display() const;
    /*设置锚点*/
    void set_anchor_mode(const AnchorMode mode);
    /*获取锚点*/
    const AnchorMode get_anchor_mode() const;
    /*设置父节点锚点*/
    void set_parent_anchor_mode(const AnchorMode mode);
    /*获取父节点锚点*/
    const AnchorMode get_parent_anchor_mode() const;
    /*设置旋转中心*/
    void set_center(const SDL_FPoint& pos);
    /*设置角度*/
    void set_rotation(double val);
    /*设置点击区域状态*/
    void set_click_enabled(bool enable);
    /*获取点击区域状态*/
    bool get_click_enabled();
    /*获取对象区域*/
    SDL_FRect get_FRect();
    /*获取对象区域*/
    SDL_Rect get_Rect();
    /*获取对象锚点坐标*/
    Vector2 get_anchor_position(const AnchorMode mode);

protected:
    std::string ID;
    // 旋转角度
    double angle = 0.0;
    /*点击区域开关状态*/
    bool click_enabled = true;
    // 是否显示
    bool is_display = true;
	/*相对父节点坐标*/
    Vector2 position = { 0.0f, 0.0f };
    // 点击区域 暂时不单独列出
    // SDL_FRect click_rect;
	/*尺寸*/
    SDL_Point size = { 0, 0 };
    // 中心点
    SDL_FPoint center = { 0.0f, 0.0f };
	/*自身锚点*/
    AnchorMode anchor_mode = AnchorMode::TOPLEFT;
    /*父锚点*/
    AnchorMode parent_anchor_mode = AnchorMode::TOPLEFT;

protected:
    // 父节点
    GameObj* parent = nullptr;
    // 子节点
    std::list<GameObj*> children;

public:
    /*设置父节点*/
    void set_parent(GameObj* p);
    /*获取父节点*/
    GameObj* get_parent();
    /*获取子节点数组*/
    std::list<GameObj*> get_children();
    /*添加子节点*/
    void add_children(GameObj* obj);
    
};