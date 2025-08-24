#include "game_btn.h"
#include "res_mgr.h"


GameBtn::GameBtn(const Vector2 pos, const std::string name, std::function<void()> click)
{
	position = pos;
	res_name = name;
	click_enabled = true;
	on_click = click;
	status = ButtonState::NORMAL;
}

void GameBtn::on_enter()
{
	status = ButtonState::NORMAL;
	GameImg::on_enter();
}

void GameBtn::on_update(float delta)
{
	GameImg::on_update(delta);
}

void GameBtn::on_render()
{
	GameImg::on_render();
}

void GameBtn::on_cursor_down()
{
	status = ButtonState::PRESSED;
	set_texture();
	set_size();
}

void GameBtn::on_cursor_up()
{
	if (status != ButtonState::PRESSED)
		return;
	status = ButtonState::NORMAL;
	set_texture();
	set_size();
	if (on_click)
	{
		on_click();
	}
}

void GameBtn::on_cursor_hover(bool is_hover)
{
	ButtonState t;
	if (is_hover)
	{
		t = status == ButtonState::PRESSED ? ButtonState::PRESSED : ButtonState::HOVER;
	}
	else
	{
		t = ButtonState::NORMAL;
	}
	if (t != status)
	{
		status = t;
		set_texture();
		set_size();
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