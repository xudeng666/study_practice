#include "game_btn.h"
#include "res_mgr.h"
#include "event_mgr.h"


INIT_TYPE_NAME(GameBtn);

void GameBtn::on_init()
{
	GameImg::on_init();
	status = ButtonState::NORMAL;
}

void GameBtn::on_enter()
{
	status = ButtonState::NORMAL;
	GameImg::on_enter();
}

//void GameBtn::on_input(const SDL_Event& event)
//{
//	GameImg::on_input(event);
//}

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
	GameImg::on_cursor_down();
}

void GameBtn::on_cursor_up()
{
	if (status != ButtonState::PRESSED)
		return;
	status = ButtonState::HOVER;
	GameImg::on_cursor_up();
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
	GameImg::on_cursor_hover(is_hover);
}

void GameBtn::set_texture()
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(status)));
	if (!texture)
	{
		std::cout << ID << " texture null" << std::endl;
	}
}