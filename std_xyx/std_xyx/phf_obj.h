#pragma once
#include "game_img.h"
#include "meal.h"

class PhfObj :
    public GameImg
{
public:
	PhfObj() = default;
	virtual ~PhfObj() = default;

	PhfObj(const std::string& id) : GameImg(id) {}
	PhfObj(const std::string& id, int num) : GameImg(id, num) {}

	virtual void on_input(const SDL_Event& event) override;
	virtual void on_cursor_down();
	virtual void on_cursor_up();

	Meal get_meal();
	void set_meal(Meal m);
	Meal get_picked_meal();
	void change_picked_meal();
private:
	void set_picked_meal(Meal m);

private:
	Meal meal = Meal::None;			// 自身类型
	Meal picked_meal = Meal::None;	// 当前拿取类型
};

