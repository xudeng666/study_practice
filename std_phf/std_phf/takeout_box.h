#pragma once

#include "meal.h"
#include "region.h"

/*�ͺ���*/
class TakeoutBox :
    public Region
{
public:
    TakeoutBox(int x, int y) : Region({ x, y, 92, 32 }) {}
    ~TakeoutBox() = default;

    // ����
    void on_cursor_up() override;
    // ץȡ
    void on_cursor_down() override;
    void on_render(SDL_Renderer* renderer) override;

private:
    Meal meal = Meal::None;     // ������λ�õ�ǰ��Ʒ����

private:
    /// <summary>
    /// �Ƿ���Է���
    /// </summary>
    /// <param name="target">��Ʒ����</param>
    /// <returns>bool</returns>
    bool can_place(Meal target);
};

