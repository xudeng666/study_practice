#pragma once

#include "game_img.h"

/*∞¥≈•¿‡*/
class GameBtn :public GameImg
{
public:
	GameBtn() = default;
	virtual ~GameBtn() = default;

	GameBtn(const std::string& id) : GameImg(id) { click_enabled = true; }
	GameBtn(const std::string& id, int num) : GameImg(id, num) { click_enabled = true; }

	DEFINE_TYPE_NAME(GameBtn);

	virtual void on_init() override;
	virtual void on_enter() override;
	//virtual void on_input(const SDL_Event& event) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	virtual void set_texture() override;
	virtual void on_cursor_down() override;
	virtual void on_cursor_up() override;
	virtual void on_cursor_hover(bool is_hover) override;
private:
	ButtonState status = ButtonState::NORMAL;
};