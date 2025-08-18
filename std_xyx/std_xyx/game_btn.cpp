#include "game_btn.h"
#include "res_mgr.h"


GameBtn::GameBtn(const Vector2 pos, const std::string name, std::function<void()> click)
{
	position = pos;
	res_name = name;
	on_click = click;
	status = ButtonState::NORMAL;
}

void GameBtn::on_update(float delta)
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(status)));
	click_rect.x = position.x;
	click_rect.y = position.y;
	SDL_QueryTexture(texture, nullptr, nullptr, &click_rect.w, &click_rect.h);
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
		status = status == ButtonState::PRESSED ? ButtonState::DISABLED : ButtonState::HOVER;
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