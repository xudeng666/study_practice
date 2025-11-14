#pragma once
#include "game_img.h"

#include "meal.h"

class Cursor :
    public GameImg
{
public:
    Cursor() = default;
    virtual ~Cursor() = default;

    Cursor(const std::string& id) : GameImg(id) {}
    Cursor(const std::string& id, int num) : GameImg(id, num) {}

    DEFINE_TYPE_NAME(Cursor);

    virtual void on_init() override;
    virtual void on_enter() override;
    virtual void on_update(float delta) override;
    virtual void on_input(const SDL_Event& event) override;
    // 设置当前抓取的餐品
    void set_picked(Meal meal);
    // 获取当前抓取的餐品
    Meal get_picked();
private:
    TreeNode_WP cursor;                 // 光标图
private:
    Meal meal_picked = Meal::None;		// 当前抓取的餐品
    bool is_mouse_lbtn_down = false;	// 鼠标左键是否按下
};

