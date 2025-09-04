#pragma once

#include <forward_list>
#include <functional>

#include <SDL.h>

#include "game_type.h"
#include "vector2.h"

/*游戏对象基类*/
class GameObj
{
public:
    GameObj() {}
    GameObj(const Vector2 pos) : position(pos) {}
    ~GameObj() {}

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
    /*设置锚定对象锚点*/
    void set_anchor_referent_mode(const AnchorMode mode);
    /*获取锚定对象锚点*/
    const AnchorMode get_anchor_referent_mode() const;
    /*设置锚定对象*/
    void set_anchor_referent_obj(GameObj* obj);
    /*获取锚定对象*/
    const GameObj* get_anchor_referent_obj();
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
    /// <summary>
    /// 获取自身某锚点的全局坐标
    /// </summary>
    /// <param name="mode">目标锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode mode);
    /// <summary>
    /// 获取自身某锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 计算本节点和指定锚定对象的锚点全局坐标（不会修改实际锚定对象）
    /// </remarks>
    /// <param name="obj">锚定对象</param>
    /// <param name="mode">目标锚点</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(GameObj* obj, const AnchorMode mode);
    /// <summary>
    /// 获取假子节点锚点的全局坐标
    /// </summary>
    /// <remarks>
    /// 某个对象以本节点为锚点，计算该对象的某个锚点全局坐标
    /// </remarks>
    /// <param name="aligned">自身对齐锚点</param>
    /// <param name="reference">目标参照锚点</param>
    /// <param name="target">目标计算锚点</param>
    /// <param name="pos">目标相对坐标</param>
    /// <param name="p_size">目标尺寸</param>
    /// <returns>Vector2</returns>
    Vector2 get_anchor_position(const AnchorMode aligned, const AnchorMode reference, const AnchorMode target, Vector2 pos, SDL_Point p_size);
    /// <summary>
    /// 检测是否在屏幕内
    /// </summary>
    /// <param name="val">-1 0 1 横向，整体，纵向</param>
    /// <returns>true/false 在/不在</returns>
    bool check_in_screen(int val);

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
    /*锚定对象锚点*/
    AnchorMode anchor_referent_mode = AnchorMode::TOPLEFT;

protected:
    // 父节点
    GameObj* parent = nullptr;
    // 锚定对象
    GameObj* anchor_referent_obj = nullptr;
    // 子节点
    std::list<GameObj*> children;

public:
    /*设置父节点*/
    void set_parent(GameObj* p);
    /*获取父节点*/
    GameObj* get_parent();
    /*获取子节点数组*/
    std::list<GameObj*>& get_children();
    /*添加子节点*/
    void add_children(GameObj* obj);
    /*移除子节点*/
    void remove_children(GameObj* obj);
    /*删除子节点*/
    void delete_children(GameObj* obj);
    
};