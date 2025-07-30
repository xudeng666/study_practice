#pragma once

#include "meal.h"
#include "region.h"

/*餐盒类*/
class TakeoutBox :
    public Region
{
public:
    TakeoutBox(int x, int y) : Region({ x, y, 92, 32 }) {}
    ~TakeoutBox() = default;

    // 放置
    void on_cursor_up() override;
    // 抓取
    void on_cursor_down() override;
    void on_render(SDL_Renderer* renderer) override;

private:
    Meal meal = Meal::None;     // 外卖盒位置当前餐品类型

private:
    /// <summary>
    /// 是否可以放置
    /// </summary>
    /// <param name="target">餐品类型</param>
    /// <returns>bool</returns>
    bool can_place(Meal target);
};

