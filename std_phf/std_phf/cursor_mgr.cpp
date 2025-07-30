#include "cursor_mgr.h"
#include "res_mgr.h"
#include "util.h"

CursorMgr* CursorMgr::instance()
{
	if (!manager)
	{
		manager = new CursorMgr();
	}
	return manager;
}

void CursorMgr::on_input(const SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		{
			pos_cursor.x = event.motion.x;
			pos_cursor.y = event.motion.y;
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_mouse_lbtn_down = true;
			std::string str = "click_" + getIntRand(1, 3);
			Mix_PlayChannel(-1, ResMgr::instance()->find_audio(str), 0);
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			is_mouse_lbtn_down = false;
		}
		break;
	}
}

void CursorMgr::on_render(SDL_Renderer* renderer)
{
	std::string str = "";
	switch (meal_picked)
	{
	case Meal::None:				break;
	case Meal::Cola:				str = "cola";				break;
	case Meal::Sprite:				str = "sprite";				break;
	case Meal::BraisedChicken_Hot:	str = "bc_hot_picked";		break;
	case Meal::BraisedChicken_Cold:	str = "bc_cold_picked";		break;
	case Meal::MeatBall_Hot:		str = "mb_hot_picked";		break;
	case Meal::MeatBall_Cold:		str = "mb_cold_picked";		break;
	case Meal::RedCookedPork_Hot:	str = "rcp_hot_picked";		break;
	case Meal::RedCookedPork_Cold:	str = "rcp_cold_picked";	break;
	case Meal::BraisedChicken_Box:	str = "bc_box";				break;
	case Meal::MeatBall_Box:		str = "mb_box";				break;
	case Meal::RedCookedPork_Box:	str = "rcp_box";			break;
	case Meal::TakeoutBox:			str = "tb_picked";			break;
	}

	if (str != "")
	{
		SDL_Texture* texture_picked = ResMgr::instance()->find_texture(str);
		SDL_Rect rect_p = { pos_cursor.x, pos_cursor.y, 0, 0 };
		SDL_QueryTexture(texture_picked, nullptr, nullptr, &rect_p.w, &rect_p.h);
		SDL_RenderCopy(renderer, texture_picked, nullptr, &rect_p);
	}

	SDL_Rect rect_cursor = { pos_cursor.x, pos_cursor.y, 64, 64 };
	SDL_Texture* texture_cursor = ResMgr::instance()->find_texture(is_mouse_lbtn_down ? "cursor_down" : "cursor_idle");
	SDL_RenderCopy(renderer, texture_cursor, nullptr, &rect_cursor);
}

void CursorMgr::set_picked(Meal meal)
{
	meal_picked = meal;
}

Meal CursorMgr::get_picked()
{
	return meal_picked;
}

CursorMgr::CursorMgr() = default;
CursorMgr::~CursorMgr() = default;