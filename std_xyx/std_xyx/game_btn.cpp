#include "game_btn.h"
#include "res_mgr.h"
#include "event_mgr.h"


INIT_TYPE_NAME(GameBtn);

void GameBtn::on_init()
{
	status = ButtonState::NORMAL;
	// 注册监听事件点击、抬起和鼠标移动
	EventMgr::instance()->add_listen_event(EventType::MOUSE_MOVE, self_node, [&](const EventParams& data) {
		if (!click_enabled) return;
		SDL_Point p = std::any_cast<SDL_Point>(data.at("point"));
		SDL_Rect t = get_Rect();
		on_cursor_hover(SDL_PointInRect(&p, &t));
		});
	EventMgr::instance()->add_listen_event(EventType::MOUSE_DOWN_LEFT, self_node, [&](const EventParams& data) {
		if (!click_enabled) return;
		SDL_Point p = std::any_cast<SDL_Point>(data.at("point"));
		SDL_Rect t = get_Rect();
		if (SDL_PointInRect(&p, &t))
		{
			on_cursor_down();
		}
		});
	EventMgr::instance()->add_listen_event(EventType::MOUSE_UP_LEFT, self_node, [&](const EventParams& data) {
		if (!click_enabled) return;
		SDL_Point p = std::any_cast<SDL_Point>(data.at("point"));
		SDL_Rect t = get_Rect();
		if (SDL_PointInRect(&p, &t))
		{
			on_cursor_up();
		}
		});
}

void GameBtn::on_enter()
{
	status = ButtonState::NORMAL;
	GameImg::on_enter();
}

void GameBtn::on_input(const SDL_Event& event)
{
	/*if (!click_enabled)
	{
		return;
	}

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
	{
		SDL_Point p = { event.motion.x,event.motion.y };
		SDL_Rect t = get_Rect();
		on_cursor_hover(SDL_PointInRect(&p, &t));
	}
	break;
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
	}*/
}

void GameBtn::on_update(float delta)
{
	set_texture();
	GameImg::on_update(delta);
}

void GameBtn::on_render()
{
	GameImg::on_render();
}

void GameBtn::on_cursor_down()
{
	status = ButtonState::PRESSED;
}

void GameBtn::on_cursor_up()
{
	if (status != ButtonState::PRESSED)
		return;
	status = ButtonState::HOVER;
	if (on_click)
	{
		on_click();
	}
}

void GameBtn::on_cursor_hover(bool is_hover)
{
	ButtonState t = ButtonState::NORMAL;
	if (is_hover)
	{
		t = status == ButtonState::PRESSED ? ButtonState::PRESSED : ButtonState::HOVER;
	}

	if (t != status)
	{
		status = t;
	}
}

void GameBtn::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(status)));
	if (!texture)
	{
		std::cout << ID << " texture null" << std::endl;
	}
}

void GameBtn::set_on_click(std::function<void()> click)
{
	on_click = click;
}