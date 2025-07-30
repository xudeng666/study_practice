#include "microwave_oven.h"
#include "res_mgr.h"
#include "cursor_mgr.h"


MicrowaveOven::MicrowaveOven(int x, int y) :Region({ x,y,284,176 })
{
	timer.set_one_shot(true);
	timer.set_wait_time(9.0f);
	timer.set_on_timeout([&]()
		{
			is_working = false;
			Mix_PlayChannel(-1, ResMgr::instance()->find_audio("mo_complete"), 0);
		});
}

//MicrowaveOven::~MicrowaveOven() = default;

void MicrowaveOven::on_cursor_up()
{
	if (!is_working && meal_target == Meal::None && can_place(CursorMgr::instance()->get_picked()))
	{
		switch (CursorMgr::instance()->get_picked())
		{
		case Meal::BraisedChicken_Cold:
			meal_target = Meal::BraisedChicken_Hot;
			break;
		case Meal::MeatBall_Cold:
			meal_target = Meal::MeatBall_Hot;
			break;
		case Meal::RedCookedPork_Cold:
			meal_target = Meal::RedCookedPork_Hot;
			break;
		}
		timer.restart();
		is_working = true;
		CursorMgr::instance()->set_picked(Meal::None);
		Mix_PlayChannel(-1, ResMgr::instance()->find_audio("mo_working"), 0);
	}
}

void MicrowaveOven::on_cursor_down()
{
	if (!is_working && CursorMgr::instance()->get_picked() == Meal::None)
	{
		CursorMgr::instance()->set_picked(meal_target);
		meal_target = Meal::None;
	}
}

void MicrowaveOven::on_update(float delta)
{
	if (is_working)
	{
		timer.on_update(delta);
	}
}

void MicrowaveOven::on_render(SDL_Renderer* renderer)
{
	SDL_Texture* texture = ResMgr::instance()->find_texture(is_working ? "mo_working" : "mo_opening");
	SDL_RenderCopy(renderer, texture, nullptr, &rect);

	if (!is_working)
	{
		std::string str = "";
		switch (meal_target)
		{
		case Meal::None:	break;
		case Meal::BraisedChicken_Hot:	str = "bc_hot_picked";	break;
		case Meal::MeatBall_Hot:		str = "mb_hot_picked";	break;
		case Meal::RedCookedPork_Hot:	str = "rcp_hot_picked";	break;
		}

		if (str != "")
		{
			SDL_Texture* texture_meal = ResMgr::instance()->find_texture(str);
			SDL_Rect rect_meal = { rect.x + 113, rect.y + 65, 0, 0 };
			SDL_QueryTexture(texture_meal, nullptr, nullptr, &rect_meal.w, &rect_meal.h);
			SDL_RenderCopy(renderer, texture_meal, nullptr, &rect_meal);
		}
	}
}

bool MicrowaveOven::can_place(Meal target)
{
	return target == Meal::BraisedChicken_Cold || target == Meal::MeatBall_Cold || target == Meal::RedCookedPork_Cold ;
}
