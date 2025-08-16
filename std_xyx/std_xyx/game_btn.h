#pragma once

#include "game_img.h"

/*∞¥≈•¿‡*/
class GameBtn :public GameImg
{
public:
	GameBtn() = default;
	~GameBtn() = default;
	GameBtn(const Vector2 pos, const std::string name, std::function<void()> click = nullptr);

	void on_update(float delta) override;
	//void on_render() override;
	void on_cursor_down() override;
	void on_cursor_up() override;
	void on_cursor_hover(bool is_hover) override;
	void set_on_click(std::function<void()> click);

private:
	std::string res_name;
	ButtonState status = ButtonState::NORMAL;
	std::function<void()> on_click = nullptr;
};

