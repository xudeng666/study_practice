#pragma once

#include <SDL.h>

#include "game_type.h"
#include "camera.h"

/*游戏对象基类*/
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
    /*玩家输入*/
    void on_input(const SDL_Event& event);
    /*设置坐标*/
    void set_position(const Vector2& pos);
    /*获取坐标*/
    const Vector2& get_position() const;
    /*设置尺寸*/
    void set_size(const SDL_Point& size);
    /*获取尺寸*/
    const SDL_Point& get_size() const;
    /*设置锚点*/
    void set_anchor_mode(const AnchorMode mode);
    /*获取锚点*/
    const AnchorMode get_anchor_mode() const;
    /*设置中心*/
    void set_center(const SDL_FPoint& pos);
    /*设置角度*/
    void set_rotation(double val);
    /*设置点击区域状态*/
    void set_enabled(bool enable);
    /*获取点击区域状态*/
    bool get_enabled();
    /*设置点击区域*/
    void set_rect(SDL_Rect* rect);

protected:
    // 旋转角度
    double angle = 0;
    /*点击区域开关状态*/
    bool click_enabled = false;
	/*坐标*/
	Vector2 position;
	/*尺寸*/
    SDL_Point size = { 0 };
    // 中心点
    SDL_FPoint center = { 0 };
	/*锚点*/
    AnchorMode anchor_mode = AnchorMode::CENTER;
    /*点击区域*/
    SDL_Rect click_rect = { 0 };
};