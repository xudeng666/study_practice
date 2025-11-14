#include "phf_obj.h"

#include "event_mgr.h"

void PhfObj::on_input(const SDL_Event& event)
{
	if (event.type == EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SYNC))
	{
		EventData* data = static_cast<EventData*>(event.user.data1);
		if (!data) return;
		int m;
		if (data->get("meal", m))
		{
			set_picked_meal(static_cast<Meal>(m));
		}
	}

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

void PhfObj::on_cursor_down() {}
void PhfObj::on_cursor_up() {}

void PhfObj::set_meal(Meal m)
{
	meal = m;
}

Meal PhfObj::get_meal()
{
	return meal;
}

void PhfObj::set_picked_meal(Meal m)
{
	picked_meal = m;
}

Meal PhfObj::get_picked_meal()
{
	return picked_meal;
}

void PhfObj::change_picked_meal()
{
	// ·¢ËÍÊÂ¼þ
	SDL_Event event;
	event.type = EventMgr::instance()->get_event_type(EventType::PHF_EVENT_SEND);
	EventData* data = new EventData();
	data->set("meal", static_cast<int>(meal));
	event.user.data1 = data;
	event.user.data2 = nullptr;
	SDL_PushEvent(&event);
}