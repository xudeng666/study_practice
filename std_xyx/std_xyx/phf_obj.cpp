#include "phf_obj.h"
#include "event_mgr.h"

INIT_TYPE_NAME(PhfObj);

void PhfObj::on_input(const SDL_Event& event)
{
	if (!click_enabled)
	{
		return;
	}

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x,event.button.y };
			SDL_Rect t = get_Rect();
			if (SDL_PointInRect(&p, &t))
			{
				on_cursor_down();
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			SDL_Point p = { event.button.x,event.button.y };
			SDL_Rect t = get_Rect();
			if (SDL_PointInRect(&p, &t))
			{
				on_cursor_up();
			}
		}
		break;
	}
}

void PhfObj::on_cursor_down()
{
}
void PhfObj::on_cursor_up()
{
}


void PhfMeal::set_meal(Meal m)
{
	meal = m;
}

Meal PhfMeal::get_meal()
{
	return meal;
}

void PhfMeal::set_picked_meal(Meal m)
{
	picked_meal = m;
}

Meal PhfMeal::get_picked_meal()
{
	return picked_meal;
}

void PhfMeal::change_picked_meal(Meal m)
{
	// ·¢ËÍÊÂ¼ş
	SDL_Event event;
	event.type = EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SEND);
	EventData* data = new EventData();
	data->set("meal", static_cast<int>(m));
	event.user.data1 = data;
	event.user.data2 = nullptr;
	SDL_PushEvent(&event);
}