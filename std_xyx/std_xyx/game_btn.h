#pragma once

#include "game_img.h"

/*∞¥≈•¿‡*/
class GameBtn :public GameImg
{
public:
	GameBtn() = default;
	virtual ~GameBtn() = default;

	GameBtn(const std::string& id) : GameImg(id) {}
	GameBtn(const std::string& id, int num) : GameImg(id, num) {}

	DEFINE_TYPE_NAME(GameBtn);

	virtual void on_init() override;
	virtual void on_enter() override;
	virtual void on_input(const SDL_Event& event) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;
	virtual void set_texture() override;
	void on_cursor_down();
	void on_cursor_up();
	void on_cursor_hover(bool is_hover);
	void set_on_click(std::function<void()> click);

private:
	ButtonState status = ButtonState::NORMAL;
	std::function<void()> on_click = nullptr;
};

INIT_TYPE_NAME(GameBtn);