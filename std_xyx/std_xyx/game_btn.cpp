#include "game_btn.h"
#include "res_mgr.h"


GameBtn::GameBtn(const Vector2 pos, const std::string name, std::function<void()> click)
{
	position = pos;
	res_name = name;
	click_enabled = true;
	on_click = click;
	status = ButtonState::NORMAL;
	set_rect();
}

void GameBtn::on_update(float delta)
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(status)));
	SDL_QueryTexture(texture, nullptr, nullptr, &size.x, &size.y);
	set_rect();
}

//void GameBtn::on_render()
//{
//
//}

void GameBtn::on_cursor_down()
{
	status = ButtonState::PRESSED;
}

void GameBtn::on_cursor_up()
{
	if (status != ButtonState::PRESSED)
		return;
	status = ButtonState::NORMAL;
	if (on_click)
	{
		on_click();
	}
}

void GameBtn::on_cursor_hover(bool is_hover)
{
	if (is_hover)
	{
		status = status == ButtonState::PRESSED ? ButtonState::PRESSED : ButtonState::HOVER;
	}
	else
	{
		status = ButtonState::NORMAL;
	}
}

void GameBtn::set_on_click(std::function<void()> click)
{
	on_click = click;
}