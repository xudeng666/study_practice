#include "game_btn.h"
#include "res_mgr.h"


GameBtn::GameBtn(const Vector2 pos, const std::string name)
{
	position = pos;
	res_name = name;
}

void GameBtn::on_update(float delta)
{
	texture = ResMgr::instance()->find_texture(res_name + std::to_string(static_cast<int>(status)));
}

//void GameBtn::on_render(const Camera* camera)
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
	on_click();
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